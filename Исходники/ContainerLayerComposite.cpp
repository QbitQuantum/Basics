static void DrawVelGraph(const nsIntRect& aClipRect,
                         LayerManagerComposite* aManager,
                         Layer* aLayer) {
  Compositor* compositor = aManager->GetCompositor();
  gfx::Rect clipRect(aClipRect.x, aClipRect.y,
                     aClipRect.width, aClipRect.height);

  TimeStamp now = TimeStamp::Now();
  LayerVelocityUserData* velocityData = GetVelocityData(aLayer);

  if (velocityData->mData.size() >= 1 &&
    now > velocityData->mData[velocityData->mData.size() - 1].mFrameTime +
      TimeDuration::FromMilliseconds(200)) {
    // clear stale data
    velocityData->mData.clear();
  }

  const gfx::Point layerTransform = GetScrollData(aLayer);
  velocityData->mData.push_back(
    LayerVelocityUserData::VelocityData(now,
      static_cast<int>(layerTransform.x), static_cast<int>(layerTransform.y)));

  // TODO: dump to file
  // XXX: Uncomment these lines to enable ScrollGraph logging. This is
  //      useful for HVGA phones or to output the data to accurate
  //      graphing software.
  // printf_stderr("ScrollGraph (%p): %f, %f\n",
  // aLayer, layerTransform.x, layerTransform.y);

  // Keep a circular buffer of 100.
  size_t circularBufferSize = 100;
  if (velocityData->mData.size() > circularBufferSize) {
    velocityData->mData.erase(velocityData->mData.begin());
  }

  if (velocityData->mData.size() == 1) {
    return;
  }

  // Clear and disable the graph when it's flat
  for (size_t i = 1; i < velocityData->mData.size(); i++) {
    if (velocityData->mData[i - 1].mPoint != velocityData->mData[i].mPoint) {
      break;
    }
    if (i == velocityData->mData.size() - 1) {
      velocityData->mData.clear();
      return;
    }
  }

  if (aLayer->GetEffectiveVisibleRegion().GetBounds().width < 300 ||
      aLayer->GetEffectiveVisibleRegion().GetBounds().height < 300) {
    // Don't want a graph for smaller layers
    return;
  }

  aManager->SetDebugOverlayWantsNextFrame(true);

  const Matrix4x4& transform = aLayer->GetEffectiveTransform();
  nsIntRect bounds = aLayer->GetEffectiveVisibleRegion().GetBounds();
  IntSize graphSize = IntSize(200, 100);
  Rect graphRect = Rect(bounds.x, bounds.y, graphSize.width, graphSize.height);

  RefPtr<DrawTarget> dt = aManager->CreateDrawTarget(graphSize, SurfaceFormat::B8G8R8A8);
  dt->FillRect(Rect(0, 0, graphSize.width, graphSize.height),
               ColorPattern(Color(0.2f,0,0,1)));

  int yScaleFactor = 3;
  Point prev = Point(0,0);
  bool first = true;
  for (int32_t i = (int32_t)velocityData->mData.size() - 2; i >= 0; i--) {
    const gfx::Point& p1 = velocityData->mData[i+1].mPoint;
    const gfx::Point& p2 = velocityData->mData[i].mPoint;
    int vel = sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                   (p1.y - p2.y) * (p1.y - p2.y));
    Point next = Point(graphRect.width / circularBufferSize * i,
                       graphRect.height - vel/yScaleFactor);
    if (first) {
      first = false;
    } else {
      dt->StrokeLine(prev, next, ColorPattern(Color(0,1,0,1)));
    }
    prev = next;
  }

  RefPtr<DataTextureSource> textureSource = compositor->CreateDataTextureSource();
  RefPtr<SourceSurface> snapshot = dt->Snapshot();
  RefPtr<DataSourceSurface> data = snapshot->GetDataSurface();
  textureSource->Update(data);

  EffectChain effectChain;
  effectChain.mPrimaryEffect = CreateTexturedEffect(SurfaceFormat::B8G8R8A8,
                                                    textureSource,
                                                    Filter::POINT,
                                                    true);

  compositor->DrawQuad(graphRect,
                       clipRect,
                       effectChain,
                       1.0f,
                       transform);
}