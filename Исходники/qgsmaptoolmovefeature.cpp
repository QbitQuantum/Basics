void QgsMapToolMoveFeature::cadCanvasReleaseEvent( QgsMapMouseEvent *e )
{
  QgsVectorLayer *vlayer = currentVectorLayer();
  if ( !vlayer || !vlayer->isEditable() )
  {
    delete mRubberBand;
    mRubberBand = nullptr;
    mSnapIndicator->setMatch( QgsPointLocator::Match() );
    cadDockWidget()->clear();
    notifyNotEditableLayer();
    return;
  }

  if ( !mRubberBand )
  {
    //find first geometry under mouse cursor and store iterator to it
    QgsPointXY layerCoords = toLayerCoordinates( vlayer, e->mapPoint() );
    double searchRadius = QgsTolerance::vertexSearchRadius( mCanvas->currentLayer(), mCanvas->mapSettings() );
    QgsRectangle selectRect( layerCoords.x() - searchRadius, layerCoords.y() - searchRadius,
                             layerCoords.x() + searchRadius, layerCoords.y() + searchRadius );

    if ( vlayer->selectedFeatureCount() == 0 )
    {
      QgsFeatureIterator fit = vlayer->getFeatures( QgsFeatureRequest().setFilterRect( selectRect ).setNoAttributes() );

      //find the closest feature
      QgsGeometry pointGeometry = QgsGeometry::fromPointXY( layerCoords );
      if ( pointGeometry.isNull() )
      {
        cadDockWidget()->clear();
        return;
      }

      double minDistance = std::numeric_limits<double>::max();

      QgsFeature cf;
      QgsFeature f;
      while ( fit.nextFeature( f ) )
      {
        if ( f.hasGeometry() )
        {
          double currentDistance = pointGeometry.distance( f.geometry() );
          if ( currentDistance < minDistance )
          {
            minDistance = currentDistance;
            cf = f;
          }
        }
      }

      if ( minDistance == std::numeric_limits<double>::max() )
      {
        cadDockWidget()->clear();
        return;
      }

      mMovedFeatures.clear();
      mMovedFeatures << cf.id(); //todo: take the closest feature, not the first one...

      mRubberBand = createRubberBand( vlayer->geometryType() );
      mRubberBand->setToGeometry( cf.geometry(), vlayer );
    }
    else
    {
      mMovedFeatures = vlayer->selectedFeatureIds();

      mRubberBand = createRubberBand( vlayer->geometryType() );
      QgsFeature feat;
      QgsFeatureIterator it = vlayer->getSelectedFeatures( QgsFeatureRequest().setNoAttributes() );

      bool allFeaturesInView = true;
      QgsRectangle viewRect = mCanvas->mapSettings().mapToLayerCoordinates( vlayer, mCanvas->extent() );

      while ( it.nextFeature( feat ) )
      {
        mRubberBand->addGeometry( feat.geometry(), vlayer );

        if ( allFeaturesInView && !viewRect.intersects( feat.geometry().boundingBox() ) )
          allFeaturesInView = false;
      }

      if ( !allFeaturesInView )
      {
        // for extra safety to make sure we are not modifying geometries by accident

        int res = QMessageBox::warning( mCanvas, tr( "Move features" ),
                                        tr( "Some of the selected features are outside of the current map view. Would you still like to continue?" ),
                                        QMessageBox::Yes | QMessageBox::No );
        if ( res != QMessageBox::Yes )
        {
          mMovedFeatures.clear();
          delete mRubberBand;
          mRubberBand = nullptr;
          mSnapIndicator->setMatch( QgsPointLocator::Match() );
          return;
        }
      }
    }

    mStartPointMapCoords = e->mapPoint();
    mRubberBand->show();
  }
  else
  {
    // copy and move mode
    if ( e->button() != Qt::LeftButton )
    {
      cadDockWidget()->clear();
      delete mRubberBand;
      mRubberBand = nullptr;
      mSnapIndicator->setMatch( QgsPointLocator::Match() );
      return;
    }

    QgsPointXY startPointLayerCoords = toLayerCoordinates( ( QgsMapLayer * )vlayer, mStartPointMapCoords );
    QgsPointXY stopPointLayerCoords = toLayerCoordinates( ( QgsMapLayer * )vlayer, e->mapPoint() );

    double dx = stopPointLayerCoords.x() - startPointLayerCoords.x();
    double dy = stopPointLayerCoords.y() - startPointLayerCoords.y();

    vlayer->beginEditCommand( mMode == Move ? tr( "Feature moved" ) : tr( "Feature copied and moved" ) );

    switch ( mMode )
    {
      case Move:
        Q_FOREACH ( QgsFeatureId id, mMovedFeatures )
        {
          vlayer->translateFeature( id, dx, dy );
        }
        delete mRubberBand;
        mRubberBand = nullptr;
        mSnapIndicator->setMatch( QgsPointLocator::Match() );
        cadDockWidget()->clear();
        break;

      case CopyMove:
        QgsFeatureRequest request;
        request.setFilterFids( mMovedFeatures );
        QString *errorMsg = new QString();
        if ( !QgisApp::instance()->vectorLayerTools()->copyMoveFeatures( vlayer, request, dx, dy, errorMsg ) )
        {
          emit messageEmitted( *errorMsg, Qgis::Critical );
          delete mRubberBand;
          mRubberBand = nullptr;
          mSnapIndicator->setMatch( QgsPointLocator::Match() );
        }
        break;
    }

    vlayer->endEditCommand();
    vlayer->triggerRepaint();
  }