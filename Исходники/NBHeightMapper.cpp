int
NBHeightMapper::loadShapeFile(const std::string& file) {
#ifdef HAVE_GDAL
#if GDAL_VERSION_MAJOR < 2
    OGRRegisterAll();
    OGRDataSource* ds = OGRSFDriverRegistrar::Open(file.c_str(), FALSE);
#else
    GDALAllRegister();
    GDALDataset* ds = (GDALDataset*)GDALOpenEx(file.c_str(), GDAL_OF_VECTOR | GA_ReadOnly, NULL, NULL, NULL);
#endif
    if (ds == NULL) {
        throw ProcessError("Could not open shape file '" + file + "'.");
    }

    // begin file parsing
    OGRLayer* layer = ds->GetLayer(0);
    layer->ResetReading();

    // triangle coordinates are stored in WGS84 and later matched with network coordinates in WGS84
    // build coordinate transformation
    OGRSpatialReference* sr_src = layer->GetSpatialRef();
    OGRSpatialReference sr_dest;
    sr_dest.SetWellKnownGeogCS("WGS84");
    OGRCoordinateTransformation* toWGS84 = OGRCreateCoordinateTransformation(sr_src, &sr_dest);
    if (toWGS84 == 0) {
        WRITE_WARNING("Could not create geocoordinates converter; check whether proj.4 is installed.");
    }

    int numFeatures = 0;
    OGRFeature* feature;
    layer->ResetReading();
    while ((feature = layer->GetNextFeature()) != NULL) {
        OGRGeometry* geom = feature->GetGeometryRef();
        assert(geom != 0);

        // @todo gracefull handling of shapefiles with unexpected contents or any error handling for that matter
        assert(std::string(geom->getGeometryName()) == std::string("POLYGON"));
        // try transform to wgs84
        geom->transform(toWGS84);
        OGRLinearRing* cgeom = ((OGRPolygon*) geom)->getExteriorRing();
        // assume TIN with with 4 points and point0 == point3
        assert(cgeom->getNumPoints() == 4);
        PositionVector corners;
        for (int j = 0; j < 3; j++) {
            Position pos((double) cgeom->getX(j), (double) cgeom->getY(j), (double) cgeom->getZ(j));
            corners.push_back(pos);
            myBoundary.add(pos);
        }
        addTriangle(corners);
        numFeatures++;

        /*
        OGRwkbGeometryType gtype = geom->getGeometryType();
        switch (gtype) {
            case wkbPolygon: {
                break;
            }
            case wkbPoint: {
                WRITE_WARNING("got wkbPoint");
                break;
            }
            case wkbLineString: {
                WRITE_WARNING("got wkbLineString");
                break;
            }
            case wkbMultiPoint: {
                WRITE_WARNING("got wkbMultiPoint");
                break;
            }
            case wkbMultiLineString: {
                WRITE_WARNING("got wkbMultiLineString");
                break;
            }
            case wkbMultiPolygon: {
                WRITE_WARNING("got wkbMultiPolygon");
                break;
            }
            default:
                WRITE_WARNING("Unsupported shape type occurred");
            break;
        }
        */
        OGRFeature::DestroyFeature(feature);
    }
#if GDAL_VERSION_MAJOR < 2
    OGRDataSource::DestroyDataSource(ds);
#else
    GDALClose(ds);
#endif
    OCTDestroyCoordinateTransformation(toWGS84);
    OGRCleanupAll();
    return numFeatures;
#else
    UNUSED_PARAMETER(file);
    WRITE_ERROR("Cannot load shape file since SUMO was compiled without GDAL support.");
    return 0;
#endif
}