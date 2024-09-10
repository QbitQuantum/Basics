CPLErr HDF5ImageDataset::CreateODIMH5Projection()
{
    const char* const pszProj4String = GetMetadataItem("where_projdef");
    const char* const pszLL_lon = GetMetadataItem("where_LL_lon");
    const char* const pszLL_lat = GetMetadataItem("where_LL_lat");
    const char* const pszUR_lon = GetMetadataItem("where_UR_lon");
    const char* const pszUR_lat = GetMetadataItem("where_UR_lat");
    if( pszProj4String == NULL ||
            pszLL_lon == NULL || pszLL_lat == NULL ||
            pszUR_lon == NULL || pszUR_lat == NULL )
        return CE_Failure;

    if( oSRS.importFromProj4( pszProj4String ) != OGRERR_NONE )
        return CE_Failure;

    OGRSpatialReference oSRSWGS84;
    oSRSWGS84.SetWellKnownGeogCS( "WGS84" );

    OGRCoordinateTransformation* poCT =
        OGRCreateCoordinateTransformation( &oSRSWGS84, &oSRS );
    if( poCT == NULL )
        return CE_Failure;

    /* Reproject corners from long,lat WGS84 to the target SRS */
    double dfLLX = CPLAtof(pszLL_lon);
    double dfLLY = CPLAtof(pszLL_lat);
    double dfURX = CPLAtof(pszUR_lon);
    double dfURY = CPLAtof(pszUR_lat);
    if( !poCT->Transform(1, &dfLLX, &dfLLY) ||
            !poCT->Transform(1, &dfURX, &dfURY) )
    {
        delete poCT;
        return CE_Failure;
    }
    delete poCT;

    /* Compute the geotransform now */
    const double dfPixelX = (dfURX - dfLLX) / nRasterXSize;
    const double dfPixelY = (dfURY - dfLLY) / nRasterYSize;

    bHasGeoTransform = true;
    adfGeoTransform[0] = dfLLX;
    adfGeoTransform[1] = dfPixelX;
    adfGeoTransform[2] = 0;
    adfGeoTransform[3] = dfURY;
    adfGeoTransform[4] = 0;
    adfGeoTransform[5] = -dfPixelY;

    CPLFree( pszProjection );
    oSRS.exportToWkt( &pszProjection );

    return CE_None;
}