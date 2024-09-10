void polygonFromQxClipper(const QPolygonF& qxPolygon,
                          ClipperLib::Polygon &clipperPolygon)
{
  clipperPolygon.clear();
  clipperPolygon.reserve(qxPolygon.size());
  foreach(const QPointF &point, qxPolygon)
  {
    clipperPolygon.push_back(ClipperLib::IntPoint(point.x()*ConversionFactor,
                                                  point.y()*ConversionFactor));
  }