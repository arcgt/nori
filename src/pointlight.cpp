// PointLight class which derives from Emitter and implements an infinitesimal light source which emits light uniformly in all directions.

#include <nori/emitter.h>

NORI_NAMESPACE_BEGIN

class PointLight : public Emitter {
public:
    PointLight(const PropertyList &propList) {
        m_power = (Color3f) propList.getColor("power");
        m_position = (Point3f) propList.getPoint3("position");
    }

    // fill in the EmitterQueryRecord fields, and return the emitter value / the probability density value
    Color3f sample(EmitterQueryRecord &lRec, const Point2f &sample) const {
        // sampled point on the emitter
        lRec.p = m_position;
        // normal at the emitter point (as it is a point light, the normal direction is the direction of the ray)
        lRec.n = (lRec.ref - lRec.p).normalized();
        // direction between the hit point and the emitter point
        lRec.wi = (lRec.p - lRec.ref).normalized();
        // probability density value
        lRec.pdf = 1.f;
        // shadow ray from sampling origin to sampled point
        lRec.shadowRay = Ray3f(lRec.ref, lRec.wi, Epsilon, (lRec.p - lRec.ref).norm());

        // return emitter value / probability density value
        return eval(lRec) / pdf(lRec);
    }

    // the emitter value
    Color3f eval(const EmitterQueryRecord &lRec) const {
        // dividing radiant intensity by the squared distance from emitter
        return m_power / (4 * M_PI * (lRec.ref - lRec.p).squaredNorm());
    }

    // the probability density value
    float pdf(const EmitterQueryRecord &lRec) const {
        return lRec.pdf;
    }

    std::string toString() const {
        return "PointLight[]";
    }

protected:
    Color3f m_power;
    Point3f m_position;
};

NORI_REGISTER_CLASS(PointLight, "point");
NORI_NAMESPACE_END
