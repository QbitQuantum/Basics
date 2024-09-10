void rulesDialog::readTest( int index, QgsMapLayerRegistry* layerRegistry )
{
  QString testName;
  QString layer1Id;
  QString layer2Id;
  QString tolerance;
  QgsProject* project = QgsProject::instance();
  QString postfix = QString( "%1" ).arg( index );

  testName = project->readEntry( "Topol", "/testname_" + postfix, "" );
  tolerance = project->readEntry( "Topol", "/tolerance_" + postfix, "" );
  layer1Id = project->readEntry( "Topol", "/layer1_" + postfix, "" );
  layer2Id = project->readEntry( "Topol", "/layer2_" + postfix, "" );

  QgsVectorLayer* l1;
  if ( !( QgsVectorLayer* )layerRegistry->mapLayers().contains( layer1Id ) )
    return;

  l1 = ( QgsVectorLayer* )layerRegistry->mapLayers()[layer1Id];
  if ( !l1 )
    return;

  QString layer1Name = l1->name();
  QString layer2Name;
  QgsVectorLayer* l2;

  if ( mTestConfMap[testName].useSecondLayer )
  {
    if ( !( QgsVectorLayer* )layerRegistry->mapLayers().contains( layer2Id ) )
      return;
    else
    {
      l2 = ( QgsVectorLayer* )layerRegistry->mapLayers()[layer2Id];
      layer2Name = l2->name();
    }
  }
  else
    layer2Name = "No layer";

  int row = index;
  mRulesTable->insertRow( row );

  QTableWidgetItem* newItem;
  newItem = new QTableWidgetItem( testName );
  newItem->setFlags( newItem->flags() & ~Qt::ItemIsEditable );
  mRulesTable->setItem( row, 0, newItem );

  newItem = new QTableWidgetItem( layer1Name );
  newItem->setFlags( newItem->flags() & ~Qt::ItemIsEditable );
  mRulesTable->setItem( row, 1, newItem );

  newItem = new QTableWidgetItem( layer2Name );
  newItem->setFlags( newItem->flags() & ~Qt::ItemIsEditable );
  mRulesTable->setItem( row, 2, newItem );

  if ( mTestConfMap[testName].useTolerance )
    newItem = new QTableWidgetItem( tolerance );
  else
    newItem = new QTableWidgetItem( tr( "No tolerance" ) );

  newItem->setFlags( newItem->flags() & ~Qt::ItemIsEditable );
  mRulesTable->setItem( row, 3, newItem );

  // add layer ids to hidden columns
  newItem = new QTableWidgetItem( layer1Id );
  mRulesTable->setItem( row, 4, newItem );
  newItem = new QTableWidgetItem( layer2Id );
  mRulesTable->setItem( row, 5, newItem );
}