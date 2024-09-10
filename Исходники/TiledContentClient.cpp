bool
ClientTiledLayerBuffer::ComputeProgressiveUpdateRegion(const nsIntRegion& aInvalidRegion,
                                                      const nsIntRegion& aOldValidRegion,
                                                      nsIntRegion& aRegionToPaint,
                                                      BasicTiledLayerPaintData* aPaintData,
                                                      bool aIsRepeated)
{
  aRegionToPaint = aInvalidRegion;

  // If the composition bounds rect is empty, we can't make any sensible
  // decision about how to update coherently. In this case, just update
  // everything in one transaction.
  if (aPaintData->mCompositionBounds.IsEmpty()) {
    aPaintData->mPaintFinished = true;
    return false;
  }

  // If this is a low precision buffer, we force progressive updates. The
  // assumption is that the contents is less important, so visual coherency
  // is lower priority than speed.
  bool drawingLowPrecision = IsLowPrecision();

  // Find out if we have any non-stale content to update.
  nsIntRegion staleRegion;
  staleRegion.And(aInvalidRegion, aOldValidRegion);

  // Find out the current view transform to determine which tiles to draw
  // first, and see if we should just abort this paint. Aborting is usually
  // caused by there being an incoming, more relevant paint.
  ParentLayerRect compositionBounds;
  CSSToParentLayerScale zoom;
#if defined(MOZ_WIDGET_ANDROID)
  bool abortPaint = mManager->ProgressiveUpdateCallback(!staleRegion.Contains(aInvalidRegion),
                                                        compositionBounds, zoom,
                                                        !drawingLowPrecision);
#else
  MOZ_ASSERT(mSharedFrameMetricsHelper);

  ContainerLayer* parent = mThebesLayer->AsLayer()->GetParent();

  bool abortPaint =
    mSharedFrameMetricsHelper->UpdateFromCompositorFrameMetrics(
      parent,
      !staleRegion.Contains(aInvalidRegion),
      drawingLowPrecision,
      compositionBounds,
      zoom);
#endif

  if (abortPaint) {
    // We ignore if front-end wants to abort if this is the first,
    // non-low-precision paint, as in that situation, we're about to override
    // front-end's page/viewport metrics.
    if (!aPaintData->mFirstPaint || drawingLowPrecision) {
      PROFILER_LABEL("ContentClient", "Abort painting");
      aRegionToPaint.SetEmpty();
      return aIsRepeated;
    }
  }

  // Transform the screen coordinates into transformed layout device coordinates.
  LayoutDeviceRect transformedCompositionBounds =
    TransformCompositionBounds(compositionBounds, zoom, aPaintData->mScrollOffset,
                               aPaintData->mResolution, aPaintData->mTransformParentLayerToLayout);

  // Paint tiles that have stale content or that intersected with the screen
  // at the time of issuing the draw command in a single transaction first.
  // This is to avoid rendering glitches on animated page content, and when
  // layers change size/shape.
  LayoutDeviceRect coherentUpdateRect =
    transformedCompositionBounds.Intersect(aPaintData->mCompositionBounds);

  nsIntRect roundedCoherentUpdateRect =
    LayoutDeviceIntRect::ToUntyped(RoundedOut(coherentUpdateRect));

  aRegionToPaint.And(aInvalidRegion, roundedCoherentUpdateRect);
  aRegionToPaint.Or(aRegionToPaint, staleRegion);
  bool drawingStale = !aRegionToPaint.IsEmpty();
  if (!drawingStale) {
    aRegionToPaint = aInvalidRegion;
  }

  // Prioritise tiles that are currently visible on the screen.
  bool paintVisible = false;
  if (aRegionToPaint.Intersects(roundedCoherentUpdateRect)) {
    aRegionToPaint.And(aRegionToPaint, roundedCoherentUpdateRect);
    paintVisible = true;
  }

  // Paint area that's visible and overlaps previously valid content to avoid
  // visible glitches in animated elements, such as gifs.
  bool paintInSingleTransaction = paintVisible && (drawingStale || aPaintData->mFirstPaint);

  // The following code decides what order to draw tiles in, based on the
  // current scroll direction of the primary scrollable layer.
  NS_ASSERTION(!aRegionToPaint.IsEmpty(), "Unexpectedly empty paint region!");
  nsIntRect paintBounds = aRegionToPaint.GetBounds();

  int startX, incX, startY, incY;
  int tileLength = GetScaledTileLength();
  if (aPaintData->mScrollOffset.x >= aPaintData->mLastScrollOffset.x) {
    startX = RoundDownToTileEdge(paintBounds.x);
    incX = tileLength;
  } else {
    startX = RoundDownToTileEdge(paintBounds.XMost() - 1);
    incX = -tileLength;
  }

  if (aPaintData->mScrollOffset.y >= aPaintData->mLastScrollOffset.y) {
    startY = RoundDownToTileEdge(paintBounds.y);
    incY = tileLength;
  } else {
    startY = RoundDownToTileEdge(paintBounds.YMost() - 1);
    incY = -tileLength;
  }

  // Find a tile to draw.
  nsIntRect tileBounds(startX, startY, tileLength, tileLength);
  int32_t scrollDiffX = aPaintData->mScrollOffset.x - aPaintData->mLastScrollOffset.x;
  int32_t scrollDiffY = aPaintData->mScrollOffset.y - aPaintData->mLastScrollOffset.y;
  // This loop will always terminate, as there is at least one tile area
  // along the first/last row/column intersecting with regionToPaint, or its
  // bounds would have been smaller.
  while (true) {
    aRegionToPaint.And(aInvalidRegion, tileBounds);
    if (!aRegionToPaint.IsEmpty()) {
      break;
    }
    if (Abs(scrollDiffY) >= Abs(scrollDiffX)) {
      tileBounds.x += incX;
    } else {
      tileBounds.y += incY;
    }
  }

  if (!aRegionToPaint.Contains(aInvalidRegion)) {
    // The region needed to paint is larger then our progressive chunk size
    // therefore update what we want to paint and ask for a new paint transaction.

    // If we need to draw more than one tile to maintain coherency, make
    // sure it happens in the same transaction by requesting this work be
    // repeated immediately.
    // If this is unnecessary, the remaining work will be done tile-by-tile in
    // subsequent transactions.
    if (!drawingLowPrecision && paintInSingleTransaction) {
      return true;
    }

    mManager->SetRepeatTransaction();
    return false;
  }

  // We're not repeating painting and we've not requested a repeat transaction,
  // so the paint is finished. If there's still a separate low precision
  // paint to do, it will get marked as unfinished later.
  aPaintData->mPaintFinished = true;
  return false;
}