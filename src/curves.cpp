#include <nori/shape.h>

NORI_NAMESPACE_BEGIN

struct CurveCommon;

// CurveType declarations - the shape I am interested in is "flat", which is often used to model hair and fur
enum class CurveType { Flat, Cylinder, Ribbon };

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
        // parametric range of values
        m_uMin = (float) propList.getFloat("uMin");
        m_uMax = (float) propList.getFloat("uMax");
    }




    virtual void addChild(NoriObject *child) override;

    /// Initialize internal data structures (called once by the XML parser)
    virtual void activate() override;

    //// Return an axis-aligned bounding box of the entire mesh
    const BoundingBox3f &getBoundingBox() const { return m_bbox; }

    /// Is this mesh an area emitter?
    bool isEmitter() const { return m_emitter != nullptr; }

    /// Return a pointer to an attached area emitter instance
    Emitter *getEmitter() { return m_emitter; }

    /// Return a pointer to an attached area emitter instance (const version)
    const Emitter *getEmitter() const { return m_emitter; }

    /// Return a pointer to the BSDF associated with this mesh
    const BSDF *getBSDF() const { return m_bsdf; }


    /// Return the total number of primitives in this shape
    virtual uint32_t getPrimitiveCount() const { return 1; }

    //// Return an axis-aligned bounding box containing the given triangle
    virtual BoundingBox3f getBoundingBox(uint32_t index) const = 0;

    //// Return the centroid of the given triangle
    virtual Point3f getCentroid(uint32_t index) const = 0;

    //// Ray-Shape intersection test
    virtual bool rayIntersect(uint32_t index, const Ray3f &ray, float &u, float &v, float &t) const = 0;

    /// Set the intersection information: hit point, shading frame, UVs, etc.
    virtual void setHitInformation(uint32_t index, const Ray3f &ray, Intersection & its) const = 0;

    /**
     * \brief Sample a point on the surface (potentially using the point sRec.ref to importance sample)
     * This method should set sRec.p, sRec.n and sRec.pdf
     * Probability should be with respect to area
     * */
    virtual void sampleSurface(ShapeQueryRecord & sRec, const Point2f & sample) const = 0;
    /**
     * \brief Return the probability of sampling a point sRec.p by the sampleSurface() method (sRec.ref should be set before)
     * sRec.n and sRec.pdf are ignored
     * */
    virtual float pdfSurface(const ShapeQueryRecord & sRec) const = 0;

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
};

NORI_REGISTER_CLASS(Curve, "curve");
NORI_NAMESPACE_END
