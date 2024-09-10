QPolygonF UBGeometryUtils::lineToPolygon(const QLineF& pLine, const qreal& pWidth)
{
    qreal x1 = pLine.x1();
    qreal y1 = pLine.y1();

    qreal x2 = pLine.x2();
    qreal y2 = pLine.y2();

    qreal alpha = (90.0 - pLine.angle()) * PI / 180.0;
    qreal hypothenuse = pWidth / 2;

    // TODO UB 4.x PERF cache sin/cos table
    qreal opposite = sin(alpha) * hypothenuse;
    qreal adjacent = cos(alpha) * hypothenuse;

    QPointF p1a(x1 - adjacent, y1 - opposite);
    QPointF p1b(x1 + adjacent, y1 + opposite);

    QPointF p2a(x2 - adjacent, y2 - opposite);
    QPointF p2b(x2 + adjacent, y2 + opposite);

    QPainterPath painterPath;

    painterPath.moveTo(p1a);
    painterPath.lineTo(p2a);

    painterPath.arcTo(x2 - hypothenuse, y2 - hypothenuse, pWidth, pWidth, (90.0 + pLine.angle()), -180.0);

    //painterPath.lineTo(p2b);
    painterPath.lineTo(p1b);

    painterPath.arcTo(x1 - hypothenuse, y1 - hypothenuse, pWidth, pWidth, -1 * (90.0 - pLine.angle()), -180.0);

    painterPath.closeSubpath();

    return painterPath.toFillPolygon();
}