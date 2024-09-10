BiIt findIntersection(LineSegment<double, 2> lineSeg,
                      BiIt firstPoint, BiIt lastPoint,
                      double epsilon)
{
    for (BiIt it = firstPoint; it != lastPoint; ++it)
    {
        if (intersects(lineSeg, LineSegment<double, 2>(*it, *std::next(it)), epsilon))
            return it;
    }
    return lastPoint;
}