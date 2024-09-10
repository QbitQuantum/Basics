QgsVectorLayerImport::ImportError
QgsVectorLayerImport::importLayer( QgsVectorLayer* layer,
                                   const QString& uri,
                                   const QString& providerKey,
                                   const QgsCoordinateReferenceSystem *destCRS,
                                   bool onlySelected,
                                   QString *errorMessage,
                                   bool skipAttributeCreation,
                                   QMap<QString, QVariant> *options,
                                   QProgressDialog *progress )
{
  const QgsCoordinateReferenceSystem* outputCRS;
  QgsCoordinateTransform* ct = nullptr;
  bool shallTransform = false;

  if ( !layer )
    return ErrInvalidLayer;

  if ( destCRS && destCRS->isValid() )
  {
    // This means we should transform
    outputCRS = destCRS;
    shallTransform = true;
  }
  else
  {
    // This means we shouldn't transform, use source CRS as output (if defined)
    outputCRS = &layer->crs();
  }


  bool overwrite = false;
  bool forceSinglePartGeom = false;
  if ( options )
  {
    overwrite = options->take( "overwrite" ).toBool();
    forceSinglePartGeom = options->take( "forceSinglePartGeometryType" ).toBool();
  }

  QgsFields fields = skipAttributeCreation ? QgsFields() : layer->fields();
  QGis::WkbType wkbType = layer->wkbType();

  // Special handling for Shapefiles
  if ( layer->providerType() == "ogr" && layer->storageType() == "ESRI Shapefile" )
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
        case QGis::WKBPoint:
          wkbType = QGis::WKBMultiPoint;
          break;
        case QGis::WKBLineString:
          wkbType = QGis::WKBMultiLineString;
          break;
        case QGis::WKBPolygon:
          wkbType = QGis::WKBMultiPolygon;
          break;
        case QGis::WKBPoint25D:
          wkbType = QGis::WKBMultiPoint25D;
          break;
        case QGis::WKBLineString25D:
          wkbType = QGis::WKBMultiLineString25D;
          break;
        case QGis::WKBPolygon25D:
          wkbType = QGis::WKBMultiPolygon25D;
          break;
        default:
          break;
      }
    }
  }

  QgsVectorLayerImport * writer =
    new QgsVectorLayerImport( uri, providerKey, fields, wkbType, outputCRS, overwrite, options, progress );

  // check whether file creation was successful
  ImportError err = writer->hasError();
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

  QgsAttributeList allAttr = skipAttributeCreation ? QgsAttributeList() : layer->attributeList();
  QgsFeature fet;

  QgsFeatureRequest req;
  if ( wkbType == QGis::WKBNoGeometry )
    req.setFlags( QgsFeatureRequest::NoGeometry );
  if ( skipAttributeCreation )
    req.setSubsetOfAttributes( QgsAttributeList() );

  QgsFeatureIterator fit = layer->getFeatures( req );

  const QgsFeatureIds& ids = layer->selectedFeaturesIds();

  // Create our transform
  if ( destCRS )
    ct = new QgsCoordinateTransform( layer->crs(), *destCRS );

  // Check for failure
  if ( !ct )
    shallTransform = false;

  int n = 0;

  if ( errorMessage )
  {
    *errorMessage = QObject::tr( "Feature write errors:" );
  }

  if ( progress )
  {
    progress->setRange( 0, layer->featureCount() );
  }

  // write all features
  while ( fit.nextFeature( fet ) )
  {
    if ( progress && progress->wasCanceled() )
    {
      if ( errorMessage )
      {
        *errorMessage += '\n' + QObject::tr( "Import was canceled at %1 of %2" ).arg( progress->value() ).arg( progress->maximum() );
      }
      break;
    }

    if ( writer->errorCount() > 1000 )
    {
      if ( errorMessage )
      {
        *errorMessage += '\n' + QObject::tr( "Stopping after %1 errors" ).arg( writer->errorCount() );
      }
      break;
    }

    if ( onlySelected && !ids.contains( fet.id() ) )
      continue;

    if ( shallTransform )
    {
      try
      {
        if ( fet.constGeometry() )
        {
          fet.geometry()->transform( *ct );
        }
      }
      catch ( QgsCsException &e )
      {
        delete ct;
        delete writer;

        QString msg = QObject::tr( "Failed to transform a point while drawing a feature with ID '%1'. Writing stopped. (Exception: %2)" )
                      .arg( fet.id() ).arg( e.what() );
        QgsMessageLog::logMessage( msg, QObject::tr( "Vector import" ) );
        if ( errorMessage )
          *errorMessage += '\n' + msg;

        return ErrProjection;
      }
    }
    if ( skipAttributeCreation )
    {
      fet.initAttributes( 0 );
    }
    if ( !writer->addFeature( fet ) )
    {
      if ( writer->hasError() && errorMessage )
      {
        *errorMessage += '\n' + writer->errorMessage();
      }
    }
    n++;

    if ( progress )
    {
      progress->setValue( n );
    }
  }

  // flush the buffer to be sure that all features are written
  if ( !writer->flushBuffer() )
  {
    if ( writer->hasError() && errorMessage )
    {
      *errorMessage += '\n' + writer->errorMessage();
    }
  }
  int errors = writer->errorCount();

  if ( !writer->createSpatialIndex() )
  {
    if ( writer->hasError() && errorMessage )
    {
      *errorMessage += '\n' + writer->errorMessage();
    }
  }

  delete writer;

  if ( shallTransform )
  {
    delete ct;
  }

  if ( errorMessage )
  {
    if ( errors > 0 )
    {
      *errorMessage += '\n' + QObject::tr( "Only %1 of %2 features written." ).arg( n - errors ).arg( n );
    }
    else
    {
      errorMessage->clear();
    }
  }

  return errors == 0 ? NoError : ErrFeatureWriteFailed;
}