void QgsInterpolationDialog::on_buttonBox_accepted()
{
  if ( !mInterpolatorDialog )
  {
    return;
  }

  QgsRectangle outputBBox = currentBoundingBox();
  if ( outputBBox.isEmpty() )
  {
    return;
  }

  //warn the user if there isn't any input layer
  if ( mLayersTreeWidget->topLevelItemCount() < 1 )
  {
    QMessageBox::information( nullptr, tr( "No input data for interpolation" ), tr( "Please add one or more input layers" ) );
    return;
  }

  //read file name
  QString fileName = mOutputFileLineEdit->text();
  QFileInfo theFileInfo( fileName );
  if ( fileName.isEmpty() || !theFileInfo.dir().exists() )
  {
    QMessageBox::information( nullptr, tr( "Output file name invalid" ), tr( "Please enter a valid output file name" ) );
    return;
  }

  //add .asc suffix if the user did not provider it already
  QString suffix = theFileInfo.suffix();
  if ( suffix.isEmpty() )
  {
    fileName.append( ".asc" );
  }

  int nLayers = mLayersTreeWidget->topLevelItemCount();
  QList< QgsInterpolator::LayerData > inputLayerList;

  for ( int i = 0; i < nLayers; ++i )
  {
    QString layerName = mLayersTreeWidget->topLevelItem( i )->text( 0 );
    QgsVectorLayer* theVectorLayer = vectorLayerFromName( layerName );
    if ( !theVectorLayer )
    {
      continue;
    }

    QgsVectorDataProvider* theProvider = theVectorLayer->dataProvider();
    if ( !theProvider )
    {
      continue;
    }

    QgsInterpolator::LayerData currentLayerData;
    currentLayerData.vectorLayer = theVectorLayer;

    QString interpolationAttString = mLayersTreeWidget->topLevelItem( i )->text( 1 );
    if ( interpolationAttString == "Z_COORD" )
    {
      currentLayerData.zCoordInterpolation = true;
      currentLayerData.interpolationAttribute = -1;
    }
    else
    {
      currentLayerData.zCoordInterpolation = false;
      int attributeIndex = theProvider->fieldNameIndex( interpolationAttString );
      currentLayerData.interpolationAttribute = attributeIndex;
    }

    //type (point/structure line/ breakline)
    QComboBox* itemCombo = qobject_cast<QComboBox *>( mLayersTreeWidget->itemWidget( mLayersTreeWidget->topLevelItem( i ), 2 ) );
    if ( itemCombo )
    {
      QString typeString = itemCombo->currentText();
      if ( typeString == tr( "Break lines" ) )
      {
        currentLayerData.mInputType = QgsInterpolator::BREAK_LINES;
      }
      else if ( typeString == tr( "Structure lines" ) )
      {
        currentLayerData.mInputType = QgsInterpolator::STRUCTURE_LINES;
      }
      else //Points
      {
        currentLayerData.mInputType = QgsInterpolator::POINTS;
      }
    }
    else
    {
      currentLayerData.mInputType = QgsInterpolator::POINTS;
    }
    inputLayerList.push_back( currentLayerData );
  }

  mInterpolatorDialog->setInputData( inputLayerList );
  QgsInterpolator* theInterpolator = mInterpolatorDialog->createInterpolator();

  if ( !theInterpolator )
  {
    return;
  }

  //create grid file writer
  QgsGridFileWriter theWriter( theInterpolator, fileName, outputBBox, mNumberOfColumnsSpinBox->value(),
                               mNumberOfRowsSpinBox->value(), mCellsizeXSpinBox->value(), mCellSizeYSpinBox->value() );
  if ( theWriter.writeFile( true ) == 0 )
  {
    if ( mAddResultToProjectCheckBox->isChecked() )
    {
      mIface->addRasterLayer( fileName, QFileInfo( fileName ).baseName() );
    }
    accept();
  }

  delete theInterpolator;
}