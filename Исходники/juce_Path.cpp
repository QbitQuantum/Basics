bool Path::intersectsLine (const Line<float>& line, const float tolerance)
{
    PathFlatteningIterator i (*this, AffineTransform::identity, tolerance);
    Point<float> intersection;

    while (i.next())
        if (line.intersects (Line<float> (i.x1, i.y1, i.x2, i.y2), intersection))
            return true;

    return false;
}