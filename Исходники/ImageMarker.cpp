void ImageMarker::draw (QPainter *p, const QwtScaleMap &xMap, const QwtScaleMap &yMap, const QRect &r) const
{
const int x0 = xMap.transform(d_rect.left());
const int y0 = yMap.transform(d_rect.top());
const int x1 = xMap.transform(d_rect.right());
const int y1 = yMap.transform(d_rect.bottom());

p->drawPixmap(QRect(QPoint(x0, y0), QPoint(x1, y1)), d_pic);
}