void QgsSpatialQueryDialog::zoomFeature( QgsVectorLayer* lyr, QgsFeatureId fid )
{
  static QgsVectorLayer* lyrCheck = NULL;
  static bool hasMsg = false;
  if ( ! lyrCheck || lyrCheck != lyr )
  {
    lyrCheck = lyr;
    hasMsg = true;
  }
  else
  {
    hasMsg = false;
  }

  QgsFeature feat;
  if ( !lyr->getFeatures( QgsFeatureRequest().setFilterFid( fid ).setSubsetOfAttributes( QgsAttributeList() ) ).nextFeature( feat ) )
  {
    return;
  }
  if ( !feat.geometry() )
  {
    return;
  }
  // Set system reference
  QgsCoordinateReferenceSystem srsSource = lyr->dataProvider()->crs();
  QgsCoordinateReferenceSystem srcMapcanvas = mIface->mapCanvas()->mapSettings().destinationCrs();
  if ( ! srsSource.isValid() )
  {
    if ( hasMsg )
    {
      QString crsMapcanvas = srcMapcanvas.authid();
      bool isFly = mIface->mapCanvas()->mapSettings().hasCrsTransformEnabled();
      QString msgFly = tr( "Map \"%1\" \"on the fly\" transformation." ).arg( isFly ? tr( "enable" ) : tr( "disable" ) );
      QString msg = tr( "Coordinate reference system(CRS) of\n\"%1\" is invalid(see CRS of provider)." ).arg( lyr->name() );
      msg.append( tr( "\n\nCRS of map is %1.\n%2." ).arg( crsMapcanvas ).arg( msgFly ) );
      msg.append( "\n\nUsing CRS of map for all features!" );

      QMessageBox::warning( this, tr( "Zoom to feature" ), msg, QMessageBox::Ok );
    }
    mIface->mapCanvas()->setExtent( feat.geometry()->boundingBox() );
  }
  else if ( srsSource == srcMapcanvas )
  {
    mIface->mapCanvas()->setExtent( feat.geometry()->boundingBox() );
  }
  else
  {
    QgsCoordinateTransform * coordTransform =  new QgsCoordinateTransform( srsSource, srcMapcanvas );
    QgsRectangle rectExtent = coordTransform->transform( feat.geometry()->boundingBox() );
    delete coordTransform;
    mIface->mapCanvas()->setExtent( rectExtent );
  }
  mIface->mapCanvas()->refresh();
} // void QgsSpatialQueryDialog::zoomFeatureTarget(QgsVectorLayer* lyr, int fid)