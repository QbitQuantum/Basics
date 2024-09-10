OGRErr GTMWaypointLayer::CreateFeature (OGRFeature *poFeature)
{
    FILE* fp = poDS->getOutputFP();
    if (fp == NULL)
        return CE_Failure;

    OGRGeometry *poGeom = poFeature->GetGeometryRef();
    if ( poGeom == NULL )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Features without geometry not supported by GTM writer in waypoints layer." );
        return OGRERR_FAILURE;
    }

    if (NULL != poCT)
    {
        poGeom = poGeom->clone();
        poGeom->transform( poCT );
    }


    switch( poGeom->getGeometryType() )
    {
    case wkbPoint:
    case wkbPoint25D:
    {
        OGRPoint* point = (OGRPoint*)poGeom;
        double lat = point->getY();
        double lon = point->getX();
        CheckAndFixCoordinatesValidity(lat, lon);
        poDS->checkBounds((float)lat, (float)lon);
        writeDouble(fp, lat);
        writeDouble(fp, lon);
        float altitude = 0.0;
        if (poGeom->getGeometryType() == wkbPoint25D)
            altitude = (float) point->getZ();

        WriteFeatureAttributes(poFeature, altitude);
        break;
    }

    default:
    {
        CPLError( CE_Failure, CPLE_NotSupported,
                  "Geometry type of `%s' not supported for 'waypoint' element.\n",
                  OGRGeometryTypeToName(poGeom->getGeometryType()) );
        return OGRERR_FAILURE;
    }
    }

    if (NULL != poCT)
        delete poGeom;

    return OGRERR_NONE;

}