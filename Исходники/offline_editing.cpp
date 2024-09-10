void QgsOfflineEditing::copyVectorLayer( QgsVectorLayer* layer, sqlite3* db, const QString& offlineDbPath )
{
  if ( layer == NULL )
  {
    return;
  }

  QString tableName = layer->name();

  // create table
  QString sql = QString( "CREATE TABLE '%1' (" ).arg( tableName );
  QString delim = "";
  const QgsFieldMap& fields = layer->dataProvider()->fields();
  for ( QgsFieldMap::const_iterator it = fields.begin(); it != fields.end() ; ++it )
  {
    QString dataType = "";
    QVariant::Type type = it.value().type();
    if ( type == QVariant::Int )
    {
      dataType = "INTEGER";
    }
    else if ( type == QVariant::Double )
    {
      dataType = "REAL";
    }
    else if ( type == QVariant::String )
    {
      dataType = "TEXT";
    }
    else
    {
      showWarning( tr( "Unknown data type %1" ).arg( type ) );
    }

    sql += delim + QString( "'%1' %2" ).arg( it.value().name() ).arg( dataType );
    delim = ",";
  }
  sql += ")";

  // add geometry column
  QString geomType = "";
  switch ( layer->wkbType() )
  {
    case QGis::WKBPoint:
      geomType = "POINT";
      break;
    case QGis::WKBMultiPoint:
      geomType = "MULTIPOINT";
      break;
    case QGis::WKBLineString:
      geomType = "LINESTRING";
      break;
    case QGis::WKBMultiLineString:
      geomType = "MULTILINESTRING";
      break;
    case QGis::WKBPolygon:
      geomType = "POLYGON";
      break;
    case QGis::WKBMultiPolygon:
      geomType = "MULTIPOLYGON";
      break;
    default:
      showWarning( tr( "QGIS wkbType %1 not supported" ).arg( layer->wkbType() ) );
      break;
  };
  QString sqlAddGeom = QString( "SELECT AddGeometryColumn('%1', 'Geometry', %2, '%3', 2)" )
                       .arg( tableName )
                       .arg( layer->crs().authid().startsWith( "EPSG:", Qt::CaseInsensitive ) ? layer->crs().authid().mid( 5 ).toLong() : 0 )
                       .arg( geomType );

  // create spatial index
  QString sqlCreateIndex = QString( "SELECT CreateSpatialIndex('%1', 'Geometry')" ).arg( tableName );

  int rc = sqlExec( db, sql );
  if ( rc == SQLITE_OK )
  {
    rc = sqlExec( db, sqlAddGeom );
    if ( rc == SQLITE_OK )
    {
      rc = sqlExec( db, sqlCreateIndex );
    }
  }

  if ( rc == SQLITE_OK )
  {
    // add new layer
    QgsVectorLayer* newLayer = new QgsVectorLayer( QString( "dbname='%1' table='%2'(Geometry) sql=" )
        .arg( offlineDbPath ).arg( tableName ), tableName + " (offline)", "spatialite" );
    if ( newLayer->isValid() )
    {
      // mark as offline layer
      newLayer->setCustomProperty( CUSTOM_PROPERTY_IS_OFFLINE_EDITABLE, true );

      // store original layer source
      newLayer->setCustomProperty( CUSTOM_PROPERTY_REMOTE_SOURCE, layer->source() );
      newLayer->setCustomProperty( CUSTOM_PROPERTY_REMOTE_PROVIDER, layer->providerType() );

      // copy style
      bool hasLabels = layer->hasLabelsEnabled();
      if ( !hasLabels )
      {
        // NOTE: copy symbology before adding the layer so it is displayed correctly
        copySymbology( layer, newLayer );
      }

      // register this layer with the central layers registry
      QgsMapLayerRegistry::instance()->addMapLayer( newLayer );

      if ( hasLabels )
      {
        // NOTE: copy symbology of layers with labels enabled after adding to project, as it will crash otherwise (WORKAROUND)
        copySymbology( layer, newLayer );
      }

      // TODO: layer order

      // copy features
      newLayer->startEditing();
      QgsFeature f;

      // NOTE: force feature recount for PostGIS layer, else only visible features are counted, before iterating over all features (WORKAROUND)
      layer->setSubsetString( "" );

      layer->select( layer->pendingAllAttributesList(), QgsRectangle(), true, false );

      mProgressDialog->setupProgressBar( tr( "%v / %m features copied" ), layer->featureCount() );
      int featureCount = 1;

      QList<int> remoteFeatureIds;
      while ( layer->nextFeature( f ) )
      {
        remoteFeatureIds << f.id();

        // NOTE: Spatialite provider ignores position of geometry column
        // fill gap in QgsAttributeMap if geometry column is not last (WORKAROUND)
        int column = 0;
        QgsAttributeMap newAttrMap;
        QgsAttributeMap attrMap = f.attributeMap();
        for ( QgsAttributeMap::const_iterator it = attrMap.begin(); it != attrMap.end(); ++it )
        {
          newAttrMap.insert( column++, it.value() );
        }
        f.setAttributeMap( newAttrMap );

        newLayer->addFeature( f, false );

        mProgressDialog->setProgressValue( featureCount++ );
      }
      if ( newLayer->commitChanges() )
      {
        mProgressDialog->setupProgressBar( tr( "%v / %m features processed" ), layer->featureCount() );
        featureCount = 1;

        // update feature id lookup
        int layerId = getOrCreateLayerId( db, newLayer->id() );
        QList<int> offlineFeatureIds;
        newLayer->select( QgsAttributeList(), QgsRectangle(), false, false );
        while ( newLayer->nextFeature( f ) )
        {
          offlineFeatureIds << f.id();
        }

        // NOTE: insert fids in this loop, as the db is locked during newLayer->nextFeature()
        sqlExec( db, "BEGIN" );
        for ( int i = 0; i < remoteFeatureIds.size(); i++ )
        {
          addFidLookup( db, layerId, offlineFeatureIds.at( i ), remoteFeatureIds.at( i ) );

          mProgressDialog->setProgressValue( featureCount++ );
        }
        sqlExec( db, "COMMIT" );
      }
      else
      {
        showWarning( newLayer->commitErrors().join( "\n" ) );
      }

      // remove remote layer
      QgsMapLayerRegistry::instance()->removeMapLayer( layer->id() );
    }
  }
}