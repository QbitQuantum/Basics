bool
TileModel::ElevationData::getNormal(const osg::Vec3d&      ndc,
                                    const GeoLocator*      ndcLocator,
                                    osg::Vec3&             output,
                                    ElevationInterpolation interp ) const
{
    if ( !_locator.valid() || !ndcLocator )
    {
        output.set(0,0,1);
        return false;
    }

    double xcells = (double)(_hf->getNumColumns()-1);
    double ycells = (double)(_hf->getNumRows()-1);
    double xres = 1.0/xcells;
    double yres = 1.0/ycells;

    osg::Vec3d hf_ndc;
    GeoLocator::convertLocalCoordBetween( *ndcLocator, ndc, *_locator.get(), hf_ndc );

    float centerHeight = HeightFieldUtils::getHeightAtNormalizedLocation(_hf.get(), hf_ndc.x(), hf_ndc.y(), interp);

    osg::Vec3d west ( hf_ndc.x()-xres, hf_ndc.y(), 0.0 );
    osg::Vec3d east ( hf_ndc.x()+xres, hf_ndc.y(), 0.0 );
    osg::Vec3d south( hf_ndc.x(), hf_ndc.y()-yres, 0.0 );
    osg::Vec3d north( hf_ndc.x(), hf_ndc.y()+yres, 0.0 );

    if (!HeightFieldUtils::getHeightAtNormalizedLocation(_neighbors, west.x(),  west.y(),  west.z(), interp))
        west.z() = centerHeight;
    if (!HeightFieldUtils::getHeightAtNormalizedLocation(_neighbors, east.x(),  east.y(),  east.z(), interp))
        east.z() = centerHeight;
    if (!HeightFieldUtils::getHeightAtNormalizedLocation(_neighbors, south.x(), south.y(), south.z(), interp))
        south.z() = centerHeight;
    if (!HeightFieldUtils::getHeightAtNormalizedLocation(_neighbors, north.x(), north.y(), north.z(), interp))
        north.z() = centerHeight;

    osg::Vec3d westWorld, eastWorld, southWorld, northWorld;
    _locator->unitToModel(west,  westWorld);
    _locator->unitToModel(east,  eastWorld);
    _locator->unitToModel(south, southWorld);
    _locator->unitToModel(north, northWorld);

    output = (eastWorld-westWorld) ^ (northWorld-southWorld);
    output.normalize();

    return true;
}