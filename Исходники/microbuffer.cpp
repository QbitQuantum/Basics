/// Determine whether a sphere is wholly outside a cone.
///
/// This is used to cull disks - the sphere is the bounding sphere of the
/// disk, and the cone is the cone of incoming light of interest.
///
/// Getting an expression which is both correct and efficient (ie, not
/// involving special functions) is tricky.  The simple version of it is when
/// the radius is zero, in which case we just need to compute
///
///     cosConeAngle > dot(p/plen, N)
///
/// In the general case of spheres with nonzero radius the condition to check
/// is that
///
///     coneAngle + boundingSphereAngle < coneNormalToSphereCenterAngle
///
/// After some algebra, this reduces to the expression
///
///     sqrt(dot(p,p) - r*r)*cosConeAngle - r*sinConeAngle > dot(p, n);
///
/// which is valid as long as the sum of the sphere angle and cone angle are
/// less than pi:
///
///     sqrt(1 - r*r/dot(p,p)) < -cosConeAngle
///
/// in which case the sphere must intersect the cone.
///
/// \param p - center of sphere
/// \param plen2 - length of p
/// \param r - sphere radius
/// \param n - cone normal
/// \param cosConeAngle - cos(theta) where theta = cone angle from N
/// \param sinConeAngle - sin(theta)
inline bool sphereOutsideCone(V3f p, float plen2, float r,
                              V3f n, float cosConeAngle, float sinConeAngle)
{
    // The actual expressions used here are an optimized version which does
    // the same thing, but avoids calling sqrt().  This makes a difference
    // when this is the primary culling test and you're iterating over lots of
    // points - you need to reject invalid points as fast as possible.
    float x = plen2 - r*r;
    // special case - if the sphere covers the origin, it must intersect the
    // cone.
    if(x < 0)
        return false;
    // Special case - if sphere angle and cone angle add to >= 180 degrees, the
    // sphere and cone must intersect.
    if(cosConeAngle < 0 && x < plen2*cosConeAngle*cosConeAngle)
        return false;
    // General case
    float lhs = x*cosConeAngle*cosConeAngle;
    float rhs = dot(p, n) + r*sinConeAngle;
    return copysignf(lhs, cosConeAngle) > copysignf(rhs*rhs, rhs);
}