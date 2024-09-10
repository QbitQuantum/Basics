void StatsWidgetElement::paintEvent(QPaintEvent * /*ev*/)
{
    QPen pen;
    pen.setColor(QColor(0, 0, 0, 255));

    QRect rect;
    rect.setTopLeft(QPoint(BORDER_X, BORDER_Y));
    rect.setWidth(frameRect().width()   - BORDER_WIDTH);
    rect.setHeight(frameRect().height() - BORDER_WIDTH);

    QPainter p(this);
    p.setPen(pen);
    p.setRenderHint(QPainter::Antialiasing);
    p.drawRoundRect(rect, 1000 / rect.width(), 1000 / rect.height());
}