OGRErr GTMTrackLayer::CreateFeature (OGRFeature *poFeature)
{
    FILE* fpTmpTrackpoints = poDS->getTmpTrackpointsFP();
    if (fpTmpTrackpoints == NULL)
        return CE_Failure;

    FILE* fpTmpTracks = poDS->getTmpTracksFP();
    if (fpTmpTracks == NULL)
        return CE_Failure;

    OGRGeometry *poGeom = poFeature->GetGeometryRef();
    if ( poGeom == NULL )
    {
        CPLError( CE_Failure, CPLE_AppDefined, 
                  "Features without geometry not supported by GTM writer in track layer." );
        return OGRERR_FAILURE;
    }
   
    if (NULL != poCT)
    {
        poGeom = poGeom->clone();
        poGeom->transform( poCT );
    }
    
    switch( poGeom->getGeometryType() )
    {
    case wkbLineString:
    case wkbLineString25D:
    {
        WriteFeatureAttributes(poFeature);
        OGRLineString* line = (OGRLineString*)poGeom;
        for(int i = 0; i < line->getNumPoints(); ++i)
        {
            double lat = line->getY(i);
            double lon = line->getX(i);
            float altitude = 0;
            CheckAndFixCoordinatesValidity(lat, lon);
            poDS->checkBounds((float)lat, (float)lon);
            if (line->getGeometryType() == wkbLineString25D)
	      altitude = (float)line->getZ(i);
            WriteTrackpoint( lat, lon, altitude, i==0 );
        }
        break;
    }

    case wkbMultiLineString:
    case wkbMultiLineString25D:
    {
        int nGeometries = ((OGRGeometryCollection*)poGeom)->getNumGeometries ();
        for(int j = 0; j < nGeometries; ++j)
        {
            WriteFeatureAttributes(poFeature);
            OGRLineString* line = (OGRLineString*) ( ((OGRGeometryCollection*)poGeom)->getGeometryRef(j) );
            int n = (line) ? line->getNumPoints() : 0;
            for(int i = 0; i < n; ++i)
            {
                double lat = line->getY(i);
                double lon = line->getX(i);
                float altitude = 0;
                CheckAndFixCoordinatesValidity(lat, lon);
                if (line->getGeometryType() == wkbLineString25D)
		  altitude = (float) line->getZ(i);
                WriteTrackpoint( lat, lon, altitude, i==0 );
            }
        }
        break;
    }
    
    default:
    {
        CPLError( CE_Failure, CPLE_NotSupported,
                  "Geometry type of `%s' not supported for 'track' element.\n",
                  OGRGeometryTypeToName(poGeom->getGeometryType()) );
        if (NULL != poCT)
            delete poGeom;
        return OGRERR_FAILURE;
    }
    }
    
    if (NULL != poCT)
        delete poGeom;

    return OGRERR_NONE;
}