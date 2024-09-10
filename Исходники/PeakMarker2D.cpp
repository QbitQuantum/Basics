/// Draw marker as a circle
void PeakMarker2D::drawCircle(QPainter& painter)const
{
  QPainterPath path;
  path.addEllipse(m_boundingRect.toQRectF());
  painter.fillPath(path,m_color);
}