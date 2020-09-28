// An integrator, which computes the average visibility at every surface point visible to the camera.

#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/warp.h>

NORI_NAMESPACE_BEGIN

class AvIntegrator : public Integrator {
public:
    AvIntegrator(const PropertyList &propList) {
        m_length = (float) propList.getFloat("length");
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
        // finding the surface intersected by the camera ray
        Intersection its;

        // if there is no intersection
        if (!scene->rayIntersect(ray, its))
            return Color3f(1.0f);

        // if there is intersection, compute average visibility by generating a point on the hemisphere and tracing a ray into this direction
        Point3f p = its.p; // the intersection point
        Normal3f n = its.shFrame.n; // the world space shading normal
        Vector3f v = Warp::sampleUniformHemisphere(sampler, n); // a uniformly distributed random vector on the surface of a unit hemisphere oriented in the direction of the normal

        // new ray struct with position p, direction v, min. pos. epsilon and max. pos. m_length
        Ray3f m_ray(p, v, Epsilon, m_length);

        // if there is no intersection
        if (!scene->rayIntersect(m_ray, its))
            return Color3f(1.0f);

        // if there is intersection
        return Color3f(0.0f);
    }

    std::string toString() const {
        return "AvIntegrator[]";
    }

protected:
    float m_length;
};

NORI_REGISTER_CLASS(AvIntegrator, "av");
NORI_NAMESPACE_END
