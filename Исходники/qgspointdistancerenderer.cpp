bool QgsPointDistanceRenderer::renderFeature( QgsFeature& feature, QgsRenderContext& context, int layer, bool selected, bool drawVertexMarker )
{
  Q_UNUSED( drawVertexMarker );
  Q_UNUSED( context );
  Q_UNUSED( layer );

  //check if there is already a point at that position
  if ( !feature.hasGeometry() )
    return false;

  QgsMarkerSymbol* symbol = firstSymbolForFeature( feature, context );

  //if the feature has no symbol (eg, no matching rule in a rule-based renderer), skip it
  if ( !symbol )
    return false;

  //point position in screen coords
  QgsGeometry geom = feature.geometry();
  QgsWkbTypes::Type geomType = geom.wkbType();
  if ( QgsWkbTypes::flatType( geomType ) != QgsWkbTypes::Point )
  {
    //can only render point type
    return false;
  }

  QString label;
  if ( mDrawLabels )
  {
    label = getLabel( feature );
  }

  QgsCoordinateTransform xform = context.coordinateTransform();
  QgsFeature transformedFeature = feature;
  if ( xform.isValid() )
  {
    geom.transform( xform );
    transformedFeature.setGeometry( geom );
  }

  double searchDistance = mTolerance * QgsSymbolLayerUtils::mapUnitScaleFactor( context, mToleranceUnit, mToleranceMapUnitScale );
  QgsPoint point = transformedFeature.geometry().asPoint();
  QList<QgsFeatureId> intersectList = mSpatialIndex->intersects( searchRect( point, searchDistance ) );
  if ( intersectList.empty() )
  {
    mSpatialIndex->insertFeature( transformedFeature );
    // create new group
    ClusteredGroup newGroup;
    newGroup << GroupedFeature( transformedFeature, symbol, selected, label );
    mClusteredGroups.push_back( newGroup );
    // add to group index
    mGroupIndex.insert( transformedFeature.id(), mClusteredGroups.count() - 1 );
    mGroupLocations.insert( transformedFeature.id(), point );
  }
  else
  {
    // find group with closest location to this point (may be more than one within search tolerance)
    QgsFeatureId minDistFeatureId = intersectList.at( 0 );
    double minDist = mGroupLocations.value( minDistFeatureId ).distance( point );
    for ( int i = 1; i < intersectList.count(); ++i )
    {
      QgsFeatureId candidateId = intersectList.at( i );
      double newDist = mGroupLocations.value( candidateId ).distance( point );
      if ( newDist < minDist )
      {
        minDist = newDist;
        minDistFeatureId = candidateId;
      }
    }

    int groupIdx = mGroupIndex[ minDistFeatureId ];
    ClusteredGroup& group = mClusteredGroups[groupIdx];

    // calculate new centroid of group
    QgsPoint oldCenter = mGroupLocations.value( minDistFeatureId );
    mGroupLocations[ minDistFeatureId ] = QgsPoint(( oldCenter.x() * group.size() + point.x() ) / ( group.size() + 1.0 ),
                                          ( oldCenter.y() * group.size() + point.y() ) / ( group.size() + 1.0 ) );

    // add to a group
    group << GroupedFeature( transformedFeature, symbol, selected, label );
    // add to group index
    mGroupIndex.insert( transformedFeature.id(), groupIdx );
  }

  return true;
}