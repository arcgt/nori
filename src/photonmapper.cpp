/*
    This file is part of Nori, a simple educational ray tracer

    Copyright (c) 2015 by Wenzel Jakob

    Nori is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    Nori is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <nori/integrator.h>
#include <nori/sampler.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>
#include <nori/scene.h>
#include <nori/photon.h>

NORI_NAMESPACE_BEGIN

class PhotonMapper : public Integrator {
public:
    /// Photon map data structure
    typedef PointKDTree<Photon> PhotonMap;

    PhotonMapper(const PropertyList &props) {
        /* Lookup parameters */
        m_photonCount  = props.getInteger("photonCount", 1000000);
        m_photonRadius = props.getFloat("photonRadius", 0.0f /* Default: automatic */);
    }

    virtual void preprocess(const Scene *scene) override {
        cout << "Gathering " << m_photonCount << " photons .. ";
        cout.flush();

        /* Create a sample generator for the preprocess step */
        Sampler *sampler = static_cast<Sampler *>(
            NoriObjectFactory::createInstance("independent", PropertyList()));

        /* Allocate memory for the photon map */
        m_photonMap = std::unique_ptr<PhotonMap>(new PhotonMap());
        m_photonMap->reserve(m_photonCount);

    		/* Estimate a default photon radius */
    		if (m_photonRadius == 0)
    			m_photonRadius = scene->getBoundingBox().getExtents().norm() / 500.0f;

    		/* How to add a photon?
    		 * m_photonMap->push_back(Photon(
    		 *	Point3f(0, 0, 0),  // Position
    		 *	Vector3f(0, 0, 1), // Direction
    		 *	Color3f(1, 2, 3)   // Power
    		 * ));
    		 */

    		// put your code to trace photons here

        for (int i = 0; i < m_photonCount; ++i) {
            // sample photon on random emitter
            const Emitter * light = scene->getRandomEmitter(sampler->next1D());
            Ray3f ray;
            Color3f W = light->samplePhoton(ray, sampler->next2D(), sampler->next2D()) * scene->getLights().size(); // power

            // success probability
            float p;

            while (true) {
                // get intersection information -> if no intersection, return
                Intersection its;
                if (!scene->rayIntersect(ray, its))
                    break;

                // if surface is diffuse
                if (its.mesh->getBSDF()->isDiffuse()) {
                    // deposit photon
                    m_photonMap->push_back(Photon(its.p, -ray.d, W));
                }

                // russian roulette
                p = std::min(W.x(), 0.99f);
                if (sampler->next1D() > p) {
                    break;
                }
                else {
                  W /= p;
                }

                // sampling bsdf
                BSDFQueryRecord bRec = BSDFQueryRecord(its.shFrame.toLocal(-ray.d));
                bRec.uv = its.uv; // set uv coordinates
                Color3f bsdf = its.mesh->getBSDF()->sample(bRec, sampler->next2D());
                W *= bsdf;

                // recursion
                ray = Ray3f(its.p, its.shFrame.toWorld(bRec.wo));
            }
        }

		    /* Build the photon map */
        m_photonMap->build();
    }

    virtual Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &_ray) const override {

    		/* How to find photons?
    		 * std::vector<uint32_t> results;
    		 * m_photonMap->search(Point3f(0, 0, 0), // lookup position
    		 *                     m_photonRadius,   // search radius
    		 *                     results);
    		 *
    		 * for (uint32_t i : results) {
    		 *    const Photon &photon = (*m_photonMap)[i];
    		 *    cout << "Found photon!" << endl;
    		 *    cout << " Position  : " << photon.getPosition().toString() << endl;
    		 *    cout << " Power     : " << photon.getPower().toString() << endl;
    		 *    cout << " Direction : " << photon.getDirection().toString() << endl;
    		 * }
    		 */

    		// put your code for path tracing with photon gathering here

        // inital radiance and throughput
        Color3f Li = 0.0f;
        Color3f t = 1.0f;

        // success probability
        float p;

        // ray for recursion
        Ray3f rayR = _ray;

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

            // if surface is diffuse
            if (its.mesh->getBSDF()->isDiffuse()) {
                Color3f Lr = 0;
                std::vector<uint32_t> results;
                m_photonMap->search(its.p, m_photonRadius, results);
                for (uint32_t i : results) {
            		    const Photon &photon = (*m_photonMap)[i];
                    BSDFQueryRecord bRec = BSDFQueryRecord(its.shFrame.toLocal(-rayR.d), its.shFrame.toLocal(photon.getDirection()), ESolidAngle);
                    Lr += its.mesh->getBSDF()->eval(bRec) * photon.getPower();
          		  }

                Li += t * ((Lr * INV_PI) / (m_photonRadius * m_photonRadius * m_photonCount));
                return Li;
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

            // recursion
            rayR = Ray3f(its.p, its.shFrame.toWorld(bRec.wo));
        }

    		return Li;
    }

    virtual std::string toString() const override {
        return tfm::format(
            "PhotonMapper[\n"
            "  photonCount = %i,\n"
            "  photonRadius = %f\n"
            "]",
            m_photonCount,
            m_photonRadius
        );
    }
private:
    /*
     * Important: m_photonCount is the total number of photons deposited in the photon map,
     * NOT the number of emitted photons. You will need to keep track of those yourself.
     */
    int m_photonCount;
    float m_photonRadius;
    std::unique_ptr<PhotonMap> m_photonMap;
};

NORI_REGISTER_CLASS(PhotonMapper, "photonmapper");
NORI_NAMESPACE_END
