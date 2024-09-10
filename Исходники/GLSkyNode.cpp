void
GLSkyNode::onSetDateTime()
{
    if ( !getSunLight() || !_profile.valid() )
        return;

    const DateTime& dt = getDateTime();
    osg::Vec3d sunPosECEF = getEphemeris()->getSunPositionECEF( dt );

    if ( _profile->getSRS()->isGeographic() )
    {
        sunPosECEF.normalize();
        getSunLight()->setPosition( osg::Vec4(sunPosECEF, 0.0) );
    }
    else
    {
        // pull the ref point:
        GeoPoint refpoint = getReferencePoint();
        if ( !refpoint.isValid() )
        {
            // not found; use the center of the profile:
            _profile->getExtent().getCentroid(refpoint);
        }

        // convert to lat/long:
        GeoPoint refLatLong;
        refpoint.transform(_profile->getSRS()->getGeographicSRS(), refLatLong);

        // Matrix to convert the ECEF sun position to the local tangent plane
        // centered on our reference point:
        osg::Matrixd world2local;
        refLatLong.createWorldToLocal(world2local);

        // convert the sun position:
        osg::Vec3d sunPosLocal = sunPosECEF * world2local;
        sunPosLocal.normalize();

        getSunLight()->setPosition( osg::Vec4(sunPosLocal, 0.0) );
    }
}