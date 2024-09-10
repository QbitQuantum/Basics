void CustomStyle::drawHoverRect(QPainter *painter, const QRect &rect) const
{
/*    double h = r.height();
double h2 = r.height() / 2.0;
QPainterPath path;
path.addRect(r.x() + h2, r.y() + 0, r.width() - h2 * 2, r.height());
path.addEllipse(r.x(), r.y(), h, h);
path.addEllipse(r.x() + r.width() - h, r.y(), h, h);
path.setFillRule(Qt::WindingFill);
painter->setPen(Qt::NoPen);
painter->setBrush(QColor(191, 215, 191));
painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(path);*/
    int radius = qMin(rect.width(), rect.height()) / 2;
    int diam = 2 * radius;

    int x1, y1, x2, y2;
    rect.getCoords(&x1, &y1, &x2, &y2);
    QPainterPath path;
    QColor color;
    color = mergedColors(QColor(0x06, 0x4C, 0xA4), QColor(0xd6, 0xd6, 0xd6));
    QPen pen(color, 4);
    painter->setPen(pen);
    path.moveTo(x2, y1 + radius);
    path.arcTo(QRect(x2 - diam, y1, diam, diam), 0.0, +90.0);
    path.lineTo(x1 + radius, y1);
    path.arcTo(QRect(x1, y1, diam, diam), 90.0, +90.0);
    path.lineTo(x1, y2 - radius);
    path.arcTo(QRect(x1, y2 - diam, diam, diam), 180.0, +90.0);
    path.lineTo(x1 + radius, y2);
    path.arcTo(QRect(x2 - diam, y2 - diam, diam, diam), 270.0, +90.0);
    painter->drawPath(path);
}