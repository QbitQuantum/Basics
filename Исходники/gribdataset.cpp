void GRIBDataset::SetGribMetaData(grib_MetaData* meta)
{
    nRasterXSize = meta->gds.Nx;
    nRasterYSize = meta->gds.Ny;

/* -------------------------------------------------------------------- */
/*      Image projection.                                               */
/* -------------------------------------------------------------------- */
    OGRSpatialReference oSRS;

    switch(meta->gds.projType)
    {
      case GS3_LATLON:
      case GS3_GAUSSIAN_LATLON:
          // No projection, only latlon system (geographic)
          break;
      case GS3_MERCATOR:
        oSRS.SetMercator(meta->gds.meshLat, meta->gds.orientLon,
                         1.0, 0.0, 0.0);
        break;
      case GS3_POLAR:
        oSRS.SetPS(meta->gds.meshLat, meta->gds.orientLon,
                   meta->gds.scaleLat1,
                   0.0, 0.0);
        break;
      case GS3_LAMBERT:
        oSRS.SetLCC(meta->gds.scaleLat1, meta->gds.scaleLat2,
                    0.0, meta->gds.orientLon,
                    0.0, 0.0); // set projection
        break;
			

      case GS3_ORTHOGRAPHIC:

        //oSRS.SetOrthographic(0.0, meta->gds.orientLon,
        //											meta->gds.lon2, meta->gds.lat2);
        //oSRS.SetGEOS(meta->gds.orientLon, meta->gds.stretchFactor, meta->gds.lon2, meta->gds.lat2);
        oSRS.SetGEOS(  0, 35785831, 0, 0 ); // hardcoded for now, I don't know yet how to parse the meta->gds section
        break;
      case GS3_EQUATOR_EQUIDIST:
        break;
      case GS3_AZIMUTH_RANGE:
        break;
    }

/* -------------------------------------------------------------------- */
/*      Earth model                                                     */
/* -------------------------------------------------------------------- */
    double a = meta->gds.majEarth * 1000.0; // in meters
    double b = meta->gds.minEarth * 1000.0;
    if( a == 0 && b == 0 )
    {
        a = 6377563.396;
        b = 6356256.910;
    }

    if (meta->gds.f_sphere)
    {
        oSRS.SetGeogCS( "Coordinate System imported from GRIB file",
                        NULL,
                        "Sphere",
                        a, 0.0 );
    }
    else
    {
        double fInv = a/(a-b);
        oSRS.SetGeogCS( "Coordinate System imported from GRIB file",
                        NULL,
                        "Spheroid imported from GRIB file",
                        a, fInv );
    }

    OGRSpatialReference oLL; // construct the "geographic" part of oSRS
    oLL.CopyGeogCSFrom( &oSRS );

    double rMinX;
    double rMaxY;
    double rPixelSizeX;
    double rPixelSizeY;
    if (meta->gds.projType == GS3_ORTHOGRAPHIC)
    {
        //rMinX = -meta->gds.Dx * (meta->gds.Nx / 2); // This is what should work, but it doesn't .. Dx seems to have an inverse relation with pixel size
        //rMaxY = meta->gds.Dy * (meta->gds.Ny / 2);
        const double geosExtentInMeters = 11137496.552; // hardcoded for now, assumption: GEOS projection, full disc (like MSG)
        rMinX = -(geosExtentInMeters / 2);
        rMaxY = geosExtentInMeters / 2;
        rPixelSizeX = geosExtentInMeters / meta->gds.Nx;
        rPixelSizeY = geosExtentInMeters / meta->gds.Ny;
    }
    else if( oSRS.IsProjected() )
    {
        rMinX = meta->gds.lon1; // longitude in degrees, to be transformed to meters (or degrees in case of latlon)
        rMaxY = meta->gds.lat1; // latitude in degrees, to be transformed to meters 
        OGRCoordinateTransformation *poTransformLLtoSRS = OGRCreateCoordinateTransformation( &(oLL), &(oSRS) );
        if ((poTransformLLtoSRS != NULL) && poTransformLLtoSRS->Transform( 1, &rMinX, &rMaxY )) // transform it to meters
        {
            if (meta->gds.scan == GRIB2BIT_2) // Y is minY, GDAL wants maxY
                rMaxY += (meta->gds.Ny - 1) * meta->gds.Dy; // -1 because we GDAL needs the coordinates of the centre of the pixel
            rPixelSizeX = meta->gds.Dx;
            rPixelSizeY = meta->gds.Dy;
        }
        else
        {
            rMinX = 0.0;
            rMaxY = 0.0;
            
            rPixelSizeX = 1.0;
            rPixelSizeY = -1.0;
            
            oSRS.Clear();

            CPLError( CE_Warning, CPLE_AppDefined,
                      "Unable to perform coordinate transformations, so the correct\n"
                      "projected geotransform could not be deduced from the lat/long\n"
                      "control points.  Defaulting to ungeoreferenced." );
        }
        delete poTransformLLtoSRS;
    }
    else
    {
        rMinX = meta->gds.lon1; // longitude in degrees, to be transformed to meters (or degrees in case of latlon)
        rMaxY = meta->gds.lat1; // latitude in degrees, to be transformed to meters 

        if (meta->gds.lat2 > rMaxY)
          rMaxY = meta->gds.lat2;
        rPixelSizeX = meta->gds.Dx;
        rPixelSizeY = meta->gds.Dy;
    }

    adfGeoTransform[0] = rMinX;
    adfGeoTransform[3] = rMaxY;
    adfGeoTransform[1] = rPixelSizeX;
    adfGeoTransform[5] = -rPixelSizeY;

    CPLFree( pszProjection );
    pszProjection = NULL;
    oSRS.exportToWkt( &(pszProjection) );
}