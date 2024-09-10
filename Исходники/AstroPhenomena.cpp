Angle 
LunarArcOfLight( double julianDay )
{
    shared_ptr< JPLEphemeris > spEphemeris
            = JPLEphemeris::GetEphemeris( julianDay );
    if ( spEphemeris == 0 )
        return Angle( 0. ); //!!!
    Point3D earthBarycentric;
    Vector3D earthBarycentricVelocity;
    Matrix3D nutAndPrecMatrix;
#ifdef DEBUG
    bool earthRslt =
#endif
            GetEarthBarycentric( julianDay, &earthBarycentric,
                                 &earthBarycentricVelocity, spEphemeris );
    Assert( earthRslt );
#ifdef DEBUG
    bool oblRslt =
#endif
            GetNutPrecAndObliquity( julianDay, &nutAndPrecMatrix,
                                    0, spEphemeris );
    Assert( oblRslt );
    Equatorial solarPos = SolarEquatorialPosition( julianDay,
                                                   earthBarycentric,
                                                   earthBarycentricVelocity,
                                                   nutAndPrecMatrix,
                                                   spEphemeris );
    Equatorial lunarPos = LunarEquatorialPosition( julianDay,
                                                   nutAndPrecMatrix,
                                                   spEphemeris );
    Angle diffRA = lunarPos.RightAscension() - solarPos.RightAscension();
    Angle diffDec = lunarPos.Declination() - solarPos.Declination();
    return ArcCos( diffRA.Cos( ) * diffDec.Cos( ) );
}