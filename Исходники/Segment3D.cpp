Real Segment3D::distance(const Point3D& in) const
{
    Point3D temp;
    closestPoint(in,temp);
    return in.distance(temp);
}