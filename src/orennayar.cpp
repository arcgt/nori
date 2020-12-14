#include <nori/bsdf.h>
#include <nori/frame.h>
#include <nori/warp.h>

NORI_NAMESPACE_BEGIN

class OrenNayar : public BSDF {
public:
    OrenNayar(const PropertyList &propList) {
        // the standard deviation of the microfacet orientation angle
        m_sigma2 = pow(M_PI / 180.0 * (float) propList.getFloat("sigma", 20.0), 2.0);

        m_R = (Color3f) propList.getColor("R");

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

    virtual Color3f sample(BSDFQueryRecord &bRec, const Point2f &_sample) const override {
        if (Frame::cosTheta(bRec.wi) <= 0)
            return Color3f(0.0f);

        bRec.measure = ESolidAngle;

        // warp a uniformly distributed sample on [0,1]^2 to a direction on a cosine-weighted hemisphere
        bRec.wo = Warp::squareToCosineHemisphere(_sample);

        /* Relative index of refraction: no change */
        bRec.eta = 1.0f;

        // if the reflected direction points below the surface simply reject the sample by returning 0
        if (Frame::cosTheta(bRec.wo) <= 0){
            return Color3f(0.0f);
        }

        return (eval(bRec)*Frame::cosTheta(bRec.wo)) / pdf(bRec);
    }

    virtual std::string toString() const {
        return "OrenNayar[]";
    }
private:
    float m_sigma2;
    Color3f m_R;
    float m_A, m_B;
};

NORI_REGISTER_CLASS(OrenNayar, "orennayar");
NORI_NAMESPACE_END
