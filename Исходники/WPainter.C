void WPainter::drawChord(const WRectF& rectangle, int startAngle, int spanAngle)
{
    WTransform oldTransform = WTransform(worldTransform());

    translate(rectangle.center().x(), rectangle.center().y());
    scale(1., rectangle.height() / rectangle.width());

    double start = startAngle / 16.;
    double span = spanAngle / 16.;

    WPainterPath path;
    path.arcMoveTo(0, 0, rectangle.width()/2., start);
    path.arcTo(0, 0, rectangle.width()/2., start, span);
    path.closeSubPath();

    drawPath(path);

    setWorldTransform(oldTransform);
}