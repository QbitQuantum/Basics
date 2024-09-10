static int msContourLayerReadRaster(layerObj *layer, rectObj rect)
{
  mapObj *map = layer->map;  
  char **bands;
  char pointer[64], memDSPointer[128];
  int band = 1;
  double adfGeoTransform[6], adfInvGeoTransform[6];
  double llx, lly, urx, ury;  
  rectObj copyRect, mapRect;
  int dst_xsize, dst_ysize;
  int virtual_grid_step_x, virtual_grid_step_y;
  int src_xoff, src_yoff, src_xsize, src_ysize;  
  double map_cellsize_x, map_cellsize_y, dst_cellsize_x, dst_cellsize_y;
  GDALRasterBandH hBand = NULL;
  CPLErr eErr;
  
  contourLayerInfo *clinfo = (contourLayerInfo *) layer->layerinfo;

  if (layer->debug)
    msDebug("Entering msContourLayerReadRaster().\n");

  if (clinfo == NULL || clinfo->hOrigDS == NULL) {
    msSetError(MS_MISCERR, "Assertion failed: Contour layer not opened!!!",
               "msContourLayerReadRaster()");
    return MS_FAILURE;    
  }

  bands = CSLTokenizeStringComplex(
               CSLFetchNameValue(layer->processing,"BANDS"), " ,", FALSE, FALSE );
  if (CSLCount(bands) > 0) {
    band = atoi(bands[0]);
    if (band < 1 || band > GDALGetRasterCount(clinfo->hOrigDS)) {
      msSetError( MS_IMGERR,
                  "BANDS PROCESSING directive includes illegal band '%d', should be from 1 to %d.",
                  "msContourLayerReadRaster()",
                  band, GDALGetRasterCount(clinfo->hOrigDS));
      CSLDestroy(bands);
      return MS_FAILURE;
    }
  }
  CSLDestroy(bands);

  hBand = GDALGetRasterBand(clinfo->hOrigDS, band);
  if (hBand == NULL)
  {
    msSetError(MS_IMGERR,
               "Band %d does not exist on dataset.",
               "msContourLayerReadRaster()", band);
    return MS_FAILURE;
  }

  if (layer->projection.numargs > 0 &&
      EQUAL(layer->projection.args[0], "auto")) {
    const char *wkt;
    wkt = GDALGetProjectionRef(clinfo->hOrigDS);
    if (wkt != NULL && strlen(wkt) > 0) {
      if (msOGCWKT2ProjectionObj(wkt, &(layer->projection),
                                 layer->debug) != MS_SUCCESS) {
        char  msg[MESSAGELENGTH*2];
        errorObj *ms_error = msGetErrorObj();

        snprintf( msg, sizeof(msg),
                  "%s\n"
                  "PROJECTION AUTO cannot be used for this "
                  "GDAL raster (`%s').",
                  ms_error->message, layer->data);
        msg[MESSAGELENGTH-1] = '\0';

        msSetError(MS_OGRERR, "%s","msDrawRasterLayer()",
                   msg);
        return MS_FAILURE;
      }
    }
  }
  
  /*
   * Compute the georeferenced window of overlap, and read the source data
   * downsampled to match output resolution, or at full resolution if
   * output resolution is lower than the source resolution.
   *
   * A large portion of this overlap calculation code was borrowed from 
   * msDrawRasterLayerGDAL(). 
   * Would be possible to move some of this to a reusable function?
   *
   * Note: This code works only if no reprojection is involved. It would
   * need rework to support cases where output projection differs from source
   * data file projection.
   */
  
  src_xsize = GDALGetRasterXSize(clinfo->hOrigDS);
  src_ysize = GDALGetRasterYSize(clinfo->hOrigDS);

  /* set the Dataset extent */
  msGetGDALGeoTransform(clinfo->hOrigDS, map, layer, adfGeoTransform);  
  clinfo->extent.minx = adfGeoTransform[0];
  clinfo->extent.maxy = adfGeoTransform[3];
  clinfo->extent.maxx = adfGeoTransform[0] + src_xsize * adfGeoTransform[1];
  clinfo->extent.miny = adfGeoTransform[3] + src_ysize * adfGeoTransform[5];
  
  if (layer->transform) {
    if (layer->debug)
      msDebug("msContourLayerReadRaster(): Entering transform.\n");

    InvGeoTransform(adfGeoTransform, adfInvGeoTransform);

    mapRect = rect;
    map_cellsize_x = map_cellsize_y = map->cellsize;      
#ifdef USE_PROJ
    /* if necessary, project the searchrect to source coords */
    if (msProjectionsDiffer( &(map->projection), &(layer->projection)))  {
      if ( msProjectRect(&map->projection, &layer->projection, &mapRect)
          != MS_SUCCESS ) {
        msDebug("msContourLayerReadRaster(%s): unable to reproject map request rectangle into layer projection, canceling.\n", layer->name);
        return MS_FAILURE;
      }

      map_cellsize_x = MS_CELLSIZE(mapRect.minx, mapRect.maxx, map->width);
      map_cellsize_y = MS_CELLSIZE(mapRect.miny, mapRect.maxy, map->height);

      /* if the projection failed to project the extent requested, we need to
         calculate the cellsize to preserve the initial map cellsize ratio */
      if ( (mapRect.minx < GEO_TRANS(adfGeoTransform,0,src_ysize)) ||
           (mapRect.maxx > GEO_TRANS(adfGeoTransform,src_xsize,0)) ||
           (mapRect.miny < GEO_TRANS(adfGeoTransform+3,0,src_ysize)) || 
           (mapRect.maxy > GEO_TRANS(adfGeoTransform+3,src_xsize,0)) ) {

        int src_unit, dst_unit;
        src_unit = GetMapserverUnitUsingProj(&map->projection);
        dst_unit = GetMapserverUnitUsingProj(&layer->projection);
        if (src_unit == -1 || dst_unit == -1) {
          msDebug("msContourLayerReadRaster(%s): unable to reproject map request rectangle into layer projection, canceling.\n", layer->name);
          return MS_FAILURE;
        }

        map_cellsize_x =  MS_CONVERT_UNIT(src_unit, dst_unit,
                                          MS_CELLSIZE(rect.minx, rect.maxx, map->width)); 
        map_cellsize_y = MS_CONVERT_UNIT(src_unit, dst_unit,
                                         MS_CELLSIZE(rect.miny, rect.maxy, map->height));
      }       
    }
#endif
    
    if (map_cellsize_x == 0 || map_cellsize_y == 0) {
      if (layer->debug)
        msDebug("msContourLayerReadRaster(): Cellsize can't be 0.\n");
      return MS_FAILURE;
    }
    
    /* Adjust MapServer pixel model to GDAL pixel model */
    mapRect.minx -= map_cellsize_x*0.5;
    mapRect.maxx += map_cellsize_x*0.5;
    mapRect.miny -= map_cellsize_y*0.5;
    mapRect.maxy += map_cellsize_y*0.5;


    /*
     * If raw data cellsize (from geotransform) is larger than output map_cellsize
     * then we want to extract only enough data to match the output map resolution
     * which means that GDAL will automatically sample the data on read.
     *
     * To prevent bad contour effects on tile edges, we adjust the target cellsize 
     * to align the extracted window with a virtual grid based on the origin of the 
     * raw data and a virtual grid step size corresponding to an integer sampling step.
     *
     * If source data has a greater cellsize (i.e. lower res) that requested ouptut map
     * then we use the raw data cellsize as target cellsize since there is no point in 
     * interpolating the data for contours in this case.
     */

    virtual_grid_step_x = (int)floor(map_cellsize_x / ABS(adfGeoTransform[1]));
    if (virtual_grid_step_x < 1)
      virtual_grid_step_x = 1; /* Do not interpolate data if grid sampling step < 1 */

    virtual_grid_step_y = (int)floor(map_cellsize_y / ABS(adfGeoTransform[5]));
    if (virtual_grid_step_y < 1)
      virtual_grid_step_y = 1; /* Do not interpolate data if grid sampling step < 1 */
    
    /* target cellsize is a multiple of raw data cellsize based on grid step*/
    dst_cellsize_x = ABS(adfGeoTransform[1]) * virtual_grid_step_x;
    dst_cellsize_y = ABS(adfGeoTransform[5]) * virtual_grid_step_y;

    /* Compute overlap between source and target views */

    copyRect = mapRect;

    if (copyRect.minx < GEO_TRANS(adfGeoTransform,0,src_ysize))
      copyRect.minx = GEO_TRANS(adfGeoTransform,0,src_ysize);
    if (copyRect.maxx > GEO_TRANS(adfGeoTransform,src_xsize,0))
      copyRect.maxx = GEO_TRANS(adfGeoTransform,src_xsize,0);
    if (copyRect.miny < GEO_TRANS(adfGeoTransform+3,0,src_ysize))
      copyRect.miny = GEO_TRANS(adfGeoTransform+3,0,src_ysize);
    if (copyRect.maxy > GEO_TRANS(adfGeoTransform+3,src_xsize,0))
      copyRect.maxy = GEO_TRANS(adfGeoTransform+3,src_xsize,0);
    
    if (copyRect.minx >= copyRect.maxx || copyRect.miny >= copyRect.maxy) {
      if (layer->debug)
        msDebug("msContourLayerReadRaster(): Error in overlap calculation.\n");
      return MS_FAILURE;
    }

    /*
     * Convert extraction window to raster coordinates
     */
    llx = GEO_TRANS(adfInvGeoTransform+0,copyRect.minx,copyRect.miny);
    lly = GEO_TRANS(adfInvGeoTransform+3,copyRect.minx,copyRect.miny);
    urx = GEO_TRANS(adfInvGeoTransform+0,copyRect.maxx,copyRect.maxy);
    ury = GEO_TRANS(adfInvGeoTransform+3,copyRect.maxx,copyRect.maxy);

    /* 
     * Align extraction window with virtual grid 
     * (keep in mind raster coordinates origin is at upper-left)
     * We also add an extra buffer to fix tile boundarie issues when zoomed
     */
    llx = floor(llx / virtual_grid_step_x) * virtual_grid_step_x - (virtual_grid_step_x*5);
    urx = ceil(urx / virtual_grid_step_x) * virtual_grid_step_x + (virtual_grid_step_x*5);
    ury = floor(ury / virtual_grid_step_y) * virtual_grid_step_y - (virtual_grid_step_x*5);
    lly = ceil(lly / virtual_grid_step_y) * virtual_grid_step_y + (virtual_grid_step_x*5);
    
    src_xoff = MAX(0,(int) floor(llx+0.5));
    src_yoff = MAX(0,(int) floor(ury+0.5));
    src_xsize = MIN(MAX(0,(int) (urx - llx + 0.5)),
                    GDALGetRasterXSize(clinfo->hOrigDS) - src_xoff);
    src_ysize = MIN(MAX(0,(int) (lly - ury + 0.5)),
                    GDALGetRasterYSize(clinfo->hOrigDS) - src_yoff);

    /* Update the geographic extent (buffer added) */
    /* TODO: a better way to go the geo_trans */
    copyRect.minx = GEO_TRANS(adfGeoTransform+0,src_xoff,0);
    copyRect.maxx = GEO_TRANS(adfGeoTransform+0,src_xoff+src_xsize,0);
    copyRect.miny = GEO_TRANS(adfGeoTransform+3,0,src_yoff+src_ysize);
    copyRect.maxy = GEO_TRANS(adfGeoTransform+3,0,src_yoff);
    
    /* 
     * If input window is to small then stop here
     */
    if (src_xsize < 2 || src_ysize < 2)
    {
      if (layer->debug)
        msDebug("msContourLayerReadRaster(): input window too small, or no apparent overlap between map view and this window(1).\n");
      return MS_FAILURE;
    }

    /* Target buffer size */
    dst_xsize = (int)ceil((copyRect.maxx - copyRect.minx) / dst_cellsize_x);
    dst_ysize = (int)ceil((copyRect.maxy - copyRect.miny) / dst_cellsize_y);

    if (dst_xsize == 0 || dst_ysize == 0) {
      if (layer->debug)
        msDebug("msContourLayerReadRaster(): no apparent overlap between map view and this window(2).\n");
      return MS_FAILURE;
    }

    if (layer->debug)
      msDebug( "msContourLayerReadRaster(): src=%d,%d,%d,%d, dst=%d,%d,%d,%d\n",
               src_xoff, src_yoff, src_xsize, src_ysize,
               0, 0, dst_xsize, dst_ysize );
  } else {
    src_xoff = 0;
    src_yoff = 0;
    dst_xsize = src_xsize = MIN(map->width,src_xsize);
    dst_ysize = src_ysize = MIN(map->height,src_ysize);
  }

  /* -------------------------------------------------------------------- */
  /*      Allocate buffer, and read data into it.                         */
  /* -------------------------------------------------------------------- */

  clinfo->buffer = (double *) malloc(sizeof(double) * dst_xsize * dst_ysize);
  if (clinfo->buffer == NULL) {
    msSetError(MS_MEMERR, "Malloc(): Out of memory.", "msContourLayerReadRaster()");
    return MS_FAILURE;
  }

  eErr = GDALRasterIO(hBand, GF_Read,
                      src_xoff, src_yoff, src_xsize, src_ysize,
                      clinfo->buffer, dst_xsize, dst_ysize, GDT_Float64,
                      0, 0);

  if (eErr != CE_None) {
    msSetError( MS_IOERR, "GDALRasterIO() failed: %s",
                "msContourLayerReadRaster()", CPLGetLastErrorMsg() );
    free(clinfo->buffer);
    return MS_FAILURE;
  }

  memset(pointer, 0, sizeof(pointer));
  CPLPrintPointer(pointer, clinfo->buffer, sizeof(pointer));
  sprintf(memDSPointer,"MEM:::DATAPOINTER=%s,PIXELS=%d,LINES=%d,BANDS=1,DATATYPE=Float64",
          pointer, dst_xsize, dst_ysize);
  clinfo->hDS = GDALOpen(memDSPointer, GF_Read);
  if (clinfo->hDS == NULL) {
    msSetError(MS_IMGERR,
               "Unable to open GDAL Memory dataset.",
               "msContourLayerReadRaster()");
    free(clinfo->buffer);
    return MS_FAILURE;
  }

  adfGeoTransform[0] = copyRect.minx;
  adfGeoTransform[1] = dst_cellsize_x;
  adfGeoTransform[2] = 0;
  adfGeoTransform[3] = copyRect.maxy;
  adfGeoTransform[4] = 0;
  adfGeoTransform[5] = -dst_cellsize_y;

  clinfo->cellsize = MAX(dst_cellsize_x, dst_cellsize_y);
  {
    char buf[64];
    sprintf(buf, "%lf", clinfo->cellsize);
    msInsertHashTable(&layer->metadata, "__data_cellsize__", buf);
  }
      
  GDALSetGeoTransform(clinfo->hDS, adfGeoTransform);
  return MS_SUCCESS;
}