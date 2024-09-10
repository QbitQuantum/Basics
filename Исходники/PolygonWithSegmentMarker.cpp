PolygonWithSegmentMarker::PolygonWithSegmentMarker(
    GeoLib::Polyline const& polyline)
    : GeoLib::Polygon(polyline, true),
      _marker(polyline.getNumberOfPoints(), false)
{
}