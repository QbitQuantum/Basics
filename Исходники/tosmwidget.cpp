void TOSMWidget::drawLine(QPainter &painter, QLineF line)
{
    painter.drawLine(w2s_x(line.x1()), w2s_y(line.y1()), w2s_x(line.x2()), w2s_y(line.y2()));
}