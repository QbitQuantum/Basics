const RNBoolean R3Point::
Collinear(const R3Point& point1, const R3Point& point2) const
{
    // Check if two of points are same
    if ((*this == point1) || (*this == point2) || (point1 == point2)) return TRUE;

    /// Check if three points are collinear
    R3Vector v = point1 - *this;
    v.Cross(point1 - point2);
    if (RNIsZero(v.Length())) return TRUE;
    return FALSE;
}