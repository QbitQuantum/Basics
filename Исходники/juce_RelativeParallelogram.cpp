void RelativeParallelogram::getPath (Path& path, Expression::Scope* const scope) const
{
    Point<float> points[4];
    resolveFourCorners (points, scope);

    path.startNewSubPath (points[0]);
    path.lineTo (points[1]);
    path.lineTo (points[3]);
    path.lineTo (points[2]);
    path.closeSubPath();
}