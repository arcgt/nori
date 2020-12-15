#include <nori/shape.h>
#include <nori/transform.h>

NORI_NAMESPACE_BEGIN

struct CurveCommon;

// CurveType declarations - the shape I am interested in is "flat", which is often used to model hair and fur
enum class CurveType { Flat, Cylinder, Ribbon };

// The CurveCommon constructor mostly just initializes member variables with values passed into it for the control points, the curve width, etc. The control points provided to it should be in the curve’s object space.
struct CurveCommon {
    CurveCommon(const Point3f c[4], float w0, float w1, CurveType type, const Normal3f *norm);
    const CurveType type;
    Point3f cpObj[4];
    float width[2];
    Normal3f n[2];
    float normalAngle, invSinNormalAngle;
};

class Curve : public Shape {
public:
    Curve(const PropertyList &propList) {
        // const std::shared_ptr<CurveCommon> &common

        // parametric range of values
        m_uMin = (float) propList.getFloat("uMin");
        m_uMax = (float) propList.getFloat("uMax");
    }

    // linearly interpolates between the two provided values
    float Lerp(float t, float v1, float v2) {
        return (1 - t) * v1 + t * v2;
    }

    // computes seven control points: the first four correspond to the control points for the first half of the split curve, and the last four (starting with the last control point of the first half) correspond to the control points for the second half.
    inline void SubdivideBezier(const Point3f cp[4], Point3f cpSplit[7]) {
        cpSplit[0] = cp[0];
        cpSplit[1] = (cp[0] + cp[1]) / 2;
        cpSplit[2] = (cp[0] + 2 * cp[1] + cp[2]) / 4;
        cpSplit[3] = (cp[0] + 3 * cp[1] + 3 * cp[2] + cp[3]) / 8;
        cpSplit[4] = (cp[1] + 2 * cp[2] + cp[3]) / 4;
        cpSplit[5] = (cp[2] + cp[3]) / 2;
        cpSplit[6] = cp[3];
    }

    // omputes the blossom p(u, u, u) to evaluate a point on a Bézier spline. It optionally also returns the derivative of the curve at the point.
    static Point3f EvalBezier(const Point3f cp[4], Float u, Vector3f *deriv = nullptr) {
        Point3f cp1[3] = { Lerp(u, cp[0], cp[1]),
                           Lerp(u, cp[1], cp[2]),
                           Lerp(u, cp[2], cp[3]) };
        Point3f cp2[2] = { Lerp(u, cp1[0], cp1[1]),
                           Lerp(u, cp1[1], cp1[2]) };
        if (deriv)
            *deriv = (float)3 * (cp2[1] - cp2[0]);
        return Lerp(u, cp2[0], cp2[1]);
    }

    // construct a local coordinate system given only a single 3D vector
    void CoordinateSystem(const Vector3f &v1, Vector3f *v2, Vector3f *v3) {
        if (std::abs(v1.x()) > std::abs(v1.y()))
            *v2 = Vector3f(-v1.z(), 0, v1.x()) / std::sqrt(v1.x() * v1.x() + v1.z() * v1.z());
        else
            *v2 = Vector3f(0, v1.z(), -v1.y()) / std::sqrt(v1.y() * v1.y() + v1.z() * v1.z());
        *v3 = v1.cross(*v2);
    }

    // gives a transformation between camera space and world space
    Transform LookAt(const Point3f &pos, const Point3f &look, const Vector3f &up) {
        Eigen::Matrix4f cameraToWorld;
        // initialize fourth column of viewing matrix
        cameraToWorld[0][3] = pos.x();
        cameraToWorld[1][3] = pos.y();
        cameraToWorld[2][3] = pos.z();
        cameraToWorld[3][3] = 1;
        // initialize first three columns of viewing matrix
        Vector3f dir = (look - pos).normalized();
        Vector3f right = (Cross(Normalize(up), dir)).normalized();
        Vector3f newUp = dir.cross(right);
        cameraToWorld[0][0] = right.x();
        cameraToWorld[1][0] = right.y();
        cameraToWorld[2][0] = right.z();
        cameraToWorld[3][0] = 0.;
        cameraToWorld[0][1] = newUp.x();
        cameraToWorld[1][1] = newUp.y();
        cameraToWorld[2][1] = newUp.z();
        cameraToWorld[3][1] = 0.;
        cameraToWorld[0][2] = dir.x();
        cameraToWorld[1][2] = dir.y();
        cameraToWorld[2][2] = dir.z();
        cameraToWorld[3][2] = 0.;

        return Transform(cameraToWorld, cameraToWorld.getInverseMatrix());
    }

