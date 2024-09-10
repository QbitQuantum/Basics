QgsCircle QgsCircle::fromCenterPoint( const QgsPoint &center, const QgsPoint &pt1 )
{
  double azimuth = QgsGeometryUtils::lineAngle( center.x(), center.y(), pt1.x(), pt1.y() ) * 180.0 / M_PI;
  return QgsCircle( center, center.distance( pt1 ), azimuth );
}