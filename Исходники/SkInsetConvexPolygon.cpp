// Compute the intersection 'p' between segments s0 and s1, if any.
// 's' is the parametric value for the intersection along 's0' & 't' is the same for 's1'.
// Returns false if there is no intersection.
static bool compute_intersection(const InsetSegment& s0, const InsetSegment& s1,
                                 SkPoint* p, SkScalar* s, SkScalar* t) {
    SkVector v0 = s0.fP1 - s0.fP0;
    SkVector v1 = s1.fP1 - s1.fP0;

    SkScalar perpDot = v0.cross(v1);
    if (SkScalarNearlyZero(perpDot)) {
        // segments are parallel
        // check if endpoints are touching
        if (s0.fP1.equalsWithinTolerance(s1.fP0)) {
            *p = s0.fP1;
            *s = SK_Scalar1;
            *t = 0;
            return true;
        }
        if (s1.fP1.equalsWithinTolerance(s0.fP0)) {
            *p = s1.fP1;
            *s = 0;
            *t = SK_Scalar1;
            return true;
        }

        return false;
    }

    SkVector d = s1.fP0 - s0.fP0;
    SkScalar localS = d.cross(v1) / perpDot;
    if (localS < 0 || localS > SK_Scalar1) {
        return false;
    }
    SkScalar localT = d.cross(v0) / perpDot;
    if (localT < 0 || localT > SK_Scalar1) {
        return false;
    }

    v0 *= localS;
    *p = s0.fP0 + v0;
    *s = localS;
    *t = localT;

    return true;
}