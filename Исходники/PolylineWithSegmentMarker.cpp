PolylineWithSegmentMarker::PolylineWithSegmentMarker(
    GeoLib::Polyline const& polyline)
    : GeoLib::Polyline(polyline), _marker(polyline.getNumberOfSegments(), false)
{
}