void QgsWCSSourceSelect::populateLayerList()
{

  mLayersTreeWidget->clear();


  QgsDataSourceUri uri = mUri;
  QString cache = QgsNetworkAccessManager::cacheLoadControlName( selectedCacheLoadControl() );
  uri.setParam( QStringLiteral( "cache" ), cache );

  mCapabilities.setUri( uri );

  if ( !mCapabilities.lastError().isEmpty() )
  {
    showError( mCapabilities.lastErrorTitle(), mCapabilities.lastErrorFormat(), mCapabilities.lastError() );
    return;
  }

  QVector<QgsWcsCoverageSummary> coverages;
  if ( !mCapabilities.supportedCoverages( coverages ) )
    return;

  QMap<int, QgsTreeWidgetItem *> items;
  QMap<int, int> coverageParents;
  QMap<int, QStringList> coverageParentNames;
  mCapabilities.coverageParents( coverageParents, coverageParentNames );

  mLayersTreeWidget->setSortingEnabled( true );

  int coverageAndStyleCount = -1;

  for ( QVector<QgsWcsCoverageSummary>::iterator coverage = coverages.begin();
        coverage != coverages.end();
        ++coverage )
  {
    QgsDebugMsg( QString( "coverage orderId = %1 identifier = %2" ).arg( coverage->orderId ).arg( coverage->identifier ) );

    QgsTreeWidgetItem *lItem = createItem( coverage->orderId, QStringList() << coverage->identifier << coverage->title << coverage->abstract, items, coverageAndStyleCount, coverageParents, coverageParentNames );

    lItem->setData( 0, Qt::UserRole + 0, coverage->identifier );
    lItem->setData( 0, Qt::UserRole + 1, "" );

    // Make only leaves selectable
    if ( !coverageParents.keys( coverage->orderId ).isEmpty() )
    {
      lItem->setFlags( Qt::ItemIsEnabled );
    }
  }

  mLayersTreeWidget->sortByColumn( 0, Qt::AscendingOrder );

  // If we got some coverages, let the user add them to the map
  if ( mLayersTreeWidget->topLevelItemCount() == 1 )
  {
    mLayersTreeWidget->expandItem( mLayersTreeWidget->topLevelItem( 0 ) );
  }
}