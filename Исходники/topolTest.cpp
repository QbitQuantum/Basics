ErrorList topolTest::checkPointInPolygon( double tolerance, QgsVectorLayer *layer1, QgsVectorLayer *layer2, bool isExtent )
{
  Q_UNUSED( tolerance );

  int i = 0;
  ErrorList errorList;

  if ( layer1->geometryType() != QGis::Point )
  {
    return errorList;
  }

  if ( layer2->geometryType() != QGis::Polygon )
  {
    return errorList;
  }

  QgsSpatialIndex* index = mLayerIndexes[layer2->id()];

  QgsGeometry* canvasExtentPoly = QgsGeometry::fromWkt( theQgsInterface->mapCanvas()->extent().asWktPolygon() );

  QList<FeatureLayer>::Iterator it;
  for ( it = mFeatureList1.begin(); it != mFeatureList1.end(); ++it )
  {
    if ( !( ++i % 100 ) )
      emit progress( i );
    if ( testCancelled() )
      break;
    QgsGeometry* g1 = it->feature.geometry();
    QgsRectangle bb = g1->boundingBox();
    QList<QgsFeatureId> crossingIds;
    crossingIds = index->intersects( bb );
    QList<QgsFeatureId>::Iterator cit = crossingIds.begin();
    QList<QgsFeatureId>::ConstIterator crossingIdsEnd = crossingIds.end();
    bool touched = false;
    for ( ; cit != crossingIdsEnd; ++cit )
    {
      QgsFeature& f = mFeatureMap2[*cit].feature;
      const QgsGeometry* g2 = f.constGeometry();
      if ( !g2 || !g2->asGeos() )
      {
        QgsMessageLog::logMessage( tr( "Second geometry missing or GEOS import failed." ), tr( "Topology plugin" ) );
        continue;
      }
      if ( g2->contains( g1 ) )
      {
        touched = true;
        break;
      }
    }
    if ( !touched )
    {
      QgsGeometry* conflictGeom = new QgsGeometry( *g1 );

      if ( isExtent )
      {
        if ( canvasExtentPoly->disjoint( conflictGeom ) )
        {
          delete conflictGeom;
          continue;
        }
      }

      QList<FeatureLayer> fls;
      fls << *it << *it;
      //bb.scale(10);

      TopolErrorPointNotInPolygon* err = new TopolErrorPointNotInPolygon( bb, conflictGeom, fls );
      errorList << err;
    }
  }

  delete canvasExtentPoly;
  return errorList;
}