// fresnel blend
#include <nori/bsdf.h>
#include <nori/frame.h>
#include <nori/warp.h>

NORI_NAMESPACE_BEGIN

class FresnelBlend : public BSDF {
public:
    FresnelBlend(const PropertyList &propList) {
        /* Interior IOR (default: water) */
        m_intIOR = (float) propList.getFloat("intIOR", 1.333f);
        /* Exterior IOR (default: air) */
        m_extIOR = (float) propList.getFloat("extIOR", 1.000277f);

        m_Rs = pow((m_extIOR - m_intIOR) / (m_extIOR + m_intIOR), 2);
        m_Rd = (Color3f) propList.getColor("Rd", Color3f(0.5f));
    }

    float pow5 (float v) const {
        return (v * v) * (v * v) * v;
    }

    Color3f SchlickFresnel(float cosTheta) const {
        return m_Rs + pow5(1 - cosTheta) * (Color3f(1.) - m_Rs);
    }

    // Evaluate the microfacet normal distribution D
    float evalBeckmann(const Normal3f &m) const {
        float temp = Frame::tanTheta(m) / (1-m_Rs),
              ct = Frame::cosTheta(m), ct2 = ct*ct;

        return std::exp(-temp*temp) / (M_PI * (1-m_Rs) * (1-m_Rs) * ct2 * ct2);
    }

    virtual Color3f eval(const BSDFQueryRecord &bRec) const override {
        if (Frame::cosTheta(bRec.wo) <= 0.f) {
            return 0.f;
        }
        Color3f diffuse = (28.f/(23.f*M_PI)) * m_Rd * (Color3f(1.f) - m_Rs) * (1 - pow5(1 - .5f * std::abs(Frame::cosTheta(bRec.wi)))) * (1 - pow5(1 - .5f * std::abs(Frame::cosTheta(bRec.wo))));

        Vector3f wh = bRec.wi + bRec.wo;
        if (wh.x() == 0 && wh.y() == 0 && wh.z() == 0) {
          return Color3f(0);
        }
        wh = wh.normalized();

        Color3f specular = evalBeckmann(wh) * SchlickFresnel(bRec.wi.dot(wh)) / (4 * std::abs(bRec.wi.dot(wh)) * std::max(std::abs(Frame::cosTheta(bRec.wi)), std::abs(Frame::cosTheta(bRec.wo))));

        return diffuse + specular;
    }

    virtual float pdf(const BSDFQueryRecord &bRec) const override {
        if (Frame::cosTheta(bRec.wo) <= 0.f) {
            return 0.f;
        }
        // following the equations in the task
        Vector3f wh = (bRec.wi + bRec.wo).normalized();
        float D = evalBeckmann(wh);
        float J = 1 / (4*wh.dot(bRec.wo));

        return m_Rs*D*Frame::cosTheta(wh)*J + (1-m_Rs)*Frame::cosTheta(bRec.wo)*INV_PI;
    }

    virtual Color3f sample(BSDFQueryRecord &bRec, const Point2f &_sample) const override {
        if (Frame::cosTheta(bRec.wi) <= 0)
            return Color3f(0.0f);

        if (_sample.x() < m_Rs) {
            Point2f sample(_sample.x() / m_Rs, _sample.y()); // rescale sample as already used c for comparing with m_ks
            Vector3f wh = Warp::squareToBeckmann(sample, (1-m_Rs)); // randomly generate with pdf proportional to D
            bRec.wo = (2*(wh.dot(bRec.wi))*wh - bRec.wi).normalized(); // perfect reflection: microfacet theory slide 4
        } else {
            Point2f sample((_sample.x() - m_Rs) / (1 - m_Rs), _sample.y());
            // warp a uniformly distributed sample on [0,1]^2 to a direction on a cosine-weighted hemisphere
            bRec.wo = Warp::squareToCosineHemisphere(sample);
        }

        // if the reflected direction points below the surface simply reject the sample by returning 0
        if (Frame::cosTheta(bRec.wo) <= 0){
            return Color3f(0.0f);
        }

        return (eval(bRec)*Frame::cosTheta(bRec.wo)) / pdf(bRec);
    }

    virtual std::string toString() const {
        return "FresnelBlend[]";
    }
private:
    float m_intIOR;
    float m_extIOR;
    float m_Rs;
    Color3f m_Rd;

};

NORI_REGISTER_CLASS(FresnelBlend, "fresnelblend");
NORI_NAMESPACE_END
