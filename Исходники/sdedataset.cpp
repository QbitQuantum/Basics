CPLErr SDEDataset::ComputeRasterInfo() {
    long nSDEErr;
    SE_RASTERINFO raster;
    
    nSDEErr = SE_rasterinfo_create(&raster);
    if( nSDEErr != SE_SUCCESS )
    {
        IssueSDEError( nSDEErr, "SE_rasterinfo_create" );
        return CE_Fatal;
    }
    
    long nRasterColumnId = 0;

    nSDEErr = SE_rascolinfo_get_id( hRasterColumn, 
                                    &nRasterColumnId);
    if( nSDEErr != SE_SUCCESS )
    {
        IssueSDEError( nSDEErr, "SE_rascolinfo_get_id" );
        return CE_Fatal;
    }        

    nSDEErr = SE_raster_get_info_by_id( hConnection, 
                                        nRasterColumnId, 
                                        1, 
                                        raster);
    if( nSDEErr != SE_SUCCESS )
    {
        IssueSDEError( nSDEErr, "SE_rascolinfo_get_id" );
        return CE_Fatal;
    }
    nSDEErr = SE_raster_get_bands(  hConnection, 
                                    raster, 
                                    &paohSDERasterBands, 
                                    (long*)&nBands);
    if( nSDEErr != SE_SUCCESS )
    {
        IssueSDEError( nSDEErr, "SE_raster_get_bands" );
        return CE_Fatal;
    }
    
    SE_RASBANDINFO band;
    
    // grab our other stuff from the first band and hope for the best
    band = paohSDERasterBands[0];
    
    
    nSDEErr = SE_rasbandinfo_get_band_size( band, 
                                            (long*)&nRasterXSize, 
                                            (long*)&nRasterYSize);
    if( nSDEErr != SE_SUCCESS )
    {
        IssueSDEError( nSDEErr, "SE_rasbandinfo_get_band_size" );
        return CE_Fatal;
    }
    
    SE_ENVELOPE extent;
    nSDEErr = SE_rasbandinfo_get_extent(band, &extent);
    if( nSDEErr != SE_SUCCESS )
    {
        IssueSDEError( nSDEErr, "SE_rasbandinfo_get_extent" );
        return CE_Fatal;
    }
    dfMinX = extent.minx;
    dfMinY = extent.miny;
    dfMaxX = extent.maxx;
    dfMaxY = extent.maxy;

    CPLDebug("SDERASTER", "minx: %.5f, miny: %.5f, maxx: %.5f, maxy: %.5f", dfMinX, dfMinY, dfMaxX, dfMaxY);

    // x0 roughly corresponds to dfMinX
    // y0 roughly corresponds to dfMaxY
    // They can be different than the extent parameters because 
    // SDE uses offsets.  The following info is from Duarte Carreira 
    // in relation to bug #2063 http://trac.osgeo.org/gdal/ticket/2063 :

    // Depending on how the data was loaded, the pixel width 
    // or pixel height may include a pixel offset from the nearest
    // tile boundary. An offset will be indicated by aplus sign 
    // "+" followed by a value. The value indicates the number 
    // of pixels the nearest tile boundary is to the left of
    // the image for the x dimension or the number of
    // pixels the nearest tile boundary is above the image for 
    // the y dimension. The offset information is only useful 
    // for advanced application developers who need to know 
    // where the image begins in relation to the underlying tile structure

    LFLOAT x0, y0; 
    nSDEErr = SE_rasbandinfo_get_tile_origin(band, &x0, &y0);
    if( nSDEErr != SE_SUCCESS )
    {
        IssueSDEError( nSDEErr, "SE_rasbandinfo_get_tile_origin" );
        return CE_Fatal;
    }
    CPLDebug("SDERASTER", "Tile origin: %.5f, %.5f", x0, y0);

    // we also need to adjust dfMaxX and dfMinY otherwise the cell size will change
    dfMaxX = (x0-dfMinX) + dfMaxX;
    dfMinY = (y0-dfMaxY) + dfMinY;

    // adjust the bbox based on the tile origin.
    dfMinX = MIN(x0, dfMinX);
    dfMaxY = MAX(y0, dfMaxY);

    nSDEErr = SE_rasterattr_create(&hAttributes, false);
    if( nSDEErr != SE_SUCCESS )
    {
        IssueSDEError( nSDEErr, "SE_rasterattr_create" );
        return CE_Fatal;
    }
    
    // Grab the pointer for our member variable

    nSDEErr = SE_stream_create(hConnection, &hStream);
    if( nSDEErr != SE_SUCCESS )
    {
        IssueSDEError( nSDEErr, "SE_stream_create" );
        return CE_Fatal;
    }

    
    for (int i=0; i < nBands; i++) {
        SetBand( i+1, new SDERasterBand( this, i+1, -1, &(paohSDERasterBands[i]) ));
    }

    GDALRasterBand* b = GetRasterBand(1);
    
    eDataType = b->GetRasterDataType();
    
    SE_rasterinfo_free(raster);

    return CE_None;
}