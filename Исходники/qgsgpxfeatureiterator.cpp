bool QgsGPXFeatureIterator::readRoute( const QgsRoute& rte, QgsFeature& feature )
{
  if ( rte.points.size() == 0 )
    return false;

  QgsGeometry* theGeometry = readRouteGeometry( rte );

  if ( mRequest.filterType() == QgsFeatureRequest::FilterRect )
  {
    const QgsRectangle& rect = mRequest.filterRect();
    if (( rte.xMax < rect.xMinimum() ) || ( rte.xMin > rect.xMaximum() ) ||
        ( rte.yMax < rect.yMinimum() ) || ( rte.yMin > rect.yMaximum() ) )
      return false;

    if ( !theGeometry->intersects( rect ) ) //use geos for precise intersection test
    {
      delete theGeometry;
      return false;
    }
  }

  if ( !( mRequest.flags() & QgsFeatureRequest::NoGeometry ) )
  {
    feature.setGeometry( theGeometry );
  }
  else
  {
    delete theGeometry;
  }
  feature.setFeatureId( rte.id );
  feature.setValid( true );
  feature.setFields( &mSource->mFields ); // allow name-based attribute lookups
  feature.initAttributes( mSource->mFields.count() );

  readAttributes( feature, rte );

  return true;
}