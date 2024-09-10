void QgsLocationBasedAlgorithm::process( QgsFeatureSource *targetSource,
    QgsFeatureSource *intersectSource,
    const QList< int > &selectedPredicates,
    const std::function < void( const QgsFeature & ) > &handleFeatureFunction,
    bool onlyRequireTargetIds,
    QgsFeedback *feedback )
{
  // build a list of 'reversed' predicates, because in this function
  // we actually test the reverse of what the user wants (allowing us
  // to prepare geometries and optimise the algorithm)
  QList< Predicate > predicates;
  for ( int i : selectedPredicates )
  {
    predicates << reversePredicate( static_cast< Predicate >( i ) );
  }

  QgsFeatureIds disjointSet;
  if ( predicates.contains( Disjoint ) )
    disjointSet = targetSource->allFeatureIds();

  QgsFeatureIds foundSet;
  QgsFeatureRequest request = QgsFeatureRequest().setSubsetOfAttributes( QgsAttributeList() ).setDestinationCrs( targetSource->sourceCrs() );
  QgsFeatureIterator fIt = intersectSource->getFeatures( request );
  double step = intersectSource->featureCount() > 0 ? 100.0 / intersectSource->featureCount() : 1;
  int current = 0;
  QgsFeature f;
  std::unique_ptr< QgsGeometryEngine > engine;
  while ( fIt.nextFeature( f ) )
  {
    if ( feedback->isCanceled() )
      break;

    if ( !f.hasGeometry() )
      continue;

    engine.reset();

    QgsRectangle bbox = f.geometry().boundingBox();
    request = QgsFeatureRequest().setFilterRect( bbox );
    if ( onlyRequireTargetIds )
      request.setFlags( QgsFeatureRequest::NoGeometry ).setSubsetOfAttributes( QgsAttributeList() );

    QgsFeatureIterator testFeatureIt = targetSource->getFeatures( request );
    QgsFeature testFeature;
    while ( testFeatureIt.nextFeature( testFeature ) )
    {
      if ( feedback->isCanceled() )
        break;

      if ( foundSet.contains( testFeature.id() ) )
      {
        // already added this one, no need for further tests
        continue;
      }
      if ( predicates.count() == 1 && predicates.at( 0 ) == Disjoint && !disjointSet.contains( testFeature.id() ) )
      {
        // calculating only the disjoint set, and we've already eliminated this feature so no need for further tests
        continue;
      }

      if ( !engine )
      {
        engine.reset( QgsGeometry::createGeometryEngine( f.geometry().geometry() ) );
        engine->prepareGeometry();
      }

      for ( Predicate predicate : qgis::as_const( predicates ) )
      {
        bool isMatch = false;
        switch ( predicate )
        {
          case Intersects:
            isMatch = engine->intersects( testFeature.geometry().geometry() );
            break;
          case Contains:
            isMatch = engine->contains( testFeature.geometry().geometry() );
            break;
          case Disjoint:
            if ( engine->intersects( testFeature.geometry().geometry() ) )
            {
              disjointSet.remove( testFeature.id() );
            }
            break;
          case IsEqual:
            isMatch = engine->isEqual( testFeature.geometry().geometry() );
            break;
          case Touches:
            isMatch = engine->touches( testFeature.geometry().geometry() );
            break;
          case Overlaps:
            isMatch = engine->overlaps( testFeature.geometry().geometry() );
            break;
          case Within:
            isMatch = engine->within( testFeature.geometry().geometry() );
            break;
          case Crosses:
            isMatch = engine->crosses( testFeature.geometry().geometry() );
            break;
        }
        if ( isMatch )
        {
          foundSet.insert( testFeature.id() );
          handleFeatureFunction( testFeature );
        }
      }

    }

    current += 1;
    feedback->setProgress( current * step );
  }

  if ( predicates.contains( Disjoint ) )
  {
    disjointSet = disjointSet.subtract( foundSet );
    QgsFeatureRequest disjointReq = QgsFeatureRequest().setFilterFids( disjointSet );
    if ( onlyRequireTargetIds )
      disjointReq.setSubsetOfAttributes( QgsAttributeList() ).setFlags( QgsFeatureRequest::NoGeometry );
    QgsFeatureIterator disjointIt = targetSource->getFeatures( disjointReq );
    QgsFeature f;
    while ( disjointIt.nextFeature( f ) )
    {
      handleFeatureFunction( f );
    }
  }
}