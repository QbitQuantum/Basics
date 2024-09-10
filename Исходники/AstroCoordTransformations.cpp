Galactic 
EquatorialToGalactic( const Equatorial & equatorial )
{
    Angle galNorthRA( 192.25, Angle::Degree );
    Angle galNorthDec( 27.4, Angle::Degree );
    Angle longOffset( 33. + 270., Angle::Degree );
    Angle adjRA = galNorthRA  - equatorial.RightAscension();
    double sinAdjRA = adjRA.Sin( );
    double cosAdjRA = adjRA.Cos( );
    double sinDec = equatorial.Declination().Sin( );
    double cosDec = equatorial.Declination().Cos( );
    double tanDec = (cosDec == 0.)  ?  infinity  :  sinDec / cosDec;
    double sinNDec = galNorthDec.Sin( );
    double cosNDec = galNorthDec.Cos( );
    Angle x = ArcTan( sinAdjRA,  cosAdjRA * sinNDec  -  tanDec * cosNDec );
    Angle lng = longOffset - x;
    lng.NormalizePositive( );
    Angle lat = ArcSin( sinDec * sinNDec  +  cosAdjRA * cosDec * cosNDec );
    return Galactic( lng, lat, equatorial.Distance() );
}