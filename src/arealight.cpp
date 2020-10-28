/*
    This file is part of Nori, a simple educational ray tracer

    Copyright (c) 2015 by Romain Prévost

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

#include <nori/emitter.h>
#include <nori/warp.h>
#include <nori/shape.h>

NORI_NAMESPACE_BEGIN

class AreaEmitter : public Emitter {
public:
    AreaEmitter(const PropertyList &props) {
        m_radiance = props.getColor("radiance");
    }

    virtual std::string toString() const override {
        return tfm::format(
                "AreaLight[\n"
                "  radiance = %s,\n"
                "]",
                m_radiance.toString());
    }

    virtual Color3f eval(const EmitterQueryRecord & lRec) const override {
        if(!m_shape)
            throw NoriException("There is no shape attached to this Area light!");

        // if the front side of the emissive shape is intersected
        if ((-lRec.wi).dot(lRec.n) >= 0) {
            return m_radiance;
        }
        // otherwise
        return 0;
    }

    virtual Color3f sample(EmitterQueryRecord & lRec, const Point2f & sample) const override {
        if(!m_shape)
            throw NoriException("There is no shape attached to this Area light!");

        /**
         * \brief Sample a point on the surface (potentially using the point sRec.ref to importance sample)
         * This method should set sRec.p, sRec.n and sRec.pdf
         * Probability should be with respect to area
         * */
        ShapeQueryRecord sRec;
        m_shape->sampleSurface(sRec, sample);

        // see pointlight.cpp or emitter.h for comments
        lRec.p = sRec.p;
        lRec.n = sRec.n;
        lRec.wi = (lRec.p - lRec.ref).normalized();
        lRec.pdf = sRec.pdf;
        lRec.shadowRay = Ray3f(lRec.ref, lRec.wi, Epsilon, (lRec.p - lRec.ref).norm() - Epsilon);

        // return emitter value / probability density value
        if (pdf(lRec) > 0) {
            return eval(lRec) / pdf(lRec);
        }

        return 0;
    }

    virtual float pdf(const EmitterQueryRecord &lRec) const override {
        if(!m_shape)
            throw NoriException("There is no shape attached to this Area light!");

        // define the shape query record
        ShapeQueryRecord sRec;
        sRec.ref = lRec.ref;
        sRec.p = lRec.p;

        // costheta
        float cos = (-lRec.wi).dot(lRec.n);

        // if front facing surface encountered
        if (cos > 0) {
            /**
             * \brief Return the probability of sampling a point sRec.p by the sampleSurface() method (sRec.ref should be set before)
             * sRec.n and sRec.pdf are ignored
             * */

            //pdf converted to solid angle measure
            return m_shape->pdfSurface(sRec) * (sRec.p - sRec.ref).squaredNorm() / cos;
        }

        // if back-facing surface encountered
        return 0;

    }


    virtual Color3f samplePhoton(Ray3f &ray, const Point2f &sample1, const Point2f &sample2) const override {
        throw NoriException("To implement...");
    }


protected:
    Color3f m_radiance;
};

NORI_REGISTER_CLASS(AreaEmitter, "area")
NORI_NAMESPACE_END
