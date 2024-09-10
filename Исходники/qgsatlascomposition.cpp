QgsGeometry QgsAtlasComposition::currentGeometry( const QgsCoordinateReferenceSystem& crs ) const
{
  if ( !mCoverageLayer || !mCurrentFeature.isValid() || !mCurrentFeature.hasGeometry() )
  {
    return QgsGeometry();
  }

  if ( !crs.isValid() )
  {
    // no projection, return the native geometry
    return mCurrentFeature.geometry();
  }

  QMap<long, QgsGeometry>::const_iterator it = mGeometryCache.constFind( crs.srsid() );
  if ( it != mGeometryCache.constEnd() )
  {
    // we have it in cache, return it
    return it.value();
  }

  if ( mCoverageLayer->crs() == crs )
  {
    return mCurrentFeature.geometry();
  }

  QgsGeometry transformed = mCurrentFeature.geometry();
  transformed.transform( QgsCoordinateTransformCache::instance()->transform( mCoverageLayer->crs().authid(), crs.authid() ) );
  mGeometryCache[crs.srsid()] = transformed;
  return transformed;
}