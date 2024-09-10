void RelativePointPath::LineTo::addToPath (Path& path, Expression::Scope* scope) const
{
    path.lineTo (endPoint.resolve (scope));
}