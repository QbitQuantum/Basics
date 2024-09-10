bool
GeoTransform::setPosition(const GeoPoint& position)
{
    if ( !position.isValid() )
        return false;

    _position = position;

    // relative Z or reprojection require a terrain:
    osg::ref_ptr<Terrain> terrain;
    _terrain.lock(terrain);

    // relative Z requires a terrain:
    if (position.altitudeMode() == ALTMODE_RELATIVE && !terrain.valid())
    {
        OE_TEST << LC << "setPosition failed condition 1\n";
        return false;
    }

    GeoPoint p;

    // transform into terrain SRS if neccesary:
    if (terrain.valid() && !terrain->getSRS()->isEquivalentTo(position.getSRS()))
        p = position.transform(terrain->getSRS());
    else
        p = position;

    // bail if the transformation failed:
    if ( !p.isValid() )
    {
        OE_TEST << LC << "setPosition failed condition 2\n";
        return false;
    }

    // convert to absolute height:
    if ( !p.makeAbsolute(_terrain.get()) )
    {
        OE_TEST << LC << "setPosition failed condition 3\n";
        return false;
    }

    // assemble the matrix:
    osg::Matrixd local2world;
    p.createLocalToWorld( local2world );
    this->setMatrix( local2world );

    // install auto-recompute?
    if (_autoRecompute &&
        _position.altitudeMode() == ALTMODE_RELATIVE &&
        !_autoRecomputeReady)
    {
        // by using the adapter, there's no need to remove
        // the callback then this object destructs.
        terrain->addTerrainCallback(
           new TerrainCallbackAdapter<GeoTransform>(this) );

        _autoRecomputeReady = true;
    }

    return true;
}