// fresnel blend
#include <nori/bsdf.h>
#include <nori/frame.h>
#include <nori/warp.h>

NORI_NAMESPACE_BEGIN

class Layered : public BSDF {
public:
    Layered(const PropertyList &propList) {
        /* Interior IOR (default: water) */
        m_intIOR = (float) propList.getFloat("intIOR", 1.333f);
        /* Exterior IOR (default: air) */
        m_extIOR = (float) propList.getFloat("extIOR", 1.000277f);

        // the standard deviation of the microfacet orientation angle
        m_sigma2 = pow(M_PI / 180.0 * (float) propList.getFloat("sigma", 20.0), 2.0);
        m_R = (Color3f) propList.getColor("R", Color3f(0.5f));
        // precompute and store the values of the A and B parameters in the constructor to save work in evaluating the BRDF later
        m_A = 1.f - (m_sigma2 / (2.f * (m_sigma2 + 0.33f)));
        m_B = 0.45f * m_sigma2 / (m_sigma2 + 0.09f);
    }

    virtual Color3f eval(const BSDFQueryRecord &bRec) const override {
        if (Frame::cosTheta(bRec.wi) <= 0 || Frame::cosTheta(bRec.wo) <= 0)
            return Color3f(0.0f);

        // compute values of sinThetaI and sinThetaO
        float sinThetaI = Frame::sinTheta(bRec.wi);
        float sinThetaO = Frame::sinTheta(bRec.wo);

        // compute cosine term max(0, cos(phiI - phiO)) by applying the trigonometric identity cos(a - b) = cosacosb + sinasinb
        float maxCos = 0.0;
        if (sinThetaI > 1e-4 && sinThetaO > 1e-4) {
            float sinPhiI = Frame::sinPhi(bRec.wi);
            float sinPhiO = Frame::sinPhi(bRec.wo);
            float cosPhiI = Frame::cosPhi(bRec.wi);
            float cosPhiO = Frame::cosPhi(bRec.wo);

            float dCos = cosPhiI * cosPhiO + sinPhiI * sinPhiO;
            maxCos = std::max((float)0, dCos);
        }

        // calculate sin(alpha) using sine value computed earlier and tan(beta) = sin(beta) / cos(beta)
        float sinAlpha, tanBeta;
        if (std::abs(Frame::cosTheta(bRec.wi)) > std::abs(Frame::cosTheta(bRec.wo))) {
            sinAlpha = sinThetaO;
            tanBeta = sinThetaI / std::abs(Frame::cosTheta(bRec.wi));
        }
        else {
            sinAlpha = sinThetaI;
            tanBeta = sinThetaO / std::abs(Frame::cosTheta(bRec.wo));
        }

        return m_R * INV_PI * (m_A + m_B * maxCos * sinAlpha * tanBeta);
    }

    virtual float pdf(const BSDFQueryRecord &bRec) const override {
        if (Frame::cosTheta(bRec.wi) <= 0 || Frame::cosTheta(bRec.wo) <= 0)
            return 0.0f;

        return INV_PI * Frame::cosTheta(bRec.wo);
    }

    virtual Color3f sample(BSDFQueryRecord &bRec, const Point2f &sample) const override {
        if (fresnel(Frame::cosTheta(bRec.wi), m_extIOR, m_intIOR) > sample.x()) {
            // Reflection in local coordinates (from mirror.cpp)
            bRec.wo = Vector3f(
                -bRec.wi.x(),
                -bRec.wi.y(),
                 bRec.wi.z()
            );
            bRec.measure = EDiscrete;
            /* Relative index of reflection: no change */
            bRec.eta = 1.0f;
        }
        else {
            // Refraction
            // determine direction of incoming ray
            Vector3f n = Vector3f(0.0f, 0.0f, 1.0f);
            bRec.eta = m_extIOR / m_intIOR; // as on slide
            if (Frame::cosTheta(bRec.wi) <= 0.0f) {
                n.z() *= -1.0f;
                bRec.eta = 1 / bRec.eta;
            }

            // set wo according to equation on slide
            bRec.wo = (-bRec.eta * (bRec.wi - bRec.wi.dot(n) * n) - n * sqrt(1 - pow(bRec.eta, 2) * (1 - pow(bRec.wi.dot(n), 2)))).normalized();
            bRec.measure = EDiscrete;
            bRec.eta = m_intIOR / m_extIOR; // > 1

            // next layer BSDFQueryRecord - refracted ray direction taken as input direction to the next layer
            BSDFQueryRecord nextbRec = BSDFQueryRecord(bRec.wo);
            // ray exits from same point it originally entered
            bRec.wo = Vector3f(
                -bRec.wi.x(),
                -bRec.wi.y(),
                 bRec.wi.z()
            );
            nextbRec.measure = ESolidAngle;
            nextbRec.eta = bRec.eta;

            // if direction points below the surface simply reject the sample by returning 0
            if (Frame::cosTheta(nextbRec.wo) <= 0){
                return Color3f(0.0f);
            }

            return (eval(nextbRec)*Frame::cosTheta(nextbRec.wo)) / pdf(bRec);
        }

        return Color3f(1.0f);
    }

    virtual std::string toString() const {
        return "Layered[]";
    }
private:
    float m_intIOR, m_extIOR;
    float m_sigma2;
    Color3f m_R;
    float m_A, m_B;
};

NORI_REGISTER_CLASS(Layered, "layered");
NORI_NAMESPACE_END