    // clamps the given value val to lie between the values low and high
    float Clamp(float val, float low, float high) {
        if (val < low) return low;
        else if (val > high) return high;
        else return val;
    }

    // bezier curves lie with the convex hull of their control points
    // bounding box of control points gives a conservative bound of underlying curve
    // compute bouning box of control points of curve segment to bound spline along center of curves
    // bounds then expanded by half the max width to get 3D bounds of shape that cuve represents
    BoundingBox3f Curve::ObjectBound() const {
        // compute object-space control points for curve segment, cpObj
        Point3f cpObj[4];
        cpObj[0] = BlossomBezier(m_common->cpObj, m_uMin, m_uMin, m_uMin);
        cpObj[1] = BlossomBezier(m_common->cpObj, m_uMin, m_uMin, m_uMax);
        cpObj[2] = BlossomBezier(m_common->cpObj, m_uMin, m_uMax, m_uMax);
        cpObj[3] = BlossomBezier(m_common->cpObj, m_uMax, m_uMax, m_uMax);

        BoundingBox3f b = Union(BoundingBox3f(cpObj[0], cpObj[1]), BoundingBox3f(cpObj[2], cpObj[3]));
        float width[2] = { Lerp(m_uMin, m_common->width[0], m_common->width[1]), Lerp(m_uMax, m_common->width[0], m_common->width[1]) };
        return Expand(b, std::max(width[0], width[1]) * 0.5f));
    }

    // The blossom p(u0, u1, u2) of a cubic Bezier spline is defined by three stages of linear interpolation, starting with the original control points
    static Point3f BlossomBezier(const Point3f p[4], float u0, float u1, float u2) {
        Point3f a[3] = {
            Lerp(u0, p[0], p[1]),
            Lerp(u0, p[1], p[2]),
            Lerp(u0, p[2], p[3])
        };
        Point3f b[2] = {
            Lerp(u1, a[0], a[1]),
            Lerp(u1, a[1], a[2])
        };
        return Lerp(u2, b[0], b[1]);
    }

    // The Curve intersection algorithm is based on discarding curve segments as soon as it can be determined that the ray definitely doesn’t intersect them and otherwise recursively splitting the curve in half to create two smaller segments that are then tested. Eventually, the curve is linearly approximated for an efficient intersection test. After some preparation, the recursiveIntersect() call starts this process with the full segment that the Curve represents.
    bool Curve::Intersect(const Ray3f &r, float *tHit, Intersection *isect, bool testAlphaTexture) const {
        // transform ray to object space
        Ray3f ray;
        ray.o = *isect.shFrame.toLocal(r.o);
        ray.d = *isect.shFrame.toLocal(r.d);


        // compute object-space control points for curve segment, cpObj
        Point3f cpObj[4];
        cpObj[0] = BlossomBezier(m_common->cpObj, m_uMin, m_uMin, m_uMin);
        cpObj[1] = BlossomBezier(m_common->cpObj, m_uMin, m_uMin, m_uMax);
        cpObj[2] = BlossomBezier(m_common->cpObj, m_uMin, m_uMax, m_uMax);
        cpObj[3] = BlossomBezier(m_common->cpObm_j, m_uMax, m_uMax, m_uMax);

        // project curve control points to plane perpendicular to ray
        Vector3f dx, dy;
        CoordinateSystem(ray.d, &dx, &dy);
        Transform objectToRay = LookAt(ray.o, ray.o + ray.d, dx); //***
        Point3f cp[4] = { objectToRay(cpObj[0]), objectToRay(cpObj[1]), objectToRay(cpObj[2]), objectToRay(cpObj[3]) };

        // compute refinement depth for curve, maxDepth
        float L0 = 0;
        for (int i = 0; i < 2; ++i)
            L0 = std::max(L0, std::max(std::max(std::abs(cp[i].x() - 2 * cp[i + 1].x() + cp[i + 2].x()),
                                                std::abs(cp[i].y() - 2 * cp[i + 1].y() + cp[i + 2].y())),
                                                std::abs(cp[i].z() - 2 * cp[i + 1].z() + cp[i + 2].z())));
        float eps = std::max(m_common->width[0], m_common->width[1]) * .05f; // width / 20
        float fr0 = std::log(1.41421356237f * 12.f * L0 / (8.f * eps)) * 0.7213475108f;
        int r0 = (int) std::round(fr0);
        int maxDepth = Clamp(r0, 0, 10); // ***

        return recursiveIntersect(ray, tHit, isect, cp, objectToRay.getInverseMatrix(), m_uMin, m_uMax, maxDepth); //**
    }

    bool Curve::recursiveIntersect(const Ray3f &ray, float *tHit, Intersection *isect, const Point3f cp[4], const Transform &rayToObject, float u0, float u1, int depth) const {
        // try to cull curve segment versus ray

        //compute bounding boxes of curve segment, curveBounds
        BoundingBox3f curveBounds = Union(BoundingBox3f(cp[0], cp[1]), BoundingBox3f(cp[2], cp[3]));
        Float maxWidth = std::max(Lerp(u0, m_common->width[0], m_common->width[1]),
                                  Lerp(u1, m_common->width[0], m_common->width[1]));
        curveBounds = Expand(curveBounds, 0.5 * maxWidth);

        // compute bounding box of ray, rayBounds
        float rayLength = ray.d.norm();
        float zMax = rayLength * ray.tMax;
        BoundingBox3f rayBounds(Point3f(0, 0, 0), Point3f(0, 0, zMax)); //**

        if (Overlaps(curveBounds, rayBounds) == false)
            return false;

        if (depth > 0) {
            // split curve segment into sub-segments and test for intersection
            float uMid = 0.5f * (u0 + u1);
            Point3f cpSplit[7];
            SubdivideBezier(cp, cpSplit);
            return (recursiveIntersect(ray, tHit, isect, &cpSplit[0], rayToObject, u0, uMid, depth - 1) ||
                    recursiveIntersect(ray, tHit, isect, &cpSplit[3], rayToObject, uMid, u1, depth - 1));
        } else {
            // intersect ray with curve segment

            // test ray against segment endpoint boundaries
            // test sample point against tangent perpendicular at curve start
            float edge = (cp[1].y() - cp[0].y()) * -cp[0].y() + cp[0].x() * (cp[0].x() - cp[1].x());
            if (edge < 0)
                return false;
            // test sample point against tangent perpendicular at curve end
            edge = (cp[2].y() - cp[3].y()) * -cp[3].y() + cp[3].x() * (cp[3].x() - cp[2].x());
            if (edge < 0)
                return false;

            // compute line w that gives minimum distance to sample point
            Vector2f segmentDirection = Point2f(cp[3]) - Point2f(cp[0]);
            float denom = segmentDirection.squaredNorm();
            if (denom == 0)
                return false;
            float w = -Vector2f(cp[0]).dot(segmentDirection) / denom;

            // compute u coordinate of curve intersection point and hitWidth
            float u = Clamp(Lerp(w, u0, u1), u0, u1);
            float hitWidth = Lerp(u, m_common->width[0], m_common->width[1]);
            Normal3f nHit;
            if (m_common->type == CurveType::Ribbon) {
                // scale hitWidth based on ribbon orientation
                float sin0 = std::sin((1 - u) * m_common->normalAngle) * m_common->invSinNormalAngle;
                float sin1 = std::sin(u * m_common->normalAngle) * m_common->invSinNormalAngle;
                nHit = sin0 * m_common->n[0] + sin1 * m_common->n[1];
                hitWidth *= std::abs(nHit.dot(ray.d)) / rayLength;
            }

            // test intersection point against curve hitWidth
            Vector3f dpcdw;
            Point3f pc = EvalBezier(cp, Clamp(w, 0, 1), &dpcdw);
            float ptCurveDist2 = pc.x() * pc.x() + pc.y() * pc.y();
            if (ptCurveDist2 > hitWidth * hitWidth * .25)
                return false;
            if (pc.z() < 0 || pc.z() > zMax)
                return false;

            // compute v coordinate of curve intersection point
            float ptCurveDist = std::sqrt(ptCurveDist2);
            float edgeFunc = dpcdw.x() * -pc.y() + pc.x() * dpcdw.y();
            float v = (edgeFunc > 0) ? 0.5f + ptCurveDist / hitWidth : 0.5f - ptCurveDist / hitWidth;

            // compute hit t and partial derivatives for curve intersection
            if (tHit != nullptr) {
                *tHit = pc.z / rayLength;
                // compute error bounds for curve intersection
                Vector3f pError(2 * hitWidth, 2 * hitWidth, 2 * hitWidth);
                // compute dp/du and dp/dv for curve intersection
                Vector3f dpdu, dpdv;
                EvalBezier(common->cpObj, u, &dpdu);
                if (common->type == CurveType::Ribbon)
                    dpdv = Normalize(Cross(nHit, dpdu)) * hitWidth;
                else {
                    // compute curve dp/dv for flat and cylinder curves
                    Vector3f dpduPlane = (rayToObject.getInverseMatrix())(dpdu);
                    Vector3f dpdvPlane = Normalize(Vector3f(-dpduPlane.y, dpduPlane.x, 0)) * hitWidth;
                    if (common->type == CurveType::Cylinder) {
                        // rotate dpdvPlane to give cylindrical appearance
                        float theta = Lerp(v, -90., 90.);
                        Transform rot = Rotate(-theta, dpduPlane);
                        dpdvPlane = rot(dpdvPlane);
                    }
                    dpdv = rayToObject(dpdvPlane);
                }
                *isect = (*ObjectToWorld)(SurfaceInteraction(ray(pc.z), pError, Point2f(u, v), -ray.d, dpdu, dpdv, Normal3f(0, 0, 0), Normal3f(0, 0, 0), ray.time, this));
            }

            return true;
        }

    }

    //// Return an axis-aligned bounding box of the entire mesh
    const BoundingBox3f &getBoundingBox() const { return m_bbox; }


    /// Return the total number of primitives in this shape
    virtual uint32_t getPrimitiveCount() const { return 1; }

    //// Return an axis-aligned bounding box containing the given triangle
    virtual BoundingBox3f getBoundingBox(uint32_t index) const {
    }

    //// Return the centroid of the given triangle
    virtual Point3f getCentroid(uint32_t index) const {
    }

    //// Ray-Shape intersection test
    virtual bool rayIntersect(uint32_t index, const Ray3f &ray, float &u, float &v, float &t) const {
    }

    /// Set the intersection information: hit point, shading frame, UVs, etc.
    virtual void setHitInformation(uint32_t index, const Ray3f &ray, Intersection & its) const {
    }

    /**
     * \brief Sample a point on the surface (potentially using the point sRec.ref to importance sample)
     * This method should set sRec.p, sRec.n and sRec.pdf
     * Probability should be with respect to area
     * */
    virtual void sampleSurface(ShapeQueryRecord & sRec, const Point2f & sample) const {
    }
    /**
     * \brief Return the probability of sampling a point sRec.p by the sampleSurface() method (sRec.ref should be set before)
     * sRec.n and sRec.pdf are ignored
     * */
    virtual float pdfSurface(const ShapeQueryRecord & sRec) const {
    }

    /**
     * \brief Return the type of object (i.e. Mesh/BSDF/etc.)
     * provided by this instance
     * */
    virtual EClassType getClassType() const override { return EMesh; }

    virtual std::string toString() const {
        return "Curve[]";
    }
private:
    const std::shared_ptr<CurveCommon> m_common;
    const float m_uMin, m_uMax;
    const Transform *ObjectToWorld, *WorldToObject;
};

NORI_REGISTER_CLASS(Curve, "curve");
NORI_NAMESPACE_END
