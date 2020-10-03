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

#include <nori/shape.h>
#include <nori/bsdf.h>
#include <nori/emitter.h>
#include <nori/warp.h>

NORI_NAMESPACE_BEGIN

class Sphere : public Shape {
public:
    Sphere(const PropertyList & propList) {
        m_position = propList.getPoint3("center", Point3f());
        m_radius = propList.getFloat("radius", 1.f);

        m_bbox.expandBy(m_position - Vector3f(m_radius));
        m_bbox.expandBy(m_position + Vector3f(m_radius));
    }

    virtual BoundingBox3f getBoundingBox(uint32_t index) const override { return m_bbox; }

    virtual Point3f getCentroid(uint32_t index) const override { return m_position; }

    virtual bool rayIntersect(uint32_t index, const Ray3f &ray, float &u, float &v, float &t) const override {
        // origin and direction of ray, respectively
        Point3f o = ray.o;
        Vector3f d = ray.d;

        // coefficients of quadratic formula for intersection between ray and sphere
        float a = d.dot(d);
        float b = 2 * (d.dot(o - m_position));
        float c = (o - m_position).dot(o - m_position) - m_radius*m_radius;

        // checking for intersections
        float discriminant = b*b - 4*a*c;

        // there are two intersections between the line equation of the ray and the sphere
        if (discriminant > 0) {
            float t_minus = (-b - sqrt(discriminant)) / (2*a);
            float t_plus = (-b + sqrt(discriminant)) / (2*a);

            // find the smallest real positive root in order to compute the intersection point
            // sqrt(discriminant) > 0, 2*a > 0 --> therefore t_plus > t_minus
            if (t_minus > 0) {
                if (t_minus > ray.mint && t_minus < ray.maxt) {
                    t = t_minus;
                    return true;
                }
            }

            else if (t_plus > 0) {
                if (t_plus > ray.mint && t_plus < ray.maxt) {
                    t = t_plus;
                    return true;
                }
            }
        }

        // ray is a tangent to the sphere
        else if (discriminant == 0) {
            float t_tangent = -b / (2*a);
            if (t_tangent > ray.mint && t_tangent < ray.maxt) {
                t = t_tangent;
                return true;
            }
        }

        //no intersection
        return false;
    }

    virtual void setHitInformation(uint32_t index, const Ray3f &ray, Intersection & its) const override {
        // intersection point
        its.p = ray.o + ray.d*its.t;

        // unit normal to the intersection point
        Vector3f n = (its.p - m_position).normalized();

        // geometric normal and shading normal is the same for an exact sphere
        its.geoFrame = Frame(n);
        its.shFrame = Frame(n);

        // 3D to 2D mapping - spherical coordinates of the intersection point linearly scaled to fit in [0,1]
        its.uv = sphericalCoordinates(n);
    }

    virtual void sampleSurface(ShapeQueryRecord & sRec, const Point2f & sample) const override {
        Vector3f q = Warp::squareToUniformSphere(sample);
        sRec.p = m_position + m_radius * q;
        sRec.n = q;
        sRec.pdf = std::pow(1.f/m_radius,2) * Warp::squareToUniformSpherePdf(Vector3f(0.0f,0.0f,1.0f));
    }
    virtual float pdfSurface(const ShapeQueryRecord & sRec) const override {
        return std::pow(1.f/m_radius,2) * Warp::squareToUniformSpherePdf(Vector3f(0.0f,0.0f,1.0f));
    }


    virtual std::string toString() const override {
        return tfm::format(
                "Sphere[\n"
                "  center = %s,\n"
                "  radius = %f,\n"
                "  bsdf = %s,\n"
                "  emitter = %s\n"
                "]",
                m_position.toString(),
                m_radius,
                m_bsdf ? indent(m_bsdf->toString()) : std::string("null"),
                m_emitter ? indent(m_emitter->toString()) : std::string("null"));
    }

protected:
    Point3f m_position;
    float m_radius;
};

NORI_REGISTER_CLASS(Sphere, "sphere");
NORI_NAMESPACE_END
