void QgsGeometryCheckerResultTab::highlightErrors( bool current )
{
  qDeleteAll( mCurrentRubberBands );
  mCurrentRubberBands.clear();

  QList<QTableWidgetItem*> items;
  QList<QgsPoint> errorPositions;
  QgsRectangle totextent;

  if ( current )
  {
    items.append( ui.tableWidgetErrors->currentItem() );
  }
  else
  {
    items.append( ui.tableWidgetErrors->selectedItems() );
  }
  foreach ( QTableWidgetItem* item, items )
  {
    QgsGeometryCheckError* error = ui.tableWidgetErrors->item( item->row(), 0 )->data( Qt::UserRole ).value<QgsGeometryCheckError*>();

    QgsAbstractGeometryV2* geometry = error->geometry();
    if ( ui.checkBoxHighlight->isChecked() && geometry )
    {
      QgsRubberBand* featureRubberBand = new QgsRubberBand( mIface->mapCanvas() );
      QgsGeometry geom( geometry );
      featureRubberBand->addGeometry( &geom, mFeaturePool->getLayer() );
      featureRubberBand->setWidth( 5 );
      featureRubberBand->setColor( Qt::yellow );
      mCurrentRubberBands.append( featureRubberBand );
    }
    else
    {
      // QgsGeometry above takes ownership of geometry and deletes it when it goes out of scope
      delete geometry;
      geometry = 0;
    }

    if ( ui.radioButtonError->isChecked() || current || error->status() == QgsGeometryCheckError::StatusFixed )
    {
      QgsRubberBand* pointRubberBand = new QgsRubberBand( mIface->mapCanvas(), QGis::Point );
      QgsPoint pos = mIface->mapCanvas()->mapSettings().layerToMapCoordinates( mFeaturePool->getLayer(), QgsPoint( error->location().x(), error->location().y() ) );
      pointRubberBand->addPoint( pos );
      pointRubberBand->setWidth( 20 );
      pointRubberBand->setColor( Qt::red );
      mCurrentRubberBands.append( pointRubberBand );
      errorPositions.append( pos );
    }
    else if ( ui.radioButtonFeature->isChecked() && geometry )
    {
      QgsRectangle geomextent = mIface->mapCanvas()->mapSettings().layerExtentToOutputExtent( mFeaturePool->getLayer(), geometry->boundingBox() );
      if ( totextent.isEmpty() )
      {
        totextent = geomextent;
      }
      else
      {
        totextent.unionRect( geomextent );
      }
    }
  }