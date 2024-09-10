QgsFeature QgsTransformAlgorithm::processFeature( const QgsFeature &f, QgsProcessingContext &, QgsProcessingFeedback * )
{
  QgsFeature feature = f;
  if ( !mCreatedTransform )
  {
    mCreatedTransform = true;
    mTransform = QgsCoordinateTransform( sourceCrs(), mDestCrs, mTransformContext );
  }

  if ( feature.hasGeometry() )
  {
    QgsGeometry g = feature.geometry();
    if ( g.transform( mTransform ) == 0 )
    {
      feature.setGeometry( g );
    }
    else
    {
      feature.clearGeometry();
    }
  }
  return feature;
}