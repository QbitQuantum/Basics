void QuickSwitchButton::paintEvent(QPaintEvent *e)
{
    if (m_selected && m_showBackground)
    {
        const QRect r = rect();

        const int radius = 6;
        const int margin_bottom = 5;

        QPainterPath path;
        path.moveTo(0, 0);
        path.arcTo(QRectF(QPointF(-radius, 0), QPointF(radius, radius * 2)), 90, -90);
        path.lineTo(radius, r.bottom() - margin_bottom - radius * 2);
        path.arcTo(QRectF(QPointF(radius, r.bottom() - margin_bottom - radius * 2), QPointF(radius * 3, r.bottom() - margin_bottom)), 180, 90);
        path.lineTo(r.right() - radius * 2, r.bottom() - margin_bottom);
        path.arcTo(QRectF(QPointF(r.right() - radius * 3, r.bottom() - margin_bottom - radius * 2), QPointF(r.right() - radius, r.bottom() - margin_bottom)), 270, 90);
        path.lineTo(r.right() - radius, radius);
        path.arcTo(QRectF(QPointF(r.right() - radius, 0), QPointF(r.right() + radius, radius * 2)), 180, -90);
        path.closeSubpath();

        QPainter painter(this);
        painter.setPen(Qt::transparent);
        painter.setBrush(QColor(255, 255, 255, 255 * .2));
        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawPath(path);
    }

    QLabel::paintEvent(e);
}