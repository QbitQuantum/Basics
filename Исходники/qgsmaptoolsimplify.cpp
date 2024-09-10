void QgsMapToolSimplify::canvasPressEvent( QMouseEvent * e )
{
  QgsVectorLayer * vlayer = currentVectorLayer();

  if ( !vlayer )
  {
    notifyNotVectorLayer();
    return;
  }

  QgsPoint layerCoords = mCanvas->getCoordinateTransform()->toMapPoint( e->pos().x(), e->pos().y() );

  double r = QgsTolerance::vertexSearchRadius( vlayer, mCanvas->mapSettings() );
  QgsRectangle selectRect = QgsRectangle( layerCoords.x() - r, layerCoords.y() - r,
                                          layerCoords.x() + r, layerCoords.y() + r );
  QgsFeatureIterator fit = vlayer->getFeatures( QgsFeatureRequest().setFilterRect( selectRect ).setSubsetOfAttributes( QgsAttributeList() ) );

  QgsGeometry* geometry = QgsGeometry::fromPoint( layerCoords );
  double minDistance = DBL_MAX;
  double currentDistance;

  mSelectedFeature.setValid( false );

  QgsFeature f;
  while ( fit.nextFeature( f ) )
  {
    currentDistance = geometry->distance( *( f.geometry() ) );
    if ( currentDistance < minDistance )
    {
      minDistance = currentDistance;
      mSelectedFeature = f;
    }
  }

  // delete previous rubberband (if any)
  removeRubberBand();

  if ( mSelectedFeature.isValid() )
  {
    if ( mSelectedFeature.geometry()->isMultipart() )
    {
      emit messageEmitted( tr( "Multipart features are not supported for simplification." ), QgsMessageBar::CRITICAL );
      return;
    }

    mRubberBand = new QgsRubberBand( mCanvas );
    mRubberBand->setToGeometry( mSelectedFeature.geometry(), 0 );
    mRubberBand->setColor( QColor( 255, 0, 0, 65 ) );
    mRubberBand->setWidth( 2 );
    mRubberBand->show();
    //calculate boudaries for slidebar
    if ( calculateSliderBoudaries() )
    {
      // show dialog as a non-modal window
      mSimplifyDialog->show();
    }
    else
    {
      emit messageEmitted( tr( "This feature cannot be simplified. Check if feature has enough vertices to be simplified." ), QgsMessageBar::WARNING );
    }
  }
}