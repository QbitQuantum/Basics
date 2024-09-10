void Path::translate(const FloatSize& size)
{
    AffineTransform transformation;
    transformation.translate(size.width(), size.height());
    transform(transformation);
}