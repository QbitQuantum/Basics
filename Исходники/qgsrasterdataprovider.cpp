QgsRasterBlock * QgsRasterDataProvider::block( int theBandNo, QgsRectangle  const & theExtent, int theWidth, int theHeight )
{
  QgsDebugMsg( QString( "theBandNo = %1 theWidth = %2 theHeight = %3" ).arg( theBandNo ).arg( theWidth ).arg( theHeight ) );
  QgsDebugMsg( QString( "theExtent = %1" ).arg( theExtent.toString() ) );

  QgsRasterBlock *block = new QgsRasterBlock( dataType( theBandNo ), theWidth, theHeight, noDataValue( theBandNo ) );

  if ( block->isEmpty() )
  {
    QgsDebugMsg( "Couldn't create raster block" );
    return block;
  }

  // Read necessary extent only
  QgsRectangle tmpExtent = extent().intersect( &theExtent );

  if ( tmpExtent.isEmpty() )
  {
    QgsDebugMsg( "Extent outside provider extent" );
    block->setIsNoData();
    return block;
  }

  double xRes = theExtent.width() / theWidth;
  double yRes = theExtent.height() / theHeight;
  double tmpXRes, tmpYRes;
  double providerXRes = 0;
  double providerYRes = 0;
  if ( capabilities() & ExactResolution )
  {
    providerXRes = extent().width() / xSize();
    providerYRes = extent().height() / ySize();
    tmpXRes = qMax( providerXRes, xRes );
    tmpYRes = qMax( providerYRes, yRes );
    if ( doubleNear( tmpXRes, xRes ) ) tmpXRes = xRes;
    if ( doubleNear( tmpYRes, yRes ) ) tmpYRes = yRes;
  }
  else
  {
    tmpXRes = xRes;
    tmpYRes = yRes;
  }

  if ( tmpExtent != theExtent ||
       tmpXRes > xRes || tmpYRes > yRes )
  {
    // Read smaller extent or lower resolution

    // Calculate row/col limits (before tmpExtent is aligned)
    int fromRow = qRound(( theExtent.yMaximum() - tmpExtent.yMaximum() ) / yRes );
    int toRow = qRound(( theExtent.yMaximum() - tmpExtent.yMinimum() ) / yRes ) - 1;
    int fromCol = qRound(( tmpExtent.xMinimum() - theExtent.xMinimum() ) / xRes ) ;
    int toCol = qRound(( tmpExtent.xMaximum() - theExtent.xMinimum() ) / xRes ) - 1;

    QgsDebugMsg( QString( "fromRow = %1 toRow = %2 fromCol = %3 toCol = %4" ).arg( fromRow ).arg( toRow ).arg( fromCol ).arg( toCol ) );

    if ( fromRow < 0 || fromRow >= theHeight || toRow < 0 || toRow >= theHeight ||
         fromCol < 0 || fromCol >= theWidth || toCol < 0 || toCol >= theWidth )
    {
      // Should not happen
      QgsDebugMsg( "Row or column limits out of range" );
      return block;
    }

    // If lower source resolution is used, the extent must beS aligned to original
    // resolution to avoid possible shift due to resampling
    if ( tmpXRes > xRes )
    {
      int col = floor(( tmpExtent.xMinimum() - extent().xMinimum() ) / providerXRes );
      tmpExtent.setXMinimum( extent().xMinimum() + col * providerXRes );
      col = ceil(( tmpExtent.xMaximum() - extent().xMinimum() ) / providerXRes );
      tmpExtent.setXMaximum( extent().xMinimum() + col * providerXRes );
    }
    if ( tmpYRes > yRes )
    {
      int row = floor(( extent().yMaximum() - tmpExtent.yMaximum() ) / providerYRes );
      tmpExtent.setYMaximum( extent().yMaximum() - row * providerYRes );
      row = ceil(( extent().yMaximum() - tmpExtent.yMinimum() ) / providerYRes );
      tmpExtent.setYMinimum( extent().yMaximum() - row * providerYRes );
    }
    int tmpWidth = qRound( tmpExtent.width() / tmpXRes );
    int tmpHeight = qRound( tmpExtent.height() / tmpYRes );
    tmpXRes = tmpExtent.width() / tmpWidth;
    tmpYRes = tmpExtent.height() / tmpHeight;

    QgsDebugMsg( QString( "Reading smaller block tmpWidth = %1 theHeight = %2" ).arg( tmpWidth ).arg( tmpHeight ) );
    QgsDebugMsg( QString( "tmpExtent = %1" ).arg( tmpExtent.toString() ) );

    block->setIsNoData();

    QgsRasterBlock *tmpBlock = new QgsRasterBlock( dataType( theBandNo ), tmpWidth, tmpHeight, noDataValue( theBandNo ) );

    readBlock( theBandNo, tmpExtent, tmpWidth, tmpHeight, tmpBlock->data() );

    int pixelSize = dataTypeSize( theBandNo );

    double xMin = theExtent.xMinimum();
    double yMax = theExtent.yMaximum();
    double tmpXMin = tmpExtent.xMinimum();
    double tmpYMax = tmpExtent.yMaximum();

    for ( int row = fromRow; row <= toRow; row++ )
    {
      double y = yMax - ( row + 0.5 ) * yRes;
      int tmpRow = floor(( tmpYMax - y ) / tmpYRes );

      for ( int col = fromCol; col <= toCol; col++ )
      {
        double x = xMin + ( col + 0.5 ) * xRes;
        int tmpCol = floor(( x - tmpXMin ) / tmpXRes );

        if ( tmpRow < 0 || tmpRow >= tmpHeight || tmpCol < 0 || tmpCol >= tmpWidth )
        {
          QgsDebugMsg( "Source row or column limits out of range" );
          block->setIsNoData(); // so that the problem becomes obvious and fixed
          delete tmpBlock;
          return block;
        }

        size_t tmpIndex = tmpRow * tmpWidth + tmpCol;
        size_t index = row * theWidth + col;

        char *tmpBits = tmpBlock->bits( tmpIndex );
        char *bits = block->bits( index );
        if ( !tmpBits )
        {
          QgsDebugMsg( QString( "Cannot get input block data tmpRow = %1 tmpCol = %2 tmpIndex = %3." ).arg( tmpRow ).arg( tmpCol ).arg( tmpIndex ) );
          continue;
        }
        if ( !bits )
        {
          QgsDebugMsg( "Cannot set output block data." );
          continue;
        }
        memcpy( bits, tmpBits, pixelSize );
      }
    }

    delete tmpBlock;
  }
  else
  {
    readBlock( theBandNo, theExtent, theWidth, theHeight, block->data() );
  }

  // apply user no data values
  // TODO: there are other readBlock methods where no data are not applied
  QList<QgsRasterBlock::Range> myNoDataRangeList = userNoDataValue( theBandNo );
  if ( !myNoDataRangeList.isEmpty() )
  {
    double myNoDataValue = noDataValue( theBandNo );
    size_t size = theWidth * theHeight;
    for ( size_t i = 0; i < size; i++ )
    {
      double value = block->value( i );

      if ( QgsRasterBlock::valueInRange( value, myNoDataRangeList ) )
      {
        block->setValue( i, myNoDataValue );
      }
    }
  }

  return block;
}