bool
LocalizedNode::setPosition( const GeoPoint& pos )
{
    if ( _mapSRS.valid() )
    {
        // first transform the point to the map's SRS:
        GeoPoint mapPos = _mapSRS.get() ? pos.transform(_mapSRS.get()) : pos;
        if ( !mapPos.isValid() )
            return false;

        _mapPosition = mapPos;
    }
    else
    {
        _mapPosition = pos;
    }

    // make sure the node is set up for auto-z-update if necessary:
    configureForAltitudeMode( _mapPosition.altitudeMode() );

    // update the node.
    if ( !updateTransforms( _mapPosition ) )
        return false;

    return true;
}