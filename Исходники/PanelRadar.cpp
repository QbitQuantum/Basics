void PanelRadar::paintEvent(QPaintEvent* event) {
    const qreal scale0 = 0.14644660940672623779957781894758;
    const qreal scale1 = (1.0 - scale0);
    
    PanelWidget::paintEvent(event);
    QPainter p;
    p.begin(this);
    setMargins(&p);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    
    QPen pen = p.pen();
    pen.setWidth(1);
    p.setPen(QColor("black"));
    
    QPainterPath path;
    qreal rx = p.device()->width();
    qreal ry = p.device()->height();
    
    QPointF point(0.5 * rx, 0.5 * ry);
    
    path.addEllipse(point, 0.50 * rx, 0.50 * ry);
    p.fillPath(path, QColor("white"));
    path.addEllipse(point, 0.25 * rx, 0.25 * ry);
    p.drawPath(path);

    p.drawLine(0, 0.5 * ry, rx, 0.5 * ry);
    p.drawLine(0.5 * rx, 0, 0.5 * rx, ry);
    p.drawLine(rx * scale0 + 1, ry * scale0 + 1, rx * scale1 - 1, ry * scale1 - 1);
    p.drawLine(rx * scale0 + 1, ry * scale1 - 1, rx * scale1 - 1, ry * scale0 + 1);
    
    drawItems(&p);
    
    p.end();
}