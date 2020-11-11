#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/bsdf.h>
#include <nori/sampler.h>

NORI_NAMESPACE_BEGIN

class DirectMatsIntegrator : public Integrator {
public:
    DirectMatsIntegrator(const PropertyList &propList) {
      // params
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
        // // get intersection information -> if no intersection, return
        Intersection its;
        if (!scene->rayIntersect(ray, its))
            return Color3f(0.0f);

        // initialise for emitter sampler output - total incident radiance
        Color3f lTotal = 0.0f;

        // emitter
        if (its.mesh->isEmitter()) {
            EmitterQueryRecord lRecE = EmitterQueryRecord(ray.o, its.p, its.shFrame.n);
            lTotal += its.mesh->getEmitter()->eval(lRecE);
        }

        // create a new record for sampling bsdf
        BSDFQueryRecord bRec = BSDFQueryRecord(its.shFrame.toLocal(-ray.d));
        bRec.uv = its.uv; // set uv coordinates
        Color3f bsdf = its.mesh->getBSDF()->sample(bRec, sampler->next2D());

        // reflected
        Ray3f rayR = Ray3f(its.p, its.shFrame.toWorld(bRec.wo));
        Intersection itsR;
        if (scene->rayIntersect(rayR, itsR)) {
          if (itsR.mesh->isEmitter()) {
              EmitterQueryRecord lRecR = EmitterQueryRecord(its.p, itsR.p, itsR.shFrame.n);
              lTotal += bsdf * itsR.mesh->getEmitter()->eval(lRecR);
          }
        }
        return lTotal;
    }

    std::string toString() const {
        return "DirectMatsIntegrator[]";
    }
};

NORI_REGISTER_CLASS(DirectMatsIntegrator, "direct_mats");
NORI_NAMESPACE_END
