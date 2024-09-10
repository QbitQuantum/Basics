bool QgsVectorLayerRenderer::render()
{
  if ( mGeometryType == QgsWkbTypes::NullGeometry || mGeometryType == QgsWkbTypes::UnknownGeometry )
    return true;

  if ( !mRenderer )
  {
    mErrors.append( QObject::tr( "No renderer for drawing." ) );
    return false;
  }

  bool usingEffect = false;
  if ( mRenderer->paintEffect() && mRenderer->paintEffect()->enabled() )
  {
    usingEffect = true;
    mRenderer->paintEffect()->begin( mContext );
  }

  // Per feature blending mode
  if ( mContext.useAdvancedEffects() && mFeatureBlendMode != QPainter::CompositionMode_SourceOver )
  {
    // set the painter to the feature blend mode, so that features drawn
    // on this layer will interact and blend with each other
    mContext.painter()->setCompositionMode( mFeatureBlendMode );
  }

  mRenderer->startRender( mContext, mFields );

  QString rendererFilter = mRenderer->filter( mFields );

  QgsRectangle requestExtent = mContext.extent();
  mRenderer->modifyRequestExtent( requestExtent, mContext );

  QgsFeatureRequest featureRequest = QgsFeatureRequest()
                                     .setFilterRect( requestExtent )
                                     .setSubsetOfAttributes( mAttrNames, mFields )
                                     .setExpressionContext( mContext.expressionContext() );
  if ( mRenderer->orderByEnabled() )
  {
    featureRequest.setOrderBy( mRenderer->orderBy() );
  }

  const QgsFeatureFilterProvider *featureFilterProvider = mContext.featureFilterProvider();
  if ( featureFilterProvider )
  {
    featureFilterProvider->filterFeatures( mLayer, featureRequest );
  }
  if ( !rendererFilter.isEmpty() && rendererFilter != QLatin1String( "TRUE" ) )
  {
    featureRequest.combineFilterExpression( rendererFilter );
  }

  // enable the simplification of the geometries (Using the current map2pixel context) before send it to renderer engine.
  if ( mSimplifyGeometry )
  {
    double map2pixelTol = mSimplifyMethod.threshold();
    bool validTransform = true;

    const QgsMapToPixel &mtp = mContext.mapToPixel();
    map2pixelTol *= mtp.mapUnitsPerPixel();
    QgsCoordinateTransform ct = mContext.coordinateTransform();

    // resize the tolerance using the change of size of an 1-BBOX from the source CoordinateSystem to the target CoordinateSystem
    if ( ct.isValid() && !ct.isShortCircuited() )
    {
      try
      {
        QgsPointXY center = mContext.extent().center();
        double rectSize = ct.sourceCrs().isGeographic() ? 0.0008983 /* ~100/(40075014/360=111319.4833) */ : 100;

        QgsRectangle sourceRect = QgsRectangle( center.x(), center.y(), center.x() + rectSize, center.y() + rectSize );
        QgsRectangle targetRect = ct.transform( sourceRect );

        QgsDebugMsgLevel( QStringLiteral( "Simplify - SourceTransformRect=%1" ).arg( sourceRect.toString( 16 ) ), 4 );
        QgsDebugMsgLevel( QStringLiteral( "Simplify - TargetTransformRect=%1" ).arg( targetRect.toString( 16 ) ), 4 );

        if ( !sourceRect.isEmpty() && sourceRect.isFinite() && !targetRect.isEmpty() && targetRect.isFinite() )
        {
          QgsPointXY minimumSrcPoint( sourceRect.xMinimum(), sourceRect.yMinimum() );
          QgsPointXY maximumSrcPoint( sourceRect.xMaximum(), sourceRect.yMaximum() );
          QgsPointXY minimumDstPoint( targetRect.xMinimum(), targetRect.yMinimum() );
          QgsPointXY maximumDstPoint( targetRect.xMaximum(), targetRect.yMaximum() );

          double sourceHypothenuse = std::sqrt( minimumSrcPoint.sqrDist( maximumSrcPoint ) );
          double targetHypothenuse = std::sqrt( minimumDstPoint.sqrDist( maximumDstPoint ) );

          QgsDebugMsgLevel( QStringLiteral( "Simplify - SourceHypothenuse=%1" ).arg( sourceHypothenuse ), 4 );
          QgsDebugMsgLevel( QStringLiteral( "Simplify - TargetHypothenuse=%1" ).arg( targetHypothenuse ), 4 );

          if ( !qgsDoubleNear( targetHypothenuse, 0.0 ) )
            map2pixelTol *= ( sourceHypothenuse / targetHypothenuse );
        }
      }
      catch ( QgsCsException &cse )
      {
        QgsMessageLog::logMessage( QObject::tr( "Simplify transform error caught: %1" ).arg( cse.what() ), QObject::tr( "CRS" ) );
        validTransform = false;
      }
    }

    if ( validTransform )
    {
      QgsSimplifyMethod simplifyMethod;
      simplifyMethod.setMethodType( QgsSimplifyMethod::OptimizeForRendering );
      simplifyMethod.setTolerance( map2pixelTol );
      simplifyMethod.setThreshold( mSimplifyMethod.threshold() );
      simplifyMethod.setForceLocalOptimization( mSimplifyMethod.forceLocalOptimization() );
      featureRequest.setSimplifyMethod( simplifyMethod );

      QgsVectorSimplifyMethod vectorMethod = mSimplifyMethod;
      vectorMethod.setTolerance( map2pixelTol );
      mContext.setVectorSimplifyMethod( vectorMethod );
    }
    else
    {
      QgsVectorSimplifyMethod vectorMethod;
      vectorMethod.setSimplifyHints( QgsVectorSimplifyMethod::NoSimplification );
      mContext.setVectorSimplifyMethod( vectorMethod );
    }
  }
  else
  {
    QgsVectorSimplifyMethod vectorMethod;
    vectorMethod.setSimplifyHints( QgsVectorSimplifyMethod::NoSimplification );
    mContext.setVectorSimplifyMethod( vectorMethod );
  }

  QgsFeatureIterator fit = mSource->getFeatures( featureRequest );
  // Attach an interruption checker so that iterators that have potentially
  // slow fetchFeature() implementations, such as in the WFS provider, can
  // check it, instead of relying on just the mContext.renderingStopped() check
  // in drawRenderer()
  fit.setInterruptionChecker( mInterruptionChecker.get() );

  if ( ( mRenderer->capabilities() & QgsFeatureRenderer::SymbolLevels ) && mRenderer->usingSymbolLevels() )
    drawRendererLevels( fit );
  else
    drawRenderer( fit );

  if ( !fit.isValid() )
  {
    mErrors.append( QStringLiteral( "Data source invalid" ) );
  }

  if ( usingEffect )
  {
    mRenderer->paintEffect()->end( mContext );
  }

  return true;
}