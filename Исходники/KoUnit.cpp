qreal KoUnit::approxTransformScale(const QTransform &t)
{
    return std::sqrt(t.determinant());
}