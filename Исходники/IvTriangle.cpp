//-------------------------------------------------------------------------------
// @ ::TriangleIntersect()
//-------------------------------------------------------------------------------
// Returns true if ray intersects triangle
//-------------------------------------------------------------------------------
bool
TriangleIntersect( float& t, const IvVector3& P0, const IvVector3& P1,
                   const IvVector3& P2, const IvRay3& ray )
{
    // test ray direction against triangle
    IvVector3 e1 = P1 - P0;
    IvVector3 e2 = P2 - P0;
    IvVector3 p = ray.GetDirection().Cross(e2);
    float a = e1.Dot(p);

    // if result zero, no intersection or infinite intersections
    // (ray parallel to triangle plane)
    if ( IvIsZero(a) )
        return false;

    // compute denominator
    float f = 1.0f/a;

    // compute barycentric coordinates
    IvVector3 s = ray.GetOrigin() - P0;
    float u = f*s.Dot(p);

    // ray falls outside triangle
    if (u < 0.0f || u > 1.0f)
        return false;

    IvVector3 q = s.Cross(e1);
    float v = f*ray.GetDirection().Dot(q);

    // ray falls outside triangle
    if (v < 0.0f || u+v > 1.0f)
        return false;

    // compute line parameter
    t = f*e2.Dot(q);

    return (t >= 0.0f);
}