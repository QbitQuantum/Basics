QgsRegularPolygon::QgsRegularPolygon( const QgsPoint &pt1, const QgsPoint &pt2, const int numSides )
  : mCenter( QgsPoint() )
  , mFirstVertex( QgsPoint() )
  , mNumberSides( 0 )
  , mRadius( 0.0 )
{
  if ( numSides >= 3 )
  {
    mNumberSides = numSides;

    double azimuth = pt1.azimuth( pt2 );
    QgsPoint pm = QgsGeometryUtils::midpoint( pt1, pt2 );
    double length = pt1.distance( pm );

    double angle = ( 180 - ( 360 / numSides ) ) / 2.0;
    double hypothenuse = length / cos( angle * M_PI / 180 );
    // TODO: inclination

    mCenter = pt1.project( hypothenuse, azimuth + angle );
    mFirstVertex = pt1;
    mRadius = qAbs( hypothenuse );
  }
}