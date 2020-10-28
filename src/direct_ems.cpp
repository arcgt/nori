#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/bsdf.h>
#include <nori/sampler.h>

NORI_NAMESPACE_BEGIN

class DirectEmsIntegrator : public Integrator {
public:
    DirectEmsIntegrator(const PropertyList &propList) {
        // params
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
        // get intersection information -> if no intersection, return
        Intersection its;
        if (!scene->rayIntersect(ray, its))
            return Color3f(0.0f);

        // initialise for emitter sampler output - total incident radiance
        Color3f lTotal = 0.0f;

        // incidence radience from emitter
        if (its.mesh->isEmitter()) {
            EmitterQueryRecord lRecE = EmitterQueryRecord(ray.o, its.p, its.shFrame.n);
            lTotal += its.mesh->getEmitter()->eval(lRecE);
        }

        // get all light emitters in scene
        std::vector<Emitter *> lights = scene->getLights();

        for (int i = 0; i < lights.size(); ++i) {
            // sample incident radiance from reflected
            EmitterQueryRecord lRec;
            lRec.ref = its.p;
            Color3f lVal = lights[i]->sample(lRec, sampler->next2D());

            // get cosine term between the shading normal and the direction towards the light source
            float cos = Frame::cosTheta(its.shFrame.toLocal(lRec.wi));

            // get bsdf term by contructing a BSDFQueryRecord with (wi, wo, measure) and calling bsdf->eval()
            BSDFQueryRecord bRec = BSDFQueryRecord(its.shFrame.toLocal(-ray.d), its.shFrame.toLocal(lRec.wi), ESolidAngle);
            bRec.uv = its.uv; // set uv coordinates
            Color3f bsdf = its.mesh->getBSDF()->eval(bRec);

            // check if there is interference from the point light to the surface
            bool interference = scene->rayIntersect(lRec.shadowRay);

            // add incident radiance from light i to total incident radiance
            lTotal += !interference * bsdf * lVal * cos;
        }

        return lTotal;
    }

    std::string toString() const {
        return "DirectEmsIntegrator[]";
    }
};

NORI_REGISTER_CLASS(DirectEmsIntegrator, "direct_ems");
NORI_NAMESPACE_END
