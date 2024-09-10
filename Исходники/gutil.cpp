void drawPolygon(QPainter &p, const std::vector<QPointF> &points, bool fill,
                 const QColor colorFill, const QColor colorLine) {
  if (points.size() == 0) return;
  p.setPen(colorLine);
  QPolygonF E0Polygon;
  int i = 0;
  for (i = 0; i < (int)points.size(); i++) E0Polygon << QPointF(points[i]);
  E0Polygon << QPointF(points[0]);

  QPainterPath E0Path;
  E0Path.addPolygon(E0Polygon);
  if (fill) p.fillPath(E0Path, QBrush(colorFill));
  p.drawPath(E0Path);
}