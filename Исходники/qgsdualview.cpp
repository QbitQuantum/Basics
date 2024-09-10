void QgsDualView::setFilterMode( QgsAttributeTableFilterModel::FilterMode filterMode )
{
  // cleanup any existing connections
  switch ( mFilterModel->filterMode() )
  {
    case QgsAttributeTableFilterModel::ShowVisible:
      disconnect( mFilterModel->mapCanvas(), &QgsMapCanvas::extentsChanged, this, &QgsDualView::extentChanged );
      break;

    case QgsAttributeTableFilterModel::ShowAll:
    case QgsAttributeTableFilterModel::ShowEdited:
    case QgsAttributeTableFilterModel::ShowFilteredList:
      break;

    case QgsAttributeTableFilterModel::ShowSelected:
      disconnect( masterModel()->layer(), &QgsVectorLayer::selectionChanged, this, &QgsDualView::updateSelectedFeatures );
      break;
  }

  QgsFeatureRequest r = mMasterModel->request();
  bool needsGeometry = filterMode == QgsAttributeTableFilterModel::ShowVisible;

  bool requiresTableReload = ( r.filterType() != QgsFeatureRequest::FilterNone || !r.filterRect().isNull() ) // previous request was subset
                             || ( needsGeometry && r.flags() & QgsFeatureRequest::NoGeometry ) // no geometry for last request
                             || ( mMasterModel->rowCount() == 0 ); // no features

  if ( !needsGeometry )
    r.setFlags( r.flags() | QgsFeatureRequest::NoGeometry );
  else
    r.setFlags( r.flags() & ~( QgsFeatureRequest::NoGeometry ) );
  r.setFilterFids( QgsFeatureIds() );
  r.setFilterRect( QgsRectangle() );
  r.disableFilter();

  // setup new connections and filter request parameters
  switch ( filterMode )
  {
    case QgsAttributeTableFilterModel::ShowVisible:
      connect( mFilterModel->mapCanvas(), &QgsMapCanvas::extentsChanged, this, &QgsDualView::extentChanged );
      if ( mFilterModel->mapCanvas() )
      {
        QgsRectangle rect = mFilterModel->mapCanvas()->mapSettings().mapToLayerCoordinates( mLayer, mFilterModel->mapCanvas()->extent() );
        r.setFilterRect( rect );
      }
      break;

    case QgsAttributeTableFilterModel::ShowAll:
    case QgsAttributeTableFilterModel::ShowEdited:
    case QgsAttributeTableFilterModel::ShowFilteredList:
      break;

    case QgsAttributeTableFilterModel::ShowSelected:
      connect( masterModel()->layer(), &QgsVectorLayer::selectionChanged, this, &QgsDualView::updateSelectedFeatures );
      r.setFilterFids( masterModel()->layer()->selectedFeatureIds() );
      break;
  }

  if ( requiresTableReload )
  {
    mMasterModel->setRequest( r );
    whileBlocking( mLayerCache )->setCacheGeometry( needsGeometry );
    mMasterModel->loadLayer();
  }

  //update filter model
  mFilterModel->setFilterMode( filterMode );
  emit filterChanged();
}