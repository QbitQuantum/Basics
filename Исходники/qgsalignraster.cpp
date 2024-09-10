bool QgsAlignRaster::createAndWarp( const Item& raster )
{
  GDALDriverH hDriver = GDALGetDriverByName( "GTiff" );
  if ( !hDriver )
  {
    mErrorMessage = QString( "GDALGetDriverByName(GTiff) failed." );
    return false;
  }

  // Open the source file.
  GDALDatasetH hSrcDS = GDALOpen( raster.inputFilename.toLocal8Bit().constData(), GA_ReadOnly );
  if ( !hSrcDS )
  {
    mErrorMessage = QObject::tr( "Unable to open input file: " ) + raster.inputFilename;
    return false;
  }

  // Create output with same datatype as first input band.

  int bandCount = GDALGetRasterCount( hSrcDS );
  GDALDataType eDT = GDALGetRasterDataType( GDALGetRasterBand( hSrcDS, 1 ) );

  // Create the output file.
  GDALDatasetH hDstDS;
  hDstDS = GDALCreate( hDriver, raster.outputFilename.toLocal8Bit().constData(), mXSize, mYSize,
                       bandCount, eDT, NULL );
  if ( !hDstDS )
  {
    GDALClose( hSrcDS );
    mErrorMessage = QObject::tr( "Unable to create output file: " ) + raster.outputFilename;
    return false;
  }

  // Write out the projection definition.
  GDALSetProjection( hDstDS, mCrsWkt.toAscii().constData() );
  GDALSetGeoTransform( hDstDS, ( double* )mGeoTransform );

  // Copy the color table, if required.
  GDALColorTableH hCT = GDALGetRasterColorTable( GDALGetRasterBand( hSrcDS, 1 ) );
  if ( hCT != NULL )
    GDALSetRasterColorTable( GDALGetRasterBand( hDstDS, 1 ), hCT );

  // -----------------------------------------------------------------------

  // Setup warp options.
  GDALWarpOptions* psWarpOptions = GDALCreateWarpOptions();
  psWarpOptions->hSrcDS = hSrcDS;
  psWarpOptions->hDstDS = hDstDS;

  psWarpOptions->nBandCount = GDALGetRasterCount( hSrcDS );
  psWarpOptions->panSrcBands = ( int * ) CPLMalloc( sizeof( int ) * psWarpOptions->nBandCount );
  psWarpOptions->panDstBands = ( int * ) CPLMalloc( sizeof( int ) * psWarpOptions->nBandCount );
  for ( int i = 0; i < psWarpOptions->nBandCount; ++i )
  {
    psWarpOptions->panSrcBands[i] = i + 1;
    psWarpOptions->panDstBands[i] = i + 1;
  }

  psWarpOptions->eResampleAlg = ( GDALResampleAlg ) raster.resampleMethod;

  // our progress function
  psWarpOptions->pfnProgress = _progress;
  psWarpOptions->pProgressArg = this;

  // Establish reprojection transformer.
  psWarpOptions->pTransformerArg =
    GDALCreateGenImgProjTransformer( hSrcDS, GDALGetProjectionRef( hSrcDS ),
                                     hDstDS, GDALGetProjectionRef( hDstDS ),
                                     FALSE, 0.0, 1 );
  psWarpOptions->pfnTransformer = GDALGenImgProjTransform;

  double rescaleArg[2];
  if ( raster.rescaleValues )
  {
    rescaleArg[0] = raster.srcCellSizeInDestCRS; // source cell size
    rescaleArg[1] = mCellSizeX * mCellSizeY;  // destination cell size
    psWarpOptions->pfnPreWarpChunkProcessor = rescalePreWarpChunkProcessor;
    psWarpOptions->pfnPostWarpChunkProcessor = rescalePostWarpChunkProcessor;
    psWarpOptions->pPreWarpProcessorArg = rescaleArg;
    psWarpOptions->pPostWarpProcessorArg = rescaleArg;
    // force use of float32 data type as that is what our pre/post-processor uses
    psWarpOptions->eWorkingDataType = GDT_Float32;
  }

  // Initialize and execute the warp operation.
  GDALWarpOperation oOperation;
  oOperation.Initialize( psWarpOptions );
  oOperation.ChunkAndWarpImage( 0, 0, mXSize, mYSize );

  GDALDestroyGenImgProjTransformer( psWarpOptions->pTransformerArg );
  GDALDestroyWarpOptions( psWarpOptions );

  GDALClose( hDstDS );
  GDALClose( hSrcDS );
  return true;
}