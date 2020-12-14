#include <nori/bsdf.h>
#include <nori/frame.h>
#include <nori/warp.h>

NORI_NAMESPACE_BEGIN

class TorrenceSparrow : public BSDF {
public:
    TorrenceSparrow(const PropertyList &propList) {
        m_R = (Color3f) propList.getColor("R", Color3f(0.5f));

        /* RMS surface roughness */
        m_alpha = propList.getFloat("alpha", 0.1f);

        /* Interior IOR (default: BK7 borosilicate optical glass) */
        m_intIOR = propList.getFloat("intIOR", 1.5046f);
        /* Exterior IOR (default: air) */
        m_extIOR = propList.getFloat("extIOR", 1.000277f);
    }

        /// Evaluate the microfacet normal distribution D
        float evalBeckmann(const Normal3f &m) const {
            float temp = Frame::tanTheta(m) / m_alpha,
                  ct = Frame::cosTheta(m), ct2 = ct*ct;

            return std::exp(-temp*temp)
                / (M_PI * m_alpha * m_alpha * ct2 * ct2);
        }

        /// Evaluate Smith's shadowing-masking function G1
        float smithBeckmannG1(const Vector3f &v, const Normal3f &m) const {
            float tanTheta = Frame::tanTheta(v);

            /* Perpendicular incidence -- no shadowing/masking */
            if (tanTheta == 0.0f)
                return 1.0f;

            /* Can't see the back side from the front and vice versa */
            if (m.dot(v) * Frame::cosTheta(v) <= 0)
                return 0.0f;

            float a = 1.0f / (m_alpha * tanTheta);
            if (a >= 1.6f)
                return 1.0f;
            float a2 = a * a;

            /* Use a fast and accurate (<0.35% rel. error) rational
               approximation to the shadowing-masking function */
            return (3.535f * a + 2.181f * a2)
                 / (1.0f + 2.276f * a + 2.577f * a2);
        }

    virtual Color3f eval(const BSDFQueryRecord &bRec) const override {
        float cosThetaO = std::abs(Frame::cosTheta(bRec.wo));
        float cosThetaI = std::abs(Frame::cosTheta(bRec.wi));
        Vector3f wh = bRec.wi + bRec.wo;

        // handle degenerate cases for microfacet reflection
        if (cosThetaI == 0 || cosThetaO == 0)
            return Color3f(0.);
        if (wh.x() == 0 && wh.y() == 0 && wh.z() == 0)
            return Color3f(0.);

        wh = wh.normalized();
        Color3f F = fresnel(wh.dot(bRec.wi), m_extIOR, m_intIOR);
        return m_R * evalBeckmann(wh) * smithBeckmannG1(bRec.wi, wh)*smithBeckmannG1(bRec.wo, wh) * F / (4 * cosThetaI * cosThetaO);
    }

    virtual float pdf(const BSDFQueryRecord &bRec) const override {
        if (Frame::cosTheta(bRec.wo) <= 0.f) {
            return 0.f;
        }
        // following the equations in the task
        Vector3f wh = (bRec.wi + bRec.wo).normalized();
        float D = evalBeckmann(wh);
        float J = 1 / (4*abs(wh.dot(bRec.wo)));

        return D*Frame::cosTheta(wh)*J;
    }

    virtual Color3f sample(BSDFQueryRecord &bRec, const Point2f &_sample) const override {
        if (Frame::cosTheta(bRec.wi) <= 0)
            return Color3f(0.0f);

        Point2f sample(_sample.x(), _sample.y());
        Vector3f wh = Warp::squareToBeckmann(sample, m_alpha);
        bRec.wo = (2*(wh.dot(bRec.wi))*wh - bRec.wi).normalized(); // perfect reflection: microfacet theory slide 4

        // if the reflected direction points below the surface simply reject the sample by returning 0
        if (Frame::cosTheta(bRec.wo) <= 0){
            return Color3f(0.0f);
        }

        return (eval(bRec)*Frame::cosTheta(bRec.wo)) / pdf(bRec);
    }

    virtual std::string toString() const {
        return "TorrenceSparrow[]";
    }
private:
    Color3f m_R;
    float m_intIOR, m_extIOR;
    float m_alpha;
};

NORI_REGISTER_CLASS(TorrenceSparrow, "torrencesparrow");
NORI_NAMESPACE_END
