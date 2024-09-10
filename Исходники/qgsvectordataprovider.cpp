bool QgsVectorDataProvider::empty() const
{
  QgsFeature f;
  QgsFeatureRequest request;
  request.setNoAttributes();
  request.setFlags( QgsFeatureRequest::NoGeometry );
  request.setLimit( 1 );
  if ( getFeatures( request ).nextFeature( f ) )
    return false;
  else
    return true;
}