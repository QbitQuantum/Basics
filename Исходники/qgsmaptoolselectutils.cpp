QgsFeatureIds QgsMapToolSelectUtils::getMatchingFeatures( QgsMapCanvas *canvas, const QgsGeometry &selectGeometry, bool doContains, bool singleSelect )
{
  QgsFeatureIds newSelectedFeatures;

  if ( selectGeometry.type() != QgsWkbTypes::PolygonGeometry )
    return newSelectedFeatures;

  QgsVectorLayer *vlayer = QgsMapToolSelectUtils::getCurrentVectorLayer( canvas );
  if ( !vlayer )
    return newSelectedFeatures;

  // toLayerCoordinates will throw an exception for any 'invalid' points in
  // the rubber band.
  // For example, if you project a world map onto a globe using EPSG 2163
  // and then click somewhere off the globe, an exception will be thrown.
  QgsGeometry selectGeomTrans = selectGeometry;

  try
  {
    QgsCoordinateTransform ct( canvas->mapSettings().destinationCrs(), vlayer->crs(), QgsProject::instance() );

    if ( !ct.isShortCircuited() && selectGeomTrans.type() == QgsWkbTypes::PolygonGeometry )
    {
      // convert add more points to the edges of the rectangle
      // improve transformation result
      QgsPolygonXY poly( selectGeomTrans.asPolygon() );
      if ( poly.size() == 1 && poly.at( 0 ).size() == 5 )
      {
        const QgsPolylineXY &ringIn = poly.at( 0 );

        QgsPolygonXY newpoly( 1 );
        newpoly[0].resize( 41 );
        QgsPolylineXY &ringOut = newpoly[0];

        ringOut[ 0 ] = ringIn.at( 0 );

        int i = 1;
        for ( int j = 1; j < 5; j++ )
        {
          QgsVector v( ( ringIn.at( j ) - ringIn.at( j - 1 ) ) / 10.0 );
          for ( int k = 0; k < 9; k++ )
          {
            ringOut[ i ] = ringOut[ i - 1 ] + v;
            i++;
          }
          ringOut[ i++ ] = ringIn.at( j );
        }
        selectGeomTrans = QgsGeometry::fromPolygonXY( newpoly );
      }
    }

    selectGeomTrans.transform( ct );
  }
  catch ( QgsCsException &cse )
  {
    Q_UNUSED( cse );
    // catch exception for 'invalid' point and leave existing selection unchanged
    QgsDebugMsg( QStringLiteral( "Caught CRS exception " ) );
    QgisApp::instance()->messageBar()->pushMessage(
      QObject::tr( "CRS Exception" ),
      QObject::tr( "Selection extends beyond layer's coordinate system" ),
      Qgis::Warning,
      QgisApp::instance()->messageTimeout() );
    return newSelectedFeatures;
  }

  QgsDebugMsgLevel( "Selection layer: " + vlayer->name(), 3 );
  QgsDebugMsgLevel( "Selection polygon: " + selectGeomTrans.asWkt(), 3 );
  QgsDebugMsgLevel( "doContains: " + QString( doContains ? "T" : "F" ), 3 );

  QgsRenderContext context = QgsRenderContext::fromMapSettings( canvas->mapSettings() );
  context.expressionContext() << QgsExpressionContextUtils::layerScope( vlayer );
  std::unique_ptr< QgsFeatureRenderer > r;
  if ( vlayer->renderer() )
  {
    r.reset( vlayer->renderer()->clone() );
    r->startRender( context, vlayer->fields() );
  }

  QgsFeatureRequest request;
  request.setFilterRect( selectGeomTrans.boundingBox() );
  request.setFlags( QgsFeatureRequest::ExactIntersect );
  if ( r )
    request.setSubsetOfAttributes( r->usedAttributes( context ), vlayer->fields() );
  else
    request.setNoAttributes();

  QgsFeatureIterator fit = vlayer->getFeatures( request );

  QgsFeature f;
  QgsFeatureId closestFeatureId = 0;
  bool foundSingleFeature = false;
  double closestFeatureDist = std::numeric_limits<double>::max();
  while ( fit.nextFeature( f ) )
  {
    context.expressionContext().setFeature( f );
    // make sure to only use features that are visible
    if ( r && !r->willRenderFeature( f, context ) )
      continue;

    QgsGeometry g = f.geometry();
    if ( doContains )
    {
      if ( !selectGeomTrans.contains( g ) )
        continue;
    }
    else
    {
      if ( !selectGeomTrans.intersects( g ) )
        continue;
    }
    if ( singleSelect )
    {
      foundSingleFeature = true;
      double distance = g.distance( selectGeomTrans );
      if ( distance <= closestFeatureDist )
      {
        closestFeatureDist = distance;
        closestFeatureId = f.id();
      }
    }
    else
    {
      newSelectedFeatures.insert( f.id() );
    }
  }
  if ( singleSelect && foundSingleFeature )
  {
    newSelectedFeatures.insert( closestFeatureId );
  }

  if ( r )
    r->stopRender( context );

  QgsDebugMsg( "Number of new selected features: " + QString::number( newSelectedFeatures.size() ) );

  return newSelectedFeatures;
}