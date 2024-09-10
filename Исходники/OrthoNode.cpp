bool
OrthoNode::setPosition( const GeoPoint& position )
{
    MapNode* mapNode = getMapNode();
    if ( mapNode )
    {
        // first transform the point to the map's SRS:
        const SpatialReference* mapSRS = mapNode->getMapSRS();
		//$$$注释
        //GeoPoint mapPos = mapSRS ? position.transform(mapSRS) : position;
        //if ( !mapPos.isValid() )
        //    return false;

        //_mapPosition = mapPos;

		//$$$修改
		if ( mapSRS && position.isValid() )//position原来SRS信息不为空
		{
			position.transform( mapSRS );
			_mapPosition = position;
		}
		else if ( mapSRS )
		{
			_mapPosition = GeoPoint( mapSRS, position.x(), position.y(), position.z() );//position原来SRS信息为空
		}
		else
		{
			_mapPosition = position;
		}

    }
    else
    {
        _mapPosition = position;
    }

    // make sure the node is set up for auto-z-update if necessary:
    configureForAltitudeMode( _mapPosition.altitudeMode() );

    // and update the node.
    if ( !updateTransforms(_mapPosition) )
        return false;

    return true;
}