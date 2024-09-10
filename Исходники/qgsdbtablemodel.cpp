void QgsDbTableModel::addTableEntry( QString type, QString schemaName, QString tableName, QString geometryColName, QString sql )
{
  //is there already a root item with the given scheme Name?
  QStandardItem* schemaItem;
  QList<QStandardItem*> schemaItems = findItems( schemaName, Qt::MatchExactly, 0 );

  //there is already an item for this schema
  if ( schemaItems.size() > 0 )
  {
    schemaItem = schemaItems.at( 0 );
  }
  else //create a new toplevel item for this schema
  {
    schemaItem = new QStandardItem( schemaName );
    schemaItem->setFlags( Qt::ItemIsEnabled );
    invisibleRootItem()->setChild( invisibleRootItem()->rowCount(), schemaItem );
  }

  //path to icon for specified type
  QString typeName;

  QGis::WkbType wkbType = qgisTypeFromDbType( type );
  QIcon iconFile = iconForType( wkbType );

  QList<QStandardItem*> childItemList;
  QStandardItem* schemaNameItem = new QStandardItem( schemaName );
  schemaNameItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );
  QStandardItem* typeItem = new QStandardItem( QIcon( iconFile ), type );
  typeItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );
  QStandardItem* tableItem = new QStandardItem( tableName );
  tableItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );
  QStandardItem* geomItem = new QStandardItem( geometryColName );
  geomItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );
  QStandardItem* sqlItem = new QStandardItem( sql );
  sqlItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );


  childItemList.push_back( schemaNameItem );
  childItemList.push_back( tableItem );
  childItemList.push_back( typeItem );
  childItemList.push_back( geomItem );
  childItemList.push_back( sqlItem );

  schemaItem->appendRow( childItemList );
  ++mTableCount;
}