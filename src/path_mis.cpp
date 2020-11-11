#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/bsdf.h>
#include <nori/sampler.h>

NORI_NAMESPACE_BEGIN

class PathMisIntegrator : public Integrator {
public:
  PathMisIntegrator(const PropertyList &propList) {
    // no params
  }

  Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
      // initial radiance, throughput, success probability, recursion ray
      Color3f Li = 0.0f;
      Color3f t = 1.0f;
      float p = 1.0f;
      Ray3f rayR = ray;

      // initialise weights
      float wmats = 1.0f;
      float wems = 0.0f;

      // get intersection information -> if no intersection, return
      Intersection its;
      if (!scene->rayIntersect(rayR, its))
          return Li;

      while (true) {
          // --- emitted ---
          if (its.mesh->isEmitter()) {
              EmitterQueryRecord lRecE = EmitterQueryRecord(rayR.o, its.p, its.shFrame.n);
              Li += wmats * t * its.mesh->getEmitter()->eval(lRecE); // contribution from mats
          }

          // --- russian roulette ---
          p = std::min(t.x(), 0.99f);
          if (sampler->next1D() > p) {
              return Li;
          }
          else {
            t /= p;
          }

          // --- ems contribution ---
          float pdfEms, pdfMats = 0.0f;

          // get all light emitters in scene
          std::vector<Emitter *> lights = scene->getLights();

          for (int i = 0; i < lights.size(); ++i) {
              // sample incident radiance from reflected
              EmitterQueryRecord lRecR_ems;
              lRecR_ems.ref = its.p;
              Color3f lVal = lights[i]->sample(lRecR_ems, sampler->next2D());
              pdfEms = lights[i]->pdf(lRecR_ems);

              // get cosine term between the shading normal and the direction towards the light source
              float cos = Frame::cosTheta(its.shFrame.toLocal(lRecR_ems.wi));

              // get bsdf term by contructing a BSDFQueryRecord with (wi, wo, measure) and calling bsdf->eval()
              BSDFQueryRecord bRec = BSDFQueryRecord(its.shFrame.toLocal(-rayR.d), its.shFrame.toLocal(lRecR_ems.wi), ESolidAngle);
              bRec.uv = its.uv; // set uv coordinates
              Color3f bsdf = its.mesh->getBSDF()->eval(bRec);
              pdfMats = its.mesh->getBSDF()->pdf(bRec);

              // check if there is interference from the point light to the surface
              bool interference = scene->rayIntersect(lRecR_ems.shadowRay);
              float interferencef = static_cast<float>(!interference);

              // ems weight
              wems = (pdfEms + pdfMats > 0) ? (pdfEms / (pdfEms + pdfMats)) : pdfEms;

              // add incident radiance from light i to total incident radiance
              Li += interferencef * t * bsdf * lVal * cos * wems;
          }

          // --- sampling bsdf ---
          BSDFQueryRecord bRec = BSDFQueryRecord(its.shFrame.toLocal(-rayR.d));
          bRec.uv = its.uv; // set uv coordinates
          Color3f bsdf = its.mesh->getBSDF()->sample(bRec, sampler->next2D());
          t *= bsdf;

          // update ray for recursion
          rayR = Ray3f(its.p, its.shFrame.toWorld(bRec.wo));

          // --- calculate mats weight for next iteration ---
          pdfEms, pdfMats = 0.0f;
          pdfMats = its.mesh->getBSDF()->pdf(bRec);

          Point3f o = its.p;
          // get intersection information -> if no intersection, return
          if (!scene->rayIntersect(rayR, its))
              return Li;

          if (its.mesh->isEmitter()) {
              EmitterQueryRecord lRecR_mats = EmitterQueryRecord(o, its.p, its.shFrame.n);
              pdfEms = its.mesh->getEmitter()->pdf(lRecR_mats);
          }

          wmats = (pdfMats + pdfEms > 0) ? (pdfMats / (pdfMats + pdfEms)) : pdfMats;

          // --- check if bsdf consists of delta functions ---
          if (bRec.measure == EDiscrete) {
              wmats = 1.0f;
              wems = 0.0f;
          }
      }
      return Li;
  }

  std::string toString() const {
      return "PathMisIntegrator[]";
  }
};

NORI_REGISTER_CLASS(PathMisIntegrator, "path_mis");
NORI_NAMESPACE_END
