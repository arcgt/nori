#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/bsdf.h>
#include <nori/sampler.h>

NORI_NAMESPACE_BEGIN

class DirectMisIntegrator : public Integrator {
public:
  DirectMisIntegrator(const PropertyList &propList) {
    // params
  }

  Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
      // get intersection information -> if no intersection, return
      Intersection its;
      if (!scene->rayIntersect(ray, its))
          return Color3f(0.0f);

      // initialise for total output
      Color3f lTotal = 0.0f;

      // incident radience from emitter
      Color3f Le = 0.0f;
      if (its.mesh->isEmitter()) {
          EmitterQueryRecord lRecE = EmitterQueryRecord(ray.o, its.p, its.shFrame.n);
          Le += its.mesh->getEmitter()->eval(lRecE);
      }

      // ---- ems ----

      Color3f Lems = 0.0f;
      float pdfEms, pdfMats = 0.0f;
      float wems = 0.0f;

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
          BSDFQueryRecord bRec = BSDFQueryRecord(its.shFrame.toLocal(-ray.d), its.shFrame.toLocal(lRecR_ems.wi), ESolidAngle);
          bRec.uv = its.uv; // set uv coordinates
          Color3f bsdf = its.mesh->getBSDF()->eval(bRec);
          pdfMats = its.mesh->getBSDF()->pdf(bRec);

          // check if there is interference from the point light to the surface
          bool interference = scene->rayIntersect(lRecR_ems.shadowRay);

          if (pdfEms + pdfMats > 0) {
              wems = pdfEms / (pdfEms + pdfMats);
          } else {
              wems = pdfEms;
          }
          // add incident radiance from light i to total incident radiance
          Lems += !interference * bsdf * lVal * cos * wems;
      }

      // ---- mats ----

      Color3f Lmats = 0.0f;
      pdfEms, pdfMats = 0.0f;
      float wmats = 0.0f;

      // get bsdf term by contructing a BSDFQueryRecord with (wi) and drawing a sample from the BRDF model
      BSDFQueryRecord bRec_mats = BSDFQueryRecord(its.shFrame.toLocal(-ray.d));
      bRec_mats.uv = its.uv; // set uv coordinates
      Color3f bsdf = its.mesh->getBSDF()->sample(bRec_mats, sampler->next2D());
      pdfMats = its.mesh->getBSDF()->pdf(bRec_mats);

      //incidence radiance from reflected
      Color3f lValm = 0.0f;
      Ray3f rayR = Ray3f(its.p, its.shFrame.toWorld(bRec_mats.wo));
      Intersection itsR;
      if (scene->rayIntersect(rayR, itsR)) {
          if (itsR.mesh->isEmitter()) {
              EmitterQueryRecord lRecR_mats = EmitterQueryRecord(its.p, itsR.p, itsR.shFrame.n);
              lValm = bsdf * itsR.mesh->getEmitter()->eval(lRecR_mats);
              pdfEms = itsR.mesh->getEmitter()->pdf(lRecR_mats);
          }
      }

      if (pdfMats + pdfEms > 0) {
          wmats = pdfMats / (pdfMats + pdfEms);
      } else {
          wmats = pdfMats;
      }

      Lmats = lValm * wmats;
      lTotal = Le + Lems + Lmats;

      return lTotal;
  }

  std::string toString() const {
      return "DirectMisIntegrator[]";
  }
};

NORI_REGISTER_CLASS(DirectMisIntegrator, "direct_mis");
NORI_NAMESPACE_END
