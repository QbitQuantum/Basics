void 
Geodetic::Set( const Point3D & rectangular )
{
    //Explanatory Supplement (4.22-11 to 4.22-24)
    double X = rectangular.X();
    double Y = rectangular.Y();
    double Z = rectangular.Z();
    double a = radius;
    double b = a  -  flattening * a;
    if ( Z < 0.)
        b = -b;

    if ( (X == 0.) && (Y == 0.) )
    {
        m_longitude.Set( 0. );
        m_latitude.Set( 0. );
        m_height = Z - b;
        if ( m_height < 0. )
            m_height = - m_height;
        return;
    }
    else
        m_longitude = ArcTan( Y, X );
    if ( Z == 0.)
    {
        m_latitude.Set( 0. );
        m_height.Set( r - radius );
        return;
    }

    double r = std::sqrt( X * X  +  Y * Y );
    double aSqr = a * a;
    double bSqr = b * b;
    double E = (b * Z  -  (aSqr - bSqr)) / (a * r);
    double ESqr = E * E;
    double F = (b * Z  +  (aSqr + bSqr)) / (a * r);
    double P = (4./3.) * (E * F  +  1.);
    double Q = 2. * (ESqr  -  F * F);
    double D = P * P * P  +  Q * Q;
    double sqrtD = std::sqrt( D );
    double v = std::pow( (sqrtD - Q), (1./3.) )
            -  std::pow( (sqrtD + Q), (1./3.) );
    const double epsilon = 1.0;
    if ( (std::fabs( Z ) < epsilon ) || (std::fabs( r ) < epsilon) )
        v = - (v * v * v  +  2. * Q) / (3. * P);
    double G = 0.5 * (std::sqrt( ESqr + v )  +  E);
    double t = std::sqrt( G * G  +  (F - v * G) / (G + G - E) )  -  G;
    m_latitude = ArcTan( (a * (1. - t * t)), (2. * b * t) );
    m_height = (r - a * t) * m_latitude.Cos( )
            +  (Z - b) * m_latitude.Sin( );
}