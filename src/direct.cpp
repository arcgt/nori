#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/bsdf.h>

NORI_NAMESPACE_BEGIN

class DirectIntegrator : public Integrator {
public:
    DirectIntegrator(const PropertyList &propList) {
        // parameters
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
        // get intersection information -> if no intersection, return
        Intersection its;
        if (!scene->rayIntersect(ray, its))
            return Color3f(0.0f);

        // create EmitterQueryRecord and sample for emitter sampler
        EmitterQueryRecord lRec;
        lRec.ref = its.p;
        Point2f sample;

        // get all light emitters in scene
        std::vector<Emitter *> lights = scene->getLights();

        // initialise for emitter sampler output - total incident radiance
        Color3f lTotal = 0.0f;

        for (int i = 0; i < lights.size(); ++i) {
            // sample incident radiance from point light
            Color3f lVal = lights[i]->sample(lRec, sample);

            // get cosine term between the shading normal and the direction towards the light source
            float cos = Frame::cosTheta(its.shFrame.toLocal(lRec.wi));

            // get bsdf term by contructing a BSDFQueryRecord with (wi, wo, measure) and calling bsdf->eval()
            BSDFQueryRecord bRec = BSDFQueryRecord(its.shFrame.toLocal(lRec.wi), its.shFrame.toLocal(-ray.d), ESolidAngle);
            Color3f bsdf = its.mesh->getBSDF()->eval(bRec);

            // check if there is interference from the point light to the surface
            bool interference = scene->rayIntersect(lRec.shadowRay, its);

            // add incident radiance from light i to total incident radiance
            lTotal += !interference * bsdf * lVal * sqrt(cos*cos);
        }

        return lTotal;
    }

    std::string toString() const {
        return "DirectIntegrator[]";
    }
};

NORI_REGISTER_CLASS(DirectIntegrator, "direct");
NORI_NAMESPACE_END
