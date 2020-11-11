#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/bsdf.h>
#include <nori/sampler.h>

NORI_NAMESPACE_BEGIN

class PathMatsIntegrator : public Integrator {
public:
    PathMatsIntegrator(const PropertyList &propList) {
      // no params
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
        // inital radiance and throughput
        Color3f Li = 0.0f;
        Color3f t = 1.0f;

        // success probability
        float p;

        // ray for recursion
        Ray3f rayR = ray;

        while (true) {
            // get intersection information -> if no intersection, return
            Intersection its;
            if (!scene->rayIntersect(rayR, its))
                return Li;

            // emitter
            if (its.mesh->isEmitter()) {
                EmitterQueryRecord lRecE = EmitterQueryRecord(rayR.o, its.p, its.shFrame.n);
                Li += t * its.mesh->getEmitter()->eval(lRecE);
            }

            // russian roulette
            p = std::min(t.x(), 0.99f);
            if (sampler->next1D() > p) {
                return Li;
            }
            else {
              t /= p;
            }

            // sampling bsdf
            BSDFQueryRecord bRec = BSDFQueryRecord(its.shFrame.toLocal(-rayR.d));
            bRec.uv = its.uv; // set uv coordinates
            Color3f bsdf = its.mesh->getBSDF()->sample(bRec, sampler->next2D());
            t *= bsdf;

            // reflected
            rayR = Ray3f(its.p, its.shFrame.toWorld(bRec.wo));
        }

        return Li;
    }

    std::string toString() const {
        return "PathMatsIntegrator[]";
    }
};

NORI_REGISTER_CLASS(PathMatsIntegrator, "path_mats");
NORI_NAMESPACE_END
