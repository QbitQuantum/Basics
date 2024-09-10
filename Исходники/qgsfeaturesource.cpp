QVariant QgsFeatureSource::minimumValue( int fieldIndex ) const
{
  if ( fieldIndex < 0 || fieldIndex >= fields().count() )
    return QVariant();

  QgsFeatureRequest req;
  req.setFlags( QgsFeatureRequest::NoGeometry );
  req.setSubsetOfAttributes( QgsAttributeList() << fieldIndex );

  QVariant min;
  QgsFeatureIterator it = getFeatures( req );
  QgsFeature f;
  while ( it.nextFeature( f ) )
  {
    QVariant v = f.attribute( fieldIndex );
    if ( v.isValid() && qgsVariantLessThan( v, min ) )
    {
      min = v;
    }
  }
  return min;
}