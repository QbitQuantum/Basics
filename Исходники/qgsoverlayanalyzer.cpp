void QgsOverlayAnalyzer::intersectFeature( QgsFeature &f, QgsVectorFileWriter *vfw,
    QgsVectorLayer *vl, QgsSpatialIndex *index )
{
  if ( !f.hasGeometry() )
  {
    return;
  }

  QgsGeometry featureGeometry = f.geometry();
  QgsGeometry intersectGeometry;
  QgsFeature overlayFeature;

  QList<QgsFeatureId> intersects = index->intersects( featureGeometry.boundingBox() );
  QgsFeatureRequest req = QgsFeatureRequest().setFilterFids( intersects.toSet() );
  QgsFeatureIterator intersectIt = vl->getFeatures( req );
  QgsFeature outFeature;
  while ( intersectIt.nextFeature( overlayFeature ) )
  {
    if ( featureGeometry.intersects( overlayFeature.geometry() ) )
    {
      intersectGeometry = featureGeometry.intersection( overlayFeature.geometry() );

      outFeature.setGeometry( intersectGeometry );
      QgsAttributes attributesA = f.attributes();
      QgsAttributes attributesB = overlayFeature.attributes();
      combineAttributeMaps( attributesA, attributesB );
      outFeature.setAttributes( attributesA );

      //add it to vector file writer
      if ( vfw )
      {
        vfw->addFeature( outFeature );
      }
    }
  }
}