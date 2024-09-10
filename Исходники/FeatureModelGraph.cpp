osg::BoundingSphered
FeatureModelGraph::getBoundInWorldCoords(const GeoExtent& extent,
                                         const MapFrame*  mapf ) const
{
    osg::Vec3d center, corner;
    GeoExtent workingExtent;

    if ( !extent.isValid() )
    {
        return osg::BoundingSphered();
    }

    if ( extent.getSRS()->isEquivalentTo( _usableMapExtent.getSRS() ) )
    {
        workingExtent = extent;
    }
    else
    {
        workingExtent = extent.transform( _usableMapExtent.getSRS() ); // safe.
    }

    workingExtent.getCentroid( center.x(), center.y() );
    
    double centerZ = 0.0;    
    if ( mapf )
    {
        // Use an appropriate resolution for this extents width
        double resolution = workingExtent.width();             
        ElevationQuery query( *mapf );
        GeoPoint p( mapf->getProfile()->getSRS(), center, ALTMODE_ABSOLUTE );
        query.getElevation( p, center.z(), resolution );
        centerZ = center.z();
    }    

    corner.x() = workingExtent.xMin();
    corner.y() = workingExtent.yMin();
    corner.z() = 0;

    if ( _session->getMapInfo().isGeocentric() )
    {
        workingExtent.getSRS()->transformToECEF( center, center );
        workingExtent.getSRS()->transformToECEF( corner, corner );
    }

    return osg::BoundingSphered( center, (center-corner).length() );
}