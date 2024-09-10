QgsVectorLayerExporter::ExportError
QgsVectorLayerExporter::exportLayer( QgsVectorLayer *layer,
                                     const QString &uri,
                                     const QString &providerKey,
                                     const QgsCoordinateReferenceSystem &destCRS,
                                     bool onlySelected,
                                     QString *errorMessage,
                                     const QMap<QString, QVariant> &options,
                                     QgsFeedback *feedback )
{
  QgsCoordinateReferenceSystem outputCRS;
  QgsCoordinateTransform ct;
  bool shallTransform = false;

  if ( !layer )
    return ErrInvalidLayer;

  if ( destCRS.isValid() )
  {
    // This means we should transform
    outputCRS = destCRS;
    shallTransform = true;
  }
  else
  {
    // This means we shouldn't transform, use source CRS as output (if defined)
    outputCRS = layer->crs();
  }


  bool overwrite = false;
  bool forceSinglePartGeom = false;
  QMap<QString, QVariant> providerOptions = options;
  if ( !options.isEmpty() )
  {
    overwrite = providerOptions.take( QStringLiteral( "overwrite" ) ).toBool();
    forceSinglePartGeom = providerOptions.take( QStringLiteral( "forceSinglePartGeometryType" ) ).toBool();
  }

  QgsFields fields = layer->fields();
  QgsWkbTypes::Type wkbType = layer->wkbType();

  // Special handling for Shapefiles
  if ( layer->providerType() == QLatin1String( "ogr" ) && layer->storageType() == QLatin1String( "ESRI Shapefile" ) )
  {
    // convert field names to lowercase
    for ( int fldIdx = 0; fldIdx < fields.count(); ++fldIdx )
    {
      fields[fldIdx].setName( fields.at( fldIdx ).name().toLower() );
    }

    if ( !forceSinglePartGeom )
    {
      // convert wkbtype to multipart (see #5547)
      switch ( wkbType )
      {
        case QgsWkbTypes::Point:
          wkbType = QgsWkbTypes::MultiPoint;
          break;
        case QgsWkbTypes::LineString:
          wkbType = QgsWkbTypes::MultiLineString;
          break;
        case QgsWkbTypes::Polygon:
          wkbType = QgsWkbTypes::MultiPolygon;
          break;
        case QgsWkbTypes::Point25D:
          wkbType = QgsWkbTypes::MultiPoint25D;
          break;
        case QgsWkbTypes::LineString25D:
          wkbType = QgsWkbTypes::MultiLineString25D;
          break;
        case QgsWkbTypes::Polygon25D:
          wkbType = QgsWkbTypes::MultiPolygon25D;
          break;
        default:
          break;
      }
    }
  }

  QgsVectorLayerExporter *writer =
    new QgsVectorLayerExporter( uri, providerKey, fields, wkbType, outputCRS, overwrite, providerOptions );

  // check whether file creation was successful
  ExportError err = writer->errorCode();
  if ( err != NoError )
  {
    if ( errorMessage )
      *errorMessage = writer->errorMessage();
    delete writer;
    return err;
  }

  if ( errorMessage )
  {
    errorMessage->clear();
  }

  QgsFeature fet;

  QgsFeatureRequest req;
  if ( wkbType == QgsWkbTypes::NoGeometry )
    req.setFlags( QgsFeatureRequest::NoGeometry );
  if ( onlySelected )
    req.setFilterFids( layer->selectedFeatureIds() );

  QgsFeatureIterator fit = layer->getFeatures( req );

  // Create our transform
  if ( destCRS.isValid() )
  {
    Q_NOWARN_DEPRECATED_PUSH
    ct = QgsCoordinateTransform( layer->crs(), destCRS );
    Q_NOWARN_DEPRECATED_POP
  }