bool QgsHeatmapRenderer::renderFeature( QgsFeature& feature, QgsRenderContext& context, int layer, bool selected, bool drawVertexMarker )
{
  Q_UNUSED( layer );
  Q_UNUSED( selected );
  Q_UNUSED( drawVertexMarker );

  if ( !context.painter() )
  {
    return false;
  }

  if ( !feature.constGeometry() || feature.constGeometry()->type() != QGis::Point )
  {
    //can only render point type
    return false;
  }

  double weight = 1.0;
  if ( !mWeightExpressionString.isEmpty() )
  {
    QVariant value;
    if ( mWeightAttrNum == -1 )
    {
      Q_ASSERT( mWeightExpression.data() );
      value = mWeightExpression->evaluate( &feature );
    }
    else
    {
      QgsAttributes attrs = feature.attributes();
      value = attrs.value( mWeightAttrNum );
    }
    bool ok = false;
    double evalWeight = value.toDouble( &ok );
    if ( ok )
    {
      weight = evalWeight;
    }
  }

  int width = context.painter()->device()->width() / mRenderQuality;
  int height = context.painter()->device()->height() / mRenderQuality;

  //transform geometry if required
  QgsGeometry* transformedGeom = 0;
  const QgsCoordinateTransform* xform = context.coordinateTransform();
  if ( xform )
  {
    transformedGeom = new QgsGeometry( *feature.constGeometry() );
    transformedGeom->transform( *xform );
  }

  //convert point to multipoint
  QgsMultiPoint multiPoint = convertToMultipoint( transformedGeom ? transformedGeom : feature.constGeometry() );

  delete transformedGeom;
  transformedGeom = 0;

  //loop through all points in multipoint
  for ( QgsMultiPoint::const_iterator pointIt = multiPoint.constBegin(); pointIt != multiPoint.constEnd(); ++pointIt )
  {
    QgsPoint pixel = context.mapToPixel().transform( *pointIt );
    int pointX = pixel.x() / mRenderQuality;
    int pointY = pixel.y() / mRenderQuality;
    for ( int x = qMax( pointX - mRadiusPixels, 0 ); x < qMin( pointX + mRadiusPixels, width ); ++x )
    {
      for ( int y = qMax( pointY - mRadiusPixels, 0 ); y < qMin( pointY + mRadiusPixels, height ); ++y )
      {
        int index = y * width + x;
        if ( index >= mValues.count( ) )
        {
          continue;
        }
        double distanceSquared = pow( pointX - x, 2.0 ) + pow( pointY - y, 2.0 );
        if ( distanceSquared > mRadiusSquared )
        {
          continue;
        }

        double score = weight * quarticKernel( sqrt( distanceSquared ), mRadiusPixels );
        double value = mValues[ index ] + score;
        if ( value > mCalculatedMaxValue )
        {
          mCalculatedMaxValue = value;
        }
        mValues[ index ] = value;
      }
    }
  }

  mFeaturesRendered++;
#if 0
  //TODO - enable progressive rendering
  if ( mFeaturesRendered % 200  == 0 )
  {
    renderImage( context );
  }
#endif
  return true;
}