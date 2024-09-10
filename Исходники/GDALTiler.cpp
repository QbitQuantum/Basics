GDALTiler::GDALTiler(GDALDataset *poDataset, const Grid &grid, const TilerOptions &options):
  mGrid(grid),
  poDataset(poDataset),
  options(options)
{

  // Transformed bounds can give slightly different results on different threads unless mutexed
  static std::mutex mutex;
  std::lock_guard<std::mutex> lock(mutex);

  // if the dataset is set we need to initialise the tile bounds and raster
  // resolution from it.
  if (poDataset != NULL) {

    // Get the bounds of the dataset
    double adfGeoTransform[6];
    CRSBounds bounds;

    if (poDataset->GetGeoTransform(adfGeoTransform) == CE_None) {
      bounds = CRSBounds(adfGeoTransform[0],
                         adfGeoTransform[3] + (poDataset->GetRasterYSize() * adfGeoTransform[5]),
                         adfGeoTransform[0] + (poDataset->GetRasterXSize() * adfGeoTransform[1]),
                         adfGeoTransform[3]);
    } else {
      throw CTBException("Could not get transformation information from source dataset");
    }

    // Find out whether the dataset SRS matches that of the grid
    const char *srcWKT = poDataset->GetProjectionRef();
    if (!strlen(srcWKT))
      throw CTBException("The source dataset does not have a spatial reference system assigned");

    OGRSpatialReference srcSRS = OGRSpatialReference(srcWKT);
    OGRSpatialReference gridSRS = mGrid.getSRS();

    if (!srcSRS.IsSame(&gridSRS)) { // it doesn't match
      // Check the srs is valid
      switch(srcSRS.Validate()) {
      case OGRERR_NONE:
        break;
      case OGRERR_CORRUPT_DATA:
        throw CTBException("The source spatial reference system appears to be corrupted");
        break;
      case OGRERR_UNSUPPORTED_SRS:
        throw CTBException("The source spatial reference system is not supported");
        break;
      default:
        throw CTBException("There is an unhandled return value from `srcSRS.Validate()`");
      }

      // We need to transform the bounds to the grid SRS
      double x[4] = { bounds.getMinX(), bounds.getMaxX(), bounds.getMaxX(), bounds.getMinX() };
      double y[4] = { bounds.getMinY(), bounds.getMinY(), bounds.getMaxY(), bounds.getMaxY() };

      OGRCoordinateTransformation *transformer = OGRCreateCoordinateTransformation(&srcSRS, &gridSRS);
      if (transformer == NULL) {
        throw CTBException("The source dataset to tile grid coordinate transformation could not be created");
      } else if (transformer->Transform(4, x, y) != true) {
        delete transformer;
        throw CTBException("Could not transform dataset bounds to tile spatial reference system");
      }
      delete transformer;

      // Get the min and max values of the transformed coordinates
      double minX = std::min(std::min(x[0], x[1]), std::min(x[2], x[3])),
        maxX = std::max(std::max(x[0], x[1]), std::max(x[2], x[3])),
        minY = std::min(std::min(y[0], y[1]), std::min(y[2], y[3])),
        maxY = std::max(std::max(y[0], y[1]), std::max(y[2], y[3]));

      mBounds = CRSBounds(minX, minY, maxX, maxY); // set the bounds
      mResolution = mBounds.getWidth() / poDataset->GetRasterXSize(); // set the resolution

      // cache the SRS string for use in reprojections later
      char *srsWKT = NULL;
      if (gridSRS.exportToWkt(&srsWKT) != OGRERR_NONE) {
        CPLFree(srsWKT);
        throw CTBException("Could not create grid WKT string");
      }
      crsWKT = srsWKT;
      CPLFree(srsWKT);
      srsWKT = NULL;

    } else {                    // no reprojection is necessary
      mBounds = bounds;         // use the existing dataset bounds
      mResolution = std::abs(adfGeoTransform[1]); // use the existing dataset resolution
    }

    poDataset->Reference();     // increase the refcount of the dataset
  }
}