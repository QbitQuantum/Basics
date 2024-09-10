void Path::addEllipse(const FloatPoint& p, float radiusX, float radiusY, float rotation, float startAngle, float endAngle, bool anticlockwise)
{
    ASSERT(ellipseIsRenderable(startAngle, endAngle));
    ASSERT(startAngle >= 0 && startAngle < twoPiFloat);
    ASSERT((anticlockwise && (startAngle - endAngle) >= 0) || (!anticlockwise && (endAngle - startAngle) >= 0));

    if (!rotation) {
        addEllipse(FloatPoint(p.x(), p.y()), radiusX, radiusY, startAngle, endAngle, anticlockwise);
        return;
    }

    // Add an arc after the relevant transform.
    AffineTransform ellipseTransform = AffineTransform::translation(p.x(), p.y()).rotateRadians(rotation);
    ASSERT(ellipseTransform.isInvertible());
    AffineTransform inverseEllipseTransform = ellipseTransform.inverse();
    transform(inverseEllipseTransform);
    addEllipse(FloatPoint::zero(), radiusX, radiusY, startAngle, endAngle, anticlockwise);
    transform(ellipseTransform);
}