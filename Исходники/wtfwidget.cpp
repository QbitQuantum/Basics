void WTFWidget::drawInnerArrow(QPainter& painter) {

    if(_innerPercent == 0) return;

    QRect rect = this->contentsRect();
    QPoint center = rect.center();
    painter.save();
    painter.translate(center);
    painter.rotate(90 * _innerPercent);

    QColor arrowColor = QColor::fromRgb(0xff,0xff,0xff,0xff * _innerPercent);
    QPen pen = QPen(arrowColor);
    pen.setWidth(2);
    painter.setPen(pen);
    int left = - CIRCLE_INNER_RADIUS;
    int top =  - CIRCLE_INNER_RADIUS;
    QRect arcRect = QRect(left,top,CIRCLE_INNER_RADIUS * 2,
                          CIRCLE_INNER_RADIUS * 2);
    painter.drawArc(arcRect,90 * 16,270 * 16);

    // start draw arrow
    qreal arrowBorderLen = 8;
    QPainterPath path;
    QPoint topPoint(0,
                    - CIRCLE_INNER_RADIUS - arrowBorderLen/2);
    path.moveTo(topPoint);
    qreal distance = (arrowBorderLen / 2) / qTan(qDegreesToRadians((double)30));
    QPoint rightPoint(distance,-CIRCLE_INNER_RADIUS);
    path.lineTo(rightPoint);
    QPoint bottomPoint(0,
                       - CIRCLE_INNER_RADIUS + arrowBorderLen/2);
    path.lineTo(bottomPoint);
    path.closeSubpath();
    painter.fillPath(path,QBrush(arrowColor));

    painter.translate(-center.x(),-center.y());
    painter.restore();
}