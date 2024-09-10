osg::Image* QgsOsgEarthTileSource::createImage( const TileKey& key, ProgressCallback* progress )
{
  QString kname = key.str().c_str();
  kname.replace( '/', '_' );

  Q_UNUSED( progress );

  //Get the extents of the tile
  int tileSize = getPixelsPerTile();
  if ( tileSize <= 0 )
  {
    QgsDebugMsg( "Tile size too small." );
    return ImageUtils::createEmptyImage();
  }

  QgsRectangle viewExtent = mQGisIface->mapCanvas()->fullExtent();
  if ( mCoordTransform )
  {
    QgsDebugMsg( QString( "vext0:%1" ).arg( viewExtent.toString( 5 ) ) );
    viewExtent = mCoordTransform->transformBoundingBox( viewExtent );
  }

  QgsDebugMsg( QString( "vext1:%1" ).arg( viewExtent.toString( 5 ) ) );

  double xmin, ymin, xmax, ymax;
  key.getExtent().getBounds( xmin, ymin, xmax, ymax );
  QgsRectangle tileExtent( xmin, ymin, xmax, ymax );

  QgsDebugMsg( QString( "text0:%1" ).arg( tileExtent.toString( 5 ) ) );
  if ( !viewExtent.intersects( tileExtent ) )
  {
    QgsDebugMsg( QString( "earth tile key:%1 ext:%2: NO INTERSECT" ).arg( kname ).arg( tileExtent.toString( 5 ) ) );
    return ImageUtils::createEmptyImage();
  }

#ifdef USE_RENDERER
  QImage *qImage = createQImage( tileSize, tileSize );
  if ( !qImage )
  {
    QgsDebugMsg( QString( "earth tile key:%1 ext:%2: EMPTY IMAGE" ).arg( kname ).arg( tileExtent.toString( 5 ) ) );
    return ImageUtils::createEmptyImage();
  }

  mMapRenderer->setLayerSet( mQGisIface->mapCanvas()->mapRenderer()->layerSet() );
  mMapRenderer->setOutputSize( QSize( tileSize, tileSize ), qImage->logicalDpiX() );
  mMapRenderer->setExtent( tileExtent );

  QPainter thePainter( qImage );
  mMapRenderer->render( &thePainter );
#else
  mMapSettings.setLayers( mQGisIface->mapCanvas()->mapSettings().layers() );
  mMapSettings.setOutputSize( QSize( tileSize, tileSize ) );
  mMapSettings.setOutputDpi( QgsApplication::desktop()->logicalDpiX() );
  mMapSettings.setExtent( tileExtent );
  mMapSettings.setBackgroundColor( QColor( 0, 0, 0, 0 ) );

  QgsMapRendererSequentialJob job( mMapSettings );
  job.start();
  job.waitForFinished();

  QImage *qImage = new QImage( job.renderedImage() );
  if ( !qImage )
  {
    QgsDebugMsg( QString( "earth tile key:%1 ext:%2: EMPTY IMAGE" ).arg( kname ).arg( tileExtent.toString( 5 ) ) );
    return ImageUtils::createEmptyImage();
  }

  Q_ASSERT( qImage->logicalDpiX() == QgsApplication::desktop()->logicalDpiX() );
  Q_ASSERT( qImage->format() == QImage::Format_ARGB32_Premultiplied );
#endif

  QgsDebugMsg( QString( "earth tile key:%1 ext:%2" ).arg( kname ).arg( tileExtent.toString( 5 ) ) );
#if 0
  qImage->save( QString( "/tmp/tile-%1.png" ).arg( kname ) );
#endif

  osg::ref_ptr<osg::Image> image = new osg::Image;

  //The pixel format is always RGBA to support transparency
  image->setImage( tileSize, tileSize, 1, 4, // width, height, depth, pixelFormat?
                   GL_BGRA, GL_UNSIGNED_BYTE, //Why not GL_RGBA - Qt bug?
                   qImage->bits(),
                   osg::Image::NO_DELETE, 1 );

  image->flipVertical();

  //Create a transparent image if we don't have an image
  if ( !image.valid() )
  {
    QgsDebugMsg( "image is invalid" );
    return ImageUtils::createEmptyImage();
  }

  QgsDebugMsg( "returning image" );
  return image.release();
}