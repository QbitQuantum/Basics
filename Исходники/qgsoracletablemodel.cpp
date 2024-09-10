void QgsOracleTableModel::addTableEntry( const QgsOracleLayerProperty &layerProperty )
{
  QgsDebugMsg( layerProperty.toString() );

  if ( layerProperty.isView && layerProperty.pkCols.isEmpty() )
  {
    QgsDebugMsg( "View without pk skipped." );
    return;
  }

  // is there already a root item with the given scheme Name?
  QStandardItem *ownerItem = 0;

  for ( int i = 0; i < layerProperty.size(); i++ )
  {
    QGis::WkbType wkbType = layerProperty.types[ i ];
    int srid = layerProperty.srids[ i ];


    QString tip;
    if ( wkbType == QGis::WKBUnknown )
    {
      tip = tr( "Specify a geometry type" );
    }
    else if ( wkbType != QGis::WKBNoGeometry && srid == 0 )
    {
      tip = tr( "Enter a SRID" );
    }

    if ( tip.isEmpty() && layerProperty.isView )
    {
      tip = tr( "Select a primary key" );
    }

    QStandardItem *ownerNameItem = new QStandardItem( layerProperty.ownerName );
    QStandardItem *typeItem = new QStandardItem( iconForWkbType( wkbType ), wkbType == QGis::WKBUnknown ? tr( "Select..." ) : QgsOracleConn::displayStringForWkbType( wkbType ) );
    typeItem->setData( wkbType == QGis::WKBUnknown, Qt::UserRole + 1 );
    typeItem->setData( wkbType, Qt::UserRole + 2 );
    if ( wkbType == QGis::WKBUnknown )
      typeItem->setFlags( typeItem->flags() | Qt::ItemIsEditable );

    QStandardItem *tableItem = new QStandardItem( layerProperty.tableName );
    QStandardItem *geomItem  = new QStandardItem( layerProperty.geometryColName );
    QStandardItem *sridItem  = new QStandardItem( wkbType != QGis::WKBNoGeometry ? QString::number( srid ) : "" );
    sridItem->setEditable( wkbType != QGis::WKBNoGeometry && srid == 0 );
    if ( sridItem->isEditable() )
    {
      sridItem->setText( tr( "Enter..." ) );
      sridItem->setFlags( sridItem->flags() | Qt::ItemIsEditable );
    }

    QStandardItem *pkItem = new QStandardItem( "" );
    if ( layerProperty.isView )
    {
      pkItem->setText( tr( "Select..." ) );
      pkItem->setFlags( pkItem->flags() | Qt::ItemIsEditable );
    }
    else
      pkItem->setFlags( pkItem->flags() & ~Qt::ItemIsEditable );

    pkItem->setData( layerProperty.isView, Qt::UserRole + 1 );
    pkItem->setData( false, Qt::UserRole + 2 ); // not selected

    QStandardItem *selItem = new QStandardItem( "" );
    selItem->setFlags( selItem->flags() | Qt::ItemIsUserCheckable );
    selItem->setCheckState( Qt::Checked );
    selItem->setToolTip( tr( "Disable 'Fast Access to Features at ID' capability to force keeping the attribute table in memory (e.g. in case of expensive views)." ) );

    QStandardItem* sqlItem = new QStandardItem( layerProperty.sql );

    QList<QStandardItem*> childItemList;
    childItemList << ownerNameItem;
    childItemList << tableItem;
    childItemList << typeItem;
    childItemList << geomItem;
    childItemList << sridItem;
    childItemList << pkItem;
    childItemList << selItem;
    childItemList << sqlItem;

    foreach ( QStandardItem *item, childItemList )
    {
      if ( tip.isEmpty() )
      {
        item->setFlags( item->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        item->setToolTip( "" );
      }
      else
      {
        item->setFlags( item->flags() & ~Qt::ItemIsSelectable );

        if ( item == ownerNameItem || item == tableItem || item == geomItem )
        {
          item->setFlags( item->flags() & ~Qt::ItemIsEnabled );
          item->setToolTip( tip );
        }
      }
    }

    if ( !ownerItem )
    {
      QList<QStandardItem*> ownerItems = findItems( layerProperty.ownerName, Qt::MatchExactly, dbtmOwner );

      // there is already an item for this schema
      if ( ownerItems.size() > 0 )
      {
        ownerItem = ownerItems.at( dbtmOwner );
      }
      else
      {
        // create a new toplevel item for this schema
        ownerItem = new QStandardItem( layerProperty.ownerName );
        ownerItem->setFlags( Qt::ItemIsEnabled );
        invisibleRootItem()->setChild( invisibleRootItem()->rowCount(), ownerItem );
      }
    }

    ownerItem->appendRow( childItemList );

    ++mTableCount;
  }
}