R3Vector R3PointLight::
DirectionFromPoint(const R3Point& point) const
{
    // Return direction to point
    R3Vector L = position - point;
    L.Normalize();
    return L;
}