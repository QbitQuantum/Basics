SVGTransform SVGTransformList::consolidate()
{
    AffineTransform matrix;
    if (!concatenate(matrix))
        return SVGTransform();

    SVGTransform transform(matrix);
    clear();
    append(transform);
    return transform;
}