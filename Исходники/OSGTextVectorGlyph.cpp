//----------------------------------------------------------------------
// the next edge normal is computed as a pi/2 clockwise rotation of
// the direction from this point to the next one. The edge normals
// do thus point to the left of the path.
// Author: afischle
//----------------------------------------------------------------------
static Vec2f computeEdgeNormal(const Vec2f &a, const Vec2f &b, bool cw)
{
    Vec2f d = b - a;
    d.normalize();
    return cw == true ? Vec2f(d.y(), -d.x()) : Vec2f(-d.y(), d.x());
}