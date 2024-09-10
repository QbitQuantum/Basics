void QgsMapToolRotateFeature::canvasReleaseEvent( QgsMapMouseEvent *e )
{
  if ( !mCanvas )
  {
    return;
  }

  QgsVectorLayer *vlayer = currentVectorLayer();
  if ( !vlayer )
  {
    deleteRotationWidget();
    deleteRubberband();
    notifyNotVectorLayer();
    return;
  }

  if ( e->button() == Qt::RightButton )
  {
    cancel();
    return;
  }

  // place anchor point on CTRL + click
  if ( e->modifiers() & Qt::ControlModifier )
  {
    if ( !mAnchorPoint )
    {
      return;
    }
    mAnchorPoint->setCenter( toMapCoordinates( e->pos() ) );
    mStartPointMapCoords = toMapCoordinates( e->pos() );
    mStPoint = e->pos();
    return;
  }

  deleteRotationWidget();

  // Initialize rotation if not yet active
  if ( !mRotationActive )
  {
    mRotation = 0;
    mRotationOffset = 0;

    deleteRubberband();

    mInitialPos = e->pos();

    if ( !vlayer->isEditable() )
    {
      notifyNotEditableLayer();
      return;
    }

    QgsPointXY layerCoords = toLayerCoordinates( vlayer, e->pos() );
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
        emit messageEmitted( tr( "Could not find a nearby feature in the current layer." ) );
        return;
      }

      QgsRectangle bound = cf.geometry().boundingBox();
      mStartPointMapCoords = toMapCoordinates( vlayer, bound.center() );

      if ( !mAnchorPoint )
      {
        mAnchorPoint = qgis::make_unique<QgsVertexMarker>( mCanvas );
      }
      mAnchorPoint->setIconType( QgsVertexMarker::ICON_CROSS );
      mAnchorPoint->setCenter( mStartPointMapCoords );

      mStPoint = toCanvasCoordinates( mStartPointMapCoords );

      mRotatedFeatures.clear();
      mRotatedFeatures << cf.id(); //todo: take the closest feature, not the first one...

      mRubberBand = createRubberBand( vlayer->geometryType() );
      mRubberBand->setToGeometry( cf.geometry(), vlayer );
    }
    else
    {
      mRotatedFeatures = vlayer->selectedFeatureIds();

      mRubberBand = createRubberBand( vlayer->geometryType() );

      QgsFeature feat;
      QgsFeatureIterator it = vlayer->getSelectedFeatures();
      while ( it.nextFeature( feat ) )
      {
        mRubberBand->addGeometry( feat.geometry(), vlayer );
      }
    }

    mRubberBand->show();

    double XDistance = mInitialPos.x() - mAnchorPoint->x();
    double YDistance = mInitialPos.y() - mAnchorPoint->y();
    mRotationOffset = std::atan2( YDistance, XDistance ) * ( 180 / M_PI );

    createRotationWidget();
    if ( e->modifiers() & Qt::ShiftModifier )
    {
      if ( mRotationWidget )
      {
        mRotationWidget->setMagnet( 45 );
      }
    }

    mRotationActive = true;

    return;
  }

  applyRotation( mRotation );
}