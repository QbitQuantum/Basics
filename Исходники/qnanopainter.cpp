void QNanoPainter::roundedRect(const QRectF &rect, float radius)
{
    roundedRect(rect.x(), rect.y(), rect.width(), rect.height(), radius);
}