QPainterPath UBGraphicsCompass::hingeShape() const
{
    QPainterPath path;
    path.moveTo(hingeRect().left() + 4, hingeRect().top());
    path.lineTo(hingeRect().right() - 4, hingeRect().top());
    path.arcTo(
        hingeRect().right() - 8,
        hingeRect().top(),
        8, 8,
        90, -90);
    path.lineTo(hingeRect().right(), hingeRect().bottom() - 4);
    path.arcTo(
        hingeRect().right() - 8,
        hingeRect().bottom() - 8,
        8, 8,
        0, -90);
    path.lineTo(hingeRect().left() + 4, hingeRect().bottom());
    path.arcTo(
        hingeRect().left(),
        hingeRect().bottom() - 8,
        8, 8,
        -90, -90);
    path.lineTo(hingeRect().left(), hingeRect().top() + 4);
    path.arcTo(
        hingeRect().left(),
        hingeRect().top(),
        8, 8,
        -180, -90);
    path.closeSubpath();
    return path;
}