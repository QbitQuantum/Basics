void QgsAttributeTypeLoadDialog::createPreview( int fieldIndex, bool full )
{
  previewTableWidget->clearContents();

  for ( int i = previewTableWidget->rowCount() - 1; i > 0; i-- )
  {
    previewTableWidget->removeRow( i );
  }
  if ( layerComboBox->currentIndex() < 0 || fieldIndex < 0 )
  {
    //when nothing is selected there is no reason for preview
    return;
  }
  int idx = keyComboBox->itemData( keyComboBox->currentIndex() ).toInt();
  int idx2 = valueComboBox->itemData( valueComboBox->currentIndex() ).toInt();
  QgsMapLayer* dataLayer = QgsMapLayerRegistry::instance()->mapLayer( layerComboBox->currentText() );
  QgsVectorLayer* vLayer = qobject_cast<QgsVectorLayer *>( dataLayer );
  if ( vLayer == NULL )
  {
    return;
  }

  QgsVectorDataProvider* dataProvider = vLayer->dataProvider();
  dataProvider->enableGeometrylessFeatures( true );

  QgsAttributeList attributeList = QgsAttributeList();
  attributeList.append( idx );
  attributeList.append( idx2 );
  vLayer->select( attributeList, QgsRectangle(), false );

  QgsFeature f;
  QMap<QString, QVariant> valueMap;
  while ( vLayer->nextFeature( f ) )
  {
    QVariant val1 = f.attributeMap()[idx];
    QVariant val2 = f.attributeMap()[idx2];
    if ( val1.isValid() && !val1.isNull() && !val1.toString().isEmpty()
         && val2.isValid() && !val2.isNull() && !val2.toString().isEmpty() )
    {
      valueMap.insert( val1.toString(), val2.toString() );
    }
    if ( !full && valueMap.size() > 8 )
      break; //just first entries all on button
  }
  int row = 0;
  for ( QMap<QString, QVariant>::iterator mit = valueMap.begin(); mit != valueMap.end(); mit++, row++ )
  {
    previewTableWidget->insertRow( row );
    previewTableWidget->setItem( row, 0, new QTableWidgetItem( mit.value().toString() ) );
    previewTableWidget->setItem( row, 1, new QTableWidgetItem( mit.key() ) );
  }

  dataProvider->enableGeometrylessFeatures( false );
}