QgsLabelFeature* QgsVectorLayerDiagramProvider::registerDiagram( QgsFeature& feat, QgsRenderContext &context, QgsGeometry* obstacleGeometry )
{
  const QgsMapSettings& mapSettings = mEngine->mapSettings();

  const QgsDiagramRenderer* dr = mSettings.getRenderer();
  if ( dr )
  {
    QList<QgsDiagramSettings> settingList = dr->diagramSettings();
    if ( !settingList.isEmpty() && settingList.at( 0 ).scaleBasedVisibility )
    {
      double minScale = settingList.at( 0 ).minScaleDenominator;
      if ( minScale > 0 && context.rendererScale() < minScale )
      {
        return nullptr;
      }

      double maxScale = settingList.at( 0 ).maxScaleDenominator;
      if ( maxScale > 0 && context.rendererScale() > maxScale )
      {
        return nullptr;
      }
    }
  }

  //convert geom to geos
  QgsGeometry geom = feat.geometry();
  QgsGeometry extentGeom = QgsGeometry::fromRect( mapSettings.visibleExtent() );
  if ( !qgsDoubleNear( mapSettings.rotation(), 0.0 ) )
  {
    //PAL features are prerotated, so extent also needs to be unrotated
    extentGeom.rotate( -mapSettings.rotation(), mapSettings.visibleExtent().center() );
  }

  const GEOSGeometry* geos_geom = nullptr;
  QScopedPointer<QgsGeometry> scopedPreparedGeom;
  if ( QgsPalLabeling::geometryRequiresPreparation( geom, context, mSettings.coordinateTransform(), &extentGeom ) )
  {
    scopedPreparedGeom.reset( new QgsGeometry( QgsPalLabeling::prepareGeometry( geom, context, mSettings.coordinateTransform(), &extentGeom ) ) );
    QgsGeometry* preparedGeom = scopedPreparedGeom.data();
    if ( preparedGeom->isEmpty() )
      return nullptr;
    geos_geom = preparedGeom->asGeos();
  }
  else
  {
    geos_geom = geom.asGeos();
  }

  if ( !geos_geom )
    return nullptr; // invalid geometry

  GEOSGeometry* geomCopy = GEOSGeom_clone_r( QgsGeometry::getGEOSHandler(), geos_geom );

  const GEOSGeometry* geosObstacleGeom = nullptr;
  QScopedPointer<QgsGeometry> scopedObstacleGeom;
  if ( mSettings.isObstacle() && obstacleGeometry && QgsPalLabeling::geometryRequiresPreparation( *obstacleGeometry, context, mSettings.coordinateTransform(), &extentGeom ) )
  {
    QgsGeometry preparedObstacleGeom = QgsPalLabeling::prepareGeometry( *obstacleGeometry, context, mSettings.coordinateTransform(), &extentGeom );
    geosObstacleGeom = preparedObstacleGeom.asGeos();
  }
  else if ( mSettings.isObstacle() && obstacleGeometry )
  {
    geosObstacleGeom = obstacleGeometry->asGeos();
  }
  GEOSGeometry* geosObstacleGeomClone = nullptr;
  if ( geosObstacleGeom )
  {
    geosObstacleGeomClone = GEOSGeom_clone_r( QgsGeometry::getGEOSHandler(), geosObstacleGeom );
  }


  double diagramWidth = 0;
  double diagramHeight = 0;
  if ( dr )
  {
    QSizeF diagSize = dr->sizeMapUnits( feat, context );
    if ( diagSize.isValid() )
    {
      diagramWidth = diagSize.width();
      diagramHeight = diagSize.height();
    }
  }

  //  feature to the layer
  bool alwaysShow = mSettings.showAllDiagrams();
  int ddColX = mSettings.xPosColumn;
  int ddColY = mSettings.yPosColumn;
  double ddPosX = 0.0;
  double ddPosY = 0.0;
  bool ddPos = ( ddColX >= 0 && ddColY >= 0 );
  if ( ddPos && ! feat.attribute( ddColX ).isNull() && ! feat.attribute( ddColY ).isNull() )
  {
    bool posXOk, posYOk;
    ddPosX = feat.attribute( ddColX ).toDouble( &posXOk );
    ddPosY = feat.attribute( ddColY ).toDouble( &posYOk );
    if ( !posXOk || !posYOk )
    {
      ddPos = false;
    }
    else
    {
      QgsCoordinateTransform ct = mSettings.coordinateTransform();
      if ( ct.isValid() && !ct.isShortCircuited() )
      {
        double z = 0;
        ct.transformInPlace( ddPosX, ddPosY, z );
      }
      //data defined diagram position is always centered
      ddPosX -= diagramWidth / 2.0;
      ddPosY -= diagramHeight / 2.0;
    }
  }
  else
    ddPos = false;

  int ddColShow = mSettings.showColumn;
  if ( ddColShow >= 0 && ! feat.attribute( ddColShow ).isNull() )
  {
    bool showOk;
    bool ddShow = feat.attribute( ddColShow ).toDouble( &showOk );

    if ( showOk && ! ddShow )
      return nullptr;
  }

  QgsDiagramLabelFeature* lf = new QgsDiagramLabelFeature( feat.id(), geomCopy, QSizeF( diagramWidth, diagramHeight ) );
  lf->setHasFixedPosition( ddPos );
  lf->setFixedPosition( QgsPoint( ddPosX, ddPosY ) );
  lf->setHasFixedAngle( true );
  lf->setFixedAngle( 0 );
  lf->setAlwaysShow( alwaysShow );
  lf->setIsObstacle( mSettings.isObstacle() );
  lf->setZIndex( mSettings.getZIndex() );
  if ( geosObstacleGeomClone )
  {
    lf->setObstacleGeometry( geosObstacleGeomClone );
  }

  if ( dr )
  {
    //append the diagram attributes to lbl
    lf->setAttributes( feat.attributes() );
  }

  QgsPoint ptZero = mapSettings.mapToPixel().toMapCoordinates( 0, 0 );
  QgsPoint ptOne = mapSettings.mapToPixel().toMapCoordinates( 1, 0 );
  lf->setDistLabel( ptOne.distance( ptZero ) * mSettings.distance() );
  return lf;
}