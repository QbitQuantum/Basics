double QgsDistanceArea::computeDistanceBearing(
  const QgsPoint& p1, const QgsPoint& p2,
  double* course1, double* course2 )
{
  if ( p1.x() == p2.x() && p1.y() == p2.y() )
    return 0;

  // ellipsoid
  double a = mSemiMajor;
  double b = mSemiMinor;
  double f = 1 / mInvFlattening;

  double p1_lat = DEG2RAD( p1.y() ), p1_lon = DEG2RAD( p1.x() );
  double p2_lat = DEG2RAD( p2.y() ), p2_lon = DEG2RAD( p2.x() );

  double L = p2_lon - p1_lon;
  double U1 = atan(( 1 - f ) * tan( p1_lat ) );
  double U2 = atan(( 1 - f ) * tan( p2_lat ) );
  double sinU1 = sin( U1 ), cosU1 = cos( U1 );
  double sinU2 = sin( U2 ), cosU2 = cos( U2 );
  double lambda = L;
  double lambdaP = 2 * M_PI;

  double sinLambda = 0;
  double cosLambda = 0;
  double sinSigma = 0;
  double cosSigma = 0;
  double sigma = 0;
  double alpha = 0;
  double cosSqAlpha = 0;
  double cos2SigmaM = 0;
  double C = 0;
  double tu1 = 0;
  double tu2 = 0;

  int iterLimit = 20;
  while ( qAbs( lambda - lambdaP ) > 1e-12 && --iterLimit > 0 )
  {
    sinLambda = sin( lambda );
    cosLambda = cos( lambda );
    tu1 = ( cosU2 * sinLambda );
    tu2 = ( cosU1 * sinU2 - sinU1 * cosU2 * cosLambda );
    sinSigma = sqrt( tu1 * tu1 + tu2 * tu2 );
    cosSigma = sinU1 * sinU2 + cosU1 * cosU2 * cosLambda;
    sigma = atan2( sinSigma, cosSigma );
    alpha = asin( cosU1 * cosU2 * sinLambda / sinSigma );
    cosSqAlpha = cos( alpha ) * cos( alpha );
    cos2SigmaM = cosSigma - 2 * sinU1 * sinU2 / cosSqAlpha;
    C = f / 16 * cosSqAlpha * ( 4 + f * ( 4 - 3 * cosSqAlpha ) );
    lambdaP = lambda;
    lambda = L + ( 1 - C ) * f * sin( alpha ) *
             ( sigma + C * sinSigma * ( cos2SigmaM + C * cosSigma * ( -1 + 2 * cos2SigmaM * cos2SigmaM ) ) );
  }

  if ( iterLimit == 0 )
    return -1;  // formula failed to converge

  double uSq = cosSqAlpha * ( a * a - b * b ) / ( b * b );
  double A = 1 + uSq / 16384 * ( 4096 + uSq * ( -768 + uSq * ( 320 - 175 * uSq ) ) );
  double B = uSq / 1024 * ( 256 + uSq * ( -128 + uSq * ( 74 - 47 * uSq ) ) );
  double deltaSigma = B * sinSigma * ( cos2SigmaM + B / 4 * ( cosSigma * ( -1 + 2 * cos2SigmaM * cos2SigmaM ) -
                                       B / 6 * cos2SigmaM * ( -3 + 4 * sinSigma * sinSigma ) * ( -3 + 4 * cos2SigmaM * cos2SigmaM ) ) );
  double s = b * A * ( sigma - deltaSigma );

  if ( course1 )
  {
    *course1 = atan2( tu1, tu2 );
  }
  if ( course2 )
  {
    // PI is added to return azimuth from P2 to P1
    *course2 = atan2( cosU1 * sinLambda, -sinU1 * cosU2 + cosU1 * sinU2 * cosLambda ) + M_PI;
  }

  return s;
}