void QgsOverlayUtils::resolveOverlaps( const QgsFeatureSource &source, QgsFeatureSink &sink, QgsProcessingFeedback *feedback )
{
  int count = 0;
  int totalCount = source.featureCount();
  if ( totalCount == 0 )
    return;  // nothing to do here

  QgsFeatureId newFid = -1;

  QgsWkbTypes::GeometryType geometryType = QgsWkbTypes::geometryType( QgsWkbTypes::multiType( source.wkbType() ) );

  QgsFeatureRequest requestOnlyGeoms;
  requestOnlyGeoms.setSubsetOfAttributes( QgsAttributeList() );

  QgsFeatureRequest requestOnlyAttrs;
  requestOnlyAttrs.setFlags( QgsFeatureRequest::NoGeometry );

  QgsFeatureRequest requestOnlyIds;
  requestOnlyIds.setFlags( QgsFeatureRequest::NoGeometry );
  requestOnlyIds.setSubsetOfAttributes( QgsAttributeList() );

  // make a set of used feature IDs so that we do not try to reuse them for newly added features
  QgsFeature f;
  QSet<QgsFeatureId> fids;
  QgsFeatureIterator it = source.getFeatures( requestOnlyIds );
  while ( it.nextFeature( f ) )
  {
    if ( feedback->isCanceled() )
      return;

    fids.insert( f.id() );
  }

  QHash<QgsFeatureId, QgsGeometry> geometries;
  QgsSpatialIndex index;
  QHash<QgsFeatureId, QList<QgsFeatureId> > intersectingIds;  // which features overlap a particular area

  // resolve intersections

  it = source.getFeatures( requestOnlyGeoms );
  while ( it.nextFeature( f ) )
  {
    if ( feedback->isCanceled() )
      return;

    QgsFeatureId fid1 = f.id();
    QgsGeometry g1 = f.geometry();
    std::unique_ptr< QgsGeometryEngine > g1engine;

    geometries.insert( fid1, g1 );
    index.insertFeature( f );

    QgsRectangle bbox( f.geometry().boundingBox() );
    const QList<QgsFeatureId> ids = index.intersects( bbox );
    for ( QgsFeatureId fid2 : ids )
    {
      if ( fid1 == fid2 )
        continue;

      if ( !g1engine )
      {
        // use prepared geometries for faster intersection tests
        g1engine.reset( QgsGeometry::createGeometryEngine( g1.constGet() ) );
        g1engine->prepareGeometry();
      }

      QgsGeometry g2 = geometries.value( fid2 );
      if ( !g1engine->intersects( g2.constGet() ) )
        continue;

      QgsGeometry geomIntersection = g1.intersection( g2 );
      if ( !sanitizeIntersectionResult( geomIntersection, geometryType ) )
        continue;

      //
      // add intersection geometry
      //

      // figure out new fid
      while ( fids.contains( newFid ) )
        --newFid;
      fids.insert( newFid );

      geometries.insert( newFid, geomIntersection );
      QgsFeature fx( newFid );
      fx.setGeometry( geomIntersection );

      index.insertFeature( fx );

      // figure out which feature IDs belong to this intersection. Some of the IDs can be of the newly
      // created geometries - in such case we need to retrieve original IDs
      QList<QgsFeatureId> lst;
      if ( intersectingIds.contains( fid1 ) )
        lst << intersectingIds.value( fid1 );
      else
        lst << fid1;
      if ( intersectingIds.contains( fid2 ) )
        lst << intersectingIds.value( fid2 );
      else
        lst << fid2;
      intersectingIds.insert( newFid, lst );

      //
      // update f1
      //

      QgsGeometry g12 = g1.difference( g2 );

      index.deleteFeature( f );
      geometries.remove( fid1 );

      if ( sanitizeDifferenceResult( g12 ) )
      {
        geometries.insert( fid1, g12 );

        QgsFeature f1x( fid1 );
        f1x.setGeometry( g12 );
        index.insertFeature( f1x );
      }

      //
      // update f2
      //

      QgsGeometry g21 = g2.difference( g1 );

      QgsFeature f2old( fid2 );
      f2old.setGeometry( g2 );
      index.deleteFeature( f2old );

      geometries.remove( fid2 );

      if ( sanitizeDifferenceResult( g21 ) )
      {
        geometries.insert( fid2, g21 );

        QgsFeature f2x( fid2 );
        f2x.setGeometry( g21 );
        index.insertFeature( f2x );
      }

      // update our temporary copy of the geometry to what is left from it
      g1 = g12;
      g1engine.reset();
    }

    ++count;
    feedback->setProgress( count / ( double ) totalCount * 100. );
  }

  // release some memory of structures we don't need anymore

  fids.clear();
  index = QgsSpatialIndex();

  // load attributes

  QHash<QgsFeatureId, QgsAttributes> attributesHash;
  it = source.getFeatures( requestOnlyAttrs );
  while ( it.nextFeature( f ) )
  {
    if ( feedback->isCanceled() )
      return;

    attributesHash.insert( f.id(), f.attributes() );
  }

  // store stuff in the sink

  for ( auto i = geometries.constBegin(); i != geometries.constEnd(); ++i )
  {
    if ( feedback->isCanceled() )
      return;

    QgsFeature outFeature( i.key() );
    outFeature.setGeometry( i.value() );

    if ( intersectingIds.contains( i.key() ) )
    {
      const QList<QgsFeatureId> ids = intersectingIds.value( i.key() );
      for ( QgsFeatureId id : ids )
      {
        outFeature.setAttributes( attributesHash.value( id ) );
        sink.addFeature( outFeature, QgsFeatureSink::FastInsert );
      }
    }
    else
    {
      outFeature.setAttributes( attributesHash.value( i.key() ) );
      sink.addFeature( outFeature, QgsFeatureSink::FastInsert );
    }
  }
}