void QgsSingleBandPseudoColorRendererWidget::on_mClassifyButton_clicked()
{
  int bandComboIndex = mBandComboBox->currentIndex();
  if ( bandComboIndex == -1 || !mRasterLayer )
  {
    return;
  }

  //int bandNr = mBandComboBox->itemData( bandComboIndex ).toInt();
  //QgsRasterBandStats myRasterBandStats = mRasterLayer->dataProvider()->bandStatistics( bandNr );
  int numberOfEntries;

  QgsColorRampShader::ColorRamp_TYPE interpolation = static_cast< QgsColorRampShader::ColorRamp_TYPE >( mColorInterpolationComboBox->itemData( mColorInterpolationComboBox->currentIndex() ).toInt() );
  bool discrete = interpolation == QgsColorRampShader::DISCRETE;

  QList<double> entryValues;
  QVector<QColor> entryColors;

  double min = lineEditValue( mMinLineEdit );
  double max = lineEditValue( mMaxLineEdit );

  QScopedPointer< QgsVectorColorRampV2 > colorRamp( mColorRampComboBox->currentColorRamp() );

  if ( mClassificationModeComboBox->itemData( mClassificationModeComboBox->currentIndex() ).toInt() == Continuous )
  {
    if ( colorRamp.data() )
    {
      numberOfEntries = colorRamp->count();
      entryValues.reserve( numberOfEntries );
      if ( discrete )
      {
        double intervalDiff = max - min;

        // remove last class when ColorRamp is gradient and discrete, as they are implemented with an extra stop
        QgsVectorGradientColorRampV2* colorGradientRamp = dynamic_cast<QgsVectorGradientColorRampV2*>( colorRamp.data() );
        if ( colorGradientRamp != NULL && colorGradientRamp->isDiscrete() )
        {
          numberOfEntries--;
        }
        else
        {
          // if color ramp is continuous scale values to get equally distributed classes.
          // Doesn't work perfectly when stops are non equally distributed.
          intervalDiff *= ( numberOfEntries - 1 ) / ( double )numberOfEntries;
        }

        // skip first value (always 0.0)
        for ( int i = 1; i < numberOfEntries; ++i )
        {
          double value = colorRamp->value( i );
          entryValues.push_back( min + value * intervalDiff );
        }
        entryValues.push_back( std::numeric_limits<double>::infinity() );
      }
      else
      {
        for ( int i = 0; i < numberOfEntries; ++i )
        {
          double value = colorRamp->value( i );
          entryValues.push_back( min + value * ( max - min ) );
        }
      }
      // for continuous mode take original color map colors
      for ( int i = 0; i < numberOfEntries; ++i )
      {
        entryColors.push_back( colorRamp->color( colorRamp->value( i ) ) );
      }
    }
  }
  else // for other classification modes interpolate colors linearly
  {
    numberOfEntries = mNumberOfEntriesSpinBox->value();
    if ( numberOfEntries < 2 )
      return; // < 2 classes is not useful, shouldn't happen, but if it happens save it from crashing

    if ( mClassificationModeComboBox->itemData( mClassificationModeComboBox->currentIndex() ).toInt() == Quantile )
    { // Quantile
      int bandNr = mBandComboBox->itemData( bandComboIndex ).toInt();
      //QgsRasterHistogram rasterHistogram = mRasterLayer->dataProvider()->histogram( bandNr );

      double cut1 = std::numeric_limits<double>::quiet_NaN();
      double cut2 = std::numeric_limits<double>::quiet_NaN();

      QgsRectangle extent = mMinMaxWidget->extent();
      int sampleSize = mMinMaxWidget->sampleSize();

      // set min and max from histogram, used later to calculate number of decimals to display
      mRasterLayer->dataProvider()->cumulativeCut( bandNr, 0.0, 1.0, min, max, extent, sampleSize );

      entryValues.reserve( numberOfEntries );
      if ( discrete )
      {
        double intervalDiff = 1.0 / ( numberOfEntries );
        for ( int i = 1; i < numberOfEntries; ++i )
        {
          mRasterLayer->dataProvider()->cumulativeCut( bandNr, 0.0, i * intervalDiff, cut1, cut2, extent, sampleSize );
          entryValues.push_back( cut2 );
        }
        entryValues.push_back( std::numeric_limits<double>::infinity() );
      }
      else
      {
        double intervalDiff = 1.0 / ( numberOfEntries - 1 );
        for ( int i = 0; i < numberOfEntries; ++i )
        {
          mRasterLayer->dataProvider()->cumulativeCut( bandNr, 0.0, i * intervalDiff, cut1, cut2, extent, sampleSize );
          entryValues.push_back( cut2 );
        }
      }
    }
    else // EqualInterval
    {
      entryValues.reserve( numberOfEntries );
      if ( discrete )
      {
        // in discrete mode the lowest value is not an entry and the highest
        // value is inf, there are ( numberOfEntries ) of which the first
        // and last are not used.
        double intervalDiff = ( max - min ) / ( numberOfEntries );

        for ( int i = 1; i < numberOfEntries; ++i )
        {
          entryValues.push_back( min + i * intervalDiff );
        }
        entryValues.push_back( std::numeric_limits<double>::infinity() );
      }
      else
      {
        //because the highest value is also an entry, there are (numberOfEntries - 1) intervals
        double intervalDiff = ( max - min ) / ( numberOfEntries - 1 );

        for ( int i = 0; i < numberOfEntries; ++i )
        {
          entryValues.push_back( min + i * intervalDiff );
        }
      }
    }

    if ( !colorRamp.data() )
    {
      //hard code color range from blue -> red (previous default)
      int colorDiff = 0;
      if ( numberOfEntries != 0 )
      {
        colorDiff = ( int )( 255 / numberOfEntries );
      }

      entryColors.reserve( numberOfEntries );
      for ( int i = 0; i < numberOfEntries; ++i )
      {
        QColor currentColor;
        int idx = mInvertCheckBox->isChecked() ? numberOfEntries - i - 1 : i;
        currentColor.setRgb( colorDiff*idx, 0, 255 - colorDiff * idx );
        entryColors.push_back( currentColor );
      }
    }
    else
    {
      entryColors.reserve( numberOfEntries );
      for ( int i = 0; i < numberOfEntries; ++i )
      {
        int idx = mInvertCheckBox->isChecked() ? numberOfEntries - i - 1 : i;
        entryColors.push_back( colorRamp->color((( double ) idx ) / ( numberOfEntries - 1 ) ) );
      }
    }
  }

  mColormapTreeWidget->clear();

  QList<double>::const_iterator value_it = entryValues.begin();
  QVector<QColor>::const_iterator color_it = entryColors.begin();

  // calculate a reasonable number of decimals to display
  double maxabs = log10( qMax( qAbs( max ), qAbs( min ) ) );
  int nDecimals = qRound( qMax( 3.0 + maxabs - log10( max - min ), maxabs <= 15.0 ? maxabs + 0.49 : 0.0 ) );

  for ( ; value_it != entryValues.end(); ++value_it, ++color_it )
  {
    QgsTreeWidgetItem* newItem = new QgsTreeWidgetItem( mColormapTreeWidget );
    newItem->setText( ValueColumn, QString::number( *value_it, 'g', nDecimals ) );
    newItem->setBackground( ColorColumn, QBrush( *color_it ) );
    newItem->setText( LabelColumn, QString() );
    newItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable );
    connect( newItem, SIGNAL( itemEdited( QTreeWidgetItem*, int ) ),
             this, SLOT( mColormapTreeWidget_itemEdited( QTreeWidgetItem*, int ) ) );
  }
  autoLabel();
  emit widgetChanged();
}