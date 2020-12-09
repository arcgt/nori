// Spotlight class which derives from Emitter and implements an infinitesimal light source which emits light in a specified directions.
// Uses base from previously implemented pointlight class, and method from PBR Book, Light Sources / Point Lights

#include <nori/emitter.h>

NORI_NAMESPACE_BEGIN

class Spotlight : public Emitter {
public:
    Spotlight(const PropertyList &propList) {
        m_power = (Color3f) propList.getColor("power");
        m_position = (Point3f) propList.getPoint3("position");
        m_direction = (Vector3f) propList.getVector3("direction");

        // cosine of the cut off angle of the spotlight (after this point the intensity is 0), deg -> rad
        m_cosTotalWidth = cos(M_PI / 180.0 * (float) propList.getFloat("cosTotalWidth"));
        // cosine of the start angle of the fall off (before this the intensity of the emitter is 100%), deg -> rad
        m_cosFalloffStart = cos(M_PI / 180.0 * (float) propList.getFloat("cosFalloffStart"));
    }

    // fill in the EmitterQueryRecord fields, and return the emitter value / the probability density value
    virtual Color3f sample(EmitterQueryRecord &lRec, const Point2f &sample) const {
        // sampled point on the emitter
        lRec.p = m_position;
        // normal at the emitter point (as it is a spotlight, the normal direction is the direction of the spotlight)
        lRec.n = m_direction.normalized();
        // direction between the hit point and the emitter point
        lRec.wi = (lRec.p - lRec.ref).normalized();
        // probability density value
        lRec.pdf = 1.f;
        // shadow ray from sampling origin to sampled point
        lRec.shadowRay = Ray3f(lRec.ref, lRec.wi, Epsilon, (lRec.p - lRec.ref).norm() - Epsilon);

        // intensity
        Color3f I = m_power / (4.0 * M_PI);
        // return intensity scaled by falloff and distance
        return I * falloff(-lRec.wi) / (lRec.ref - lRec.p).squaredNorm();
    }

    // the emitter value
    virtual Color3f eval(const EmitterQueryRecord &lRec) const {
        // From PBR Book:
        // The solid angle subtended by a cone with spread angle theta is 2pi(1-costheta).
        // Therefore, the integral over directions on the sphere that gives power from radiant intensity can be solved to compute the total power of a light that only emits illumination in a cone.
        // For the spotlight, we can reasonably approximate the power of the light by computing the solid angle of directions that is covered by the cone with a spread angle cosine halfway between falloffWidth and falloffStart.
        Color3f I = m_power / (4.0 * M_PI);
        return I * 2.0 * M_PI * (1 - 0.5 * (m_cosFalloffStart + m_cosTotalWidth));
    }

    // the probability density value
    virtual float pdf(const EmitterQueryRecord &lRec) const {
        return lRec.pdf;
    }

    // while the angle subtended from the direction of the beam is smaller than the fall off angle, the illumination is at full intensity, and after the subtended angle passes the total beam width, the illumination is zero. Between these two angles, there is a smooth transition between full intensity and zero intensity.
    float falloff(Vector3f w) const {
        float cosTheta = m_direction.normalized().dot(w.normalized());
        if (cosTheta < m_cosTotalWidth)     return 0.0;
        if (cosTheta > m_cosFalloffStart)   return 1.0;
        // smooth fall off from intensity 1 at cosFalloffStart and intensity 0 at cosTotalWidth
        float delta = (cosTheta - m_cosTotalWidth) / (m_cosFalloffStart - m_cosTotalWidth);
        // correct effects of cos
        // return (delta * delta) * (delta * delta);
        return delta * delta;
    }

    std::string toString() const {
        return "Spotlight[]";
    }

protected:
    Color3f m_power;
    Point3f m_position;
    Vector3f m_direction;

    float m_cosTotalWidth;
    float m_cosFalloffStart;
};

NORI_REGISTER_CLASS(Spotlight, "spotlight");
NORI_NAMESPACE_END
