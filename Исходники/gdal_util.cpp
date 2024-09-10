std::string FetchTimeZone( double dfX, double dfY, const char *pszWkt )
{
    CPLDebug( "WINDNINJA", "Fetching timezone for  %lf,%lf", dfX, dfY );
    if( pszWkt != NULL )
    {
        OGRSpatialReference oSourceSRS, oTargetSRS;
        OGRCoordinateTransformation *poCT;

        oSourceSRS.SetWellKnownGeogCS( "WGS84" );
        oTargetSRS.importFromWkt( (char**)&pszWkt );

        poCT = OGRCreateCoordinateTransformation( &oSourceSRS, &oTargetSRS );
        if( poCT == NULL )
        {
            CPLError( CE_Failure, CPLE_AppDefined,
                      "OGR coordinate transformation failed" );
            return std::string();
        }
        if( !poCT->Transform( 1, &dfX, &dfY ) )
        {
            CPLError( CE_Failure, CPLE_AppDefined,
                      "OGR coordinate transformation failed" );
            return std::string();
        }
        OGRCoordinateTransformation::DestroyCT( poCT );
    }
    OGRGeometryH hGeometry = OGR_G_CreateGeometry( wkbPoint );
    OGR_G_SetPoint_2D( hGeometry, 0, dfX, dfY );

    OGRDataSourceH hDS;
    OGRLayerH hLayer;
    OGRFeatureH hFeature;

    std::string oTzFile = FindDataPath( "tz_world.zip" );
    oTzFile = "/vsizip/" + oTzFile + "/world/tz_world.shp";

    hDS = OGROpen( oTzFile.c_str(), 0, NULL );
    if( hDS == NULL )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Failed to open datasource: %s", oTzFile.c_str() );
        return std::string();
    }
    hLayer = OGR_DS_GetLayer( hDS, 0 );
    OGR_L_SetSpatialFilter( hLayer, hGeometry );
    OGR_L_ResetReading( hLayer );
    int nMaxTries = 5;
    int nTries = 0;
    OGRGeometryH hBufferGeometry;
    do
    {
        if( nTries == 0 )
        {
            hBufferGeometry = OGR_G_Clone( hGeometry );
        }
        else
        {
            hBufferGeometry = OGR_G_Buffer( hGeometry, 0.2 * nTries, 30 );
        }
        OGR_L_SetSpatialFilter( hLayer, hBufferGeometry );
        hFeature = OGR_L_GetNextFeature( hLayer );
        OGR_G_DestroyGeometry( hBufferGeometry );
        nTries++;
    }
    while( hFeature == NULL && nTries < nMaxTries );
    std::string oTimeZone;
    if( hFeature == NULL )
    {
        oTimeZone = std::string();
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Failed to find timezone" );
    }
    else
    {
        oTimeZone = std::string( OGR_F_GetFieldAsString( hFeature, 0 ) );
    }
    OGR_F_Destroy( hFeature );
    OGR_G_DestroyGeometry( hGeometry );
    OGR_DS_Destroy( hDS );
    return oTimeZone;
}