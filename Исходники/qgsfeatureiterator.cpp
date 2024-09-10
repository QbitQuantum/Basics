void QgsAbstractFeatureIterator::geometryToDestinationCrs( QgsFeature &feature, const QgsCoordinateTransform &transform ) const
{
  if ( transform.isValid() && feature.hasGeometry() )
  {
    try
    {
      QgsGeometry g = feature.geometry();
      g.transform( transform );
      feature.setGeometry( g );
    }
    catch ( QgsCsException & )
    {
      // transform error
      if ( mRequest.transformErrorCallback() )
      {
        mRequest.transformErrorCallback()( feature );
      }
      // remove geometry - we can't reproject so better not return a geometry in a different crs
      feature.clearGeometry();
    }
  }
}