bool
AddPointHandler::addPoint( float x, float y, osgViewer::View* view )
{
    osg::Vec3d world;    
    MapNode* mapNode = _featureNode->getMapNode();

    if ( mapNode->getTerrain()->getWorldCoordsUnderMouse( view, x, y, world ) )
    {
        // Get the map point from the world
        GeoPoint mapPoint;
        mapPoint.fromWorld( mapNode->getMapSRS(), world );

        Feature* feature = _featureNode->getFeature();

        if ( feature )            
        {
            // Convert the map point to the feature's SRS
            GeoPoint featurePoint = mapPoint.transform( feature->getSRS() );

            feature->getGeometry()->push_back( featurePoint.vec3d() );            
            _featureNode->init();            
            return true;
        }        
    }
    return false;
}