// // fresnel blend with oren nayar
// #include <nori/bsdf.h>
// #include <nori/frame.h>
// #include <nori/warp.h>
//
// NORI_NAMESPACE_BEGIN
//
// class Layered : public BSDF {
// public:
//     Layered(const PropertyList &propList) {
//         /* Interior IOR (default: water) */
//         m_intIOR = (float) propList.getFloat("intIOR", 1.333f);
//         /* Exterior IOR (default: air) */
//         m_extIOR = (float) propList.getFloat("extIOR", 1.000277f);
//
//         m_Rs = pow((m_extIOR - m_intIOR) / (m_extIOR + m_intIOR), 2);
//         m_Rd = (Color3f) propList.getColor("Rd", Color3f(0.5f));
//
//         // the standard deviation of the microfacet orientation angle
//         m_sigma2 = pow(M_PI / 180.0 * (float) propList.getFloat("sigma", 20.0), 2.0);
//
//         // precompute and store the values of the A and B parameters in the constructor to save work in evaluating the BRDF later
//         m_A = 1.f - (m_sigma2 / (2.f * (m_sigma2 + 0.33f)));
//         m_B = 0.45f * m_sigma2 / (m_sigma2 + 0.09f);
//     }
//
//     float pow5 (float v) const {
//         return (v * v) * (v * v) * v;
//     }
//
//     Color3f SchlickFresnel(float cosTheta) const {
//         return m_Rs + pow5(1 - cosTheta) * (Color3f(1.) - m_Rs);
//     }
//
//     // Evaluate the microfacet normal distribution D
//     float evalBeckmann(const Normal3f &m) const {
//         float temp = Frame::tanTheta(m) / (1-m_Rs),
//               ct = Frame::cosTheta(m), ct2 = ct*ct;
//
//         return std::exp(-temp*temp) / (M_PI * (1-m_Rs) * (1-m_Rs) * ct2 * ct2);
//     }
//
//     virtual Color3f eval(const BSDFQueryRecord &bRec) const override {
//         if (Frame::cosTheta(bRec.wo) <= 0.f) {
//             return 0.f;
//         }
//
//         // compute values of sinThetaI and sinThetaO
//         float sinThetaI = Frame::sinTheta(bRec.wi);
//         float sinThetaO = Frame::sinTheta(bRec.wo);
//
//         // compute cosine term max(0, cos(phiI - phiO)) by applying the trigonometric identity cos(a - b) = cosacosb + sinasinb
//         float maxCos = 0.0;
//         if (sinThetaI > 1e-4 && sinThetaO > 1e-4) {
//             float sinPhiI = Frame::sinPhi(bRec.wi);
//             float sinPhiO = Frame::sinPhi(bRec.wo);
//             float cosPhiI = Frame::cosPhi(bRec.wi);
//             float cosPhiO = Frame::cosPhi(bRec.wo);
//
//             float dCos = cosPhiI * cosPhiO + sinPhiI * sinPhiO;
//             maxCos = std::max((float)0, dCos);
//         }
//
//         // calculate sin(alpha) using sine value computed earlier and tan(beta) = sin(beta) / cos(beta)
//         float sinAlpha, tanBeta;
//         if (std::abs(Frame::cosTheta(bRec.wi)) > std::abs(Frame::cosTheta(bRec.wo))) {
//             sinAlpha = sinThetaO;
//             tanBeta = sinThetaI / std::abs(Frame::cosTheta(bRec.wi));
//         }
//         else {
//             sinAlpha = sinThetaI;
//             tanBeta = sinThetaO / std::abs(Frame::cosTheta(bRec.wo));
//         }
//
//         Color3f diffuse = (1-m_Rs) * m_Rd * INV_PI * (m_A + m_B * maxCos * sinAlpha * tanBeta);
//
//         Vector3f wh = bRec.wi + bRec.wo;
//         if (wh.x() == 0 && wh.y() == 0 && wh.z() == 0) {
//           return Color3f(0);
//         }
//         wh = wh.normalized();
//
//         Color3f specular = evalBeckmann(wh) * SchlickFresnel(bRec.wi.dot(wh)) / (4 * std::abs(bRec.wi.dot(wh)) * std::max(std::abs(Frame::cosTheta(bRec.wi)), std::abs(Frame::cosTheta(bRec.wo))));
//
//         return diffuse + specular;
//     }
//
//     virtual float pdf(const BSDFQueryRecord &bRec) const override {
//         if (Frame::cosTheta(bRec.wo) <= 0.f) {
//             return 0.f;
//         }
//         // following the equations in the task
//         Vector3f wh = (bRec.wi + bRec.wo).normalized();
//         float D = evalBeckmann(wh);
//         float J = 1 / (4*wh.dot(bRec.wo));
//
//         return m_Rs*D*Frame::cosTheta(wh)*J + (1-m_Rs)*Frame::cosTheta(bRec.wo)*INV_PI;
//     }
//
//     virtual Color3f sample(BSDFQueryRecord &bRec, const Point2f &_sample) const override {
//         if (Frame::cosTheta(bRec.wi) <= 0)
//             return Color3f(0.0f);
//
//         if (_sample.x() < m_Rs) {
//             Point2f sample(_sample.x() / m_Rs, _sample.y()); // rescale sample as already used c for comparing with m_ks
//             Vector3f wh = Warp::squareToBeckmann(sample, (1-m_Rs)); // randomly generate with pdf proportional to D
//             bRec.wo = (2*(wh.dot(bRec.wi))*wh - bRec.wi).normalized(); // perfect reflection: microfacet theory slide 4
//         } else {
//             Point2f sample((_sample.x() - m_Rs) / (1 - m_Rs), _sample.y());
//             // warp a uniformly distributed sample on [0,1]^2 to a direction on a cosine-weighted hemisphere
//             bRec.wo = Warp::squareToCosineHemisphere(sample);
//         }
//
//         // if the reflected direction points below the surface simply reject the sample by returning 0
//         if (Frame::cosTheta(bRec.wo) <= 0){
//             return Color3f(0.0f);
//         }
//
//         return (eval(bRec)*Frame::cosTheta(bRec.wo)) / pdf(bRec);
//     }
//
//     virtual std::string toString() const {
//         return "Layered[]";
//     }
// private:
//     float m_intIOR;
//     float m_extIOR;
//     float m_Rs;
//     Color3f m_Rd;
//     float m_sigma2;
//     float m_A, m_B;
//
// };
//
// NORI_REGISTER_CLASS(Layered, "layered");
// NORI_NAMESPACE_END

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
        return "Layered[]";
    }
private:
    float m_intIOR;
    float m_extIOR;
    float m_Rs;
    Color3f m_Rd;

};

NORI_REGISTER_CLASS(Layered, "layered");
NORI_NAMESPACE_END



// #include <nori/bsdf.h>
// #include <nori/frame.h>
//
// NORI_NAMESPACE_BEGIN
//
// class Layered : public BSDF {
// public:
//     Layered(const PropertyList &propList) {
//         // dielectric
//         /* Interior IOR (default: water) */
//         m_intIOR = propList.getFloat("intIOR", 1.333f);
//         /* Exterior IOR (default: air) */
//         m_extIOR = propList.getFloat("extIOR", 1.000277f);
//
//         m_eta = m_intIOR / m_extIOR;
//
//         // the standard deviation of the microfacet orientation angle
//         m_sigma2 = pow(M_PI / 180.0 * (float) propList.getFloat("sigma", 20.0), 2.0);
//
//         m_R = (Color3f) propList.getColor("R");
//
//         // precompute and store the values of the A and B parameters in the constructor to save work in evaluating the BRDF later
//         m_A = 1.f - (m_sigma2 / (2.f * (m_sigma2 + 0.33f)));
//         m_B = 0.45f * m_sigma2 / (m_sigma2 + 0.09f);
//
//         if(propList.has("albedo")) {
//             PropertyList l;
//             l.setColor("value", propList.getColor("albedo"));
//             m_albedo = static_cast<Texture<Color3f> *>(NoriObjectFactory::createInstance("constant_color", l));
//     }
//
//     virtual Color3f eval(const BSDFQueryRecord &bRec) const override {
//       if (Frame::cosTheta(bRec.wi) <= 0 || Frame::cosTheta(bRec.wo) <= 0)
//           return Color3f(0.0f);
//
//       // compute values of sinThetaI and sinThetaO
//       float sinThetaI = Frame::sinTheta(bRec.wi);
//       float sinThetaO = Frame::sinTheta(bRec.wo);
//
//       // compute cosine term max(0, cos(phiI - phiO)) by applying the trigonometric identity cos(a - b) = cosacosb + sinasinb
//       float maxCos = 0.0;
//       if (sinThetaI > 1e-4 && sinThetaO > 1e-4) {
//           float sinPhiI = Frame::sinPhi(bRec.wi);
//           float sinPhiO = Frame::sinPhi(bRec.wo);
//           float cosPhiI = Frame::cosPhi(bRec.wi);
//           float cosPhiO = Frame::cosPhi(bRec.wo);
//
//           float dCos = cosPhiI * cosPhiO + sinPhiI * sinPhiO;
//           maxCos = std::max((float)0, dCos);
//         }
//
//         // calculate sin(alpha) using sine value computed earlier and tan(beta) = sin(beta) / cos(beta)
//         float sinAlpha, tanBeta;
//         if (std::abs(Frame::cosTheta(bRec.wi)) > std::abs(Frame::cosTheta(bRec.wo))) {
//             sinAlpha = sinThetaO;
//             tanBeta = sinThetaI / std::abs(Frame::cosTheta(bRec.wi));
//         }
//         else {
//             sinAlpha = sinThetaI;
//             tanBeta = sinThetaO / std::abs(Frame::cosTheta(bRec.wo));
//         }
//
//         return m_R * INV_PI * (m_A + m_B * maxCos * sinAlpha * tanBeta);
//     }
//
//     virtual float pdf(const BSDFQueryRecord &bRec) const override {
//         /* Discrete BRDFs always evaluate to zero in Nori */
//         return 0.0f;
//     }
//
//     virtual Color3f sample(BSDFQueryRecord &bRec, const Point2f &sample) const override {
//         if (fresnel(Frame::cosTheta(bRec.wi), m_extIOR, m_intIOR) > sample.x()) {
//             // Reflection in local coordinates (from mirror.cpp)
//             bRec.wo = Vector3f(
//                 -bRec.wi.x(),
//                 -bRec.wi.y(),
//                  bRec.wi.z()
//             );
//             bRec.measure = EDiscrete;
//             /* Relative index of refraction: no change */
//             bRec.eta = 1.0f;
//         }
//         else {
//             // Refraction
//             // determine direction of incoming ray
//             Vector3f n = Vector3f(0.0f, 0.0f, 1.0f);
//             bRec.eta = m_extIOR / m_intIOR; // as on slide
//             if (Frame::cosTheta(bRec.wi) <= 0.0f) {
//                 n.z() *= -1.0f;
//                 bRec.eta = 1 / bRec.eta;
//             }
//
//             // set wo according to equation on slide
//             bRec.wo = (-bRec.eta * (bRec.wi - bRec.wi.dot(n) * n) - n * sqrt(1 - pow(bRec.eta, 2) * (1 - pow(bRec.wi.dot(n), 2)))).normalized();
//             bRec.measure = EDiscrete;
//             bRec.eta = m_intIOR / m_extIOR; // > 1
//         }
//
//         return Color3f(1.0f);
//     }
//
//     virtual std::string toString() const override {
//         return tfm::format(
//             "Layered[\n"
//             "  intIOR = %f,\n"
//             "  extIOR = %f\n"
//             "]",
//             m_intIOR, m_extIOR);
//     }
// private:
//     float m_intIOR, m_extIOR;
//     float m_sigma2;
//     Color3f m_R;
//     float m_A, m_B;
//
//     Texture<Color3f> * m_albedo;
// };
//
// NORI_REGISTER_CLASS(Layered, "layered");
// NORI_NAMESPACE_END
