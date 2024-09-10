void
WebRenderPaintedLayerBlob::RenderLayer(wr::DisplayListBuilder& aBuilder,
                                       const StackingContextHelper& aSc)
{
  LayerIntRegion visibleRegion = GetVisibleRegion();
  LayerIntRect bounds = visibleRegion.GetBounds();
  LayerIntSize size = bounds.Size();

  if (visibleRegion.IsEmpty()) {
    if (gfxPrefs::LayersDump()) {
      printf_stderr("PaintedLayer %p skipping\n", this->GetLayer());
    }
    return;
  }

  nsIntRegion regionToPaint;
  regionToPaint.Sub(mVisibleRegion.ToUnknownRegion(), mValidRegion);

  // We have something to paint but can't. This usually happens only in
  // empty transactions
  if (!regionToPaint.IsEmpty() && !WrManager()->GetPaintedLayerCallback()) {
    WrManager()->SetTransactionIncomplete();
    return;
  }

  IntSize imageSize(size.ToUnknownSize());
  if (!regionToPaint.IsEmpty() && WrManager()->GetPaintedLayerCallback()) {
    RefPtr<gfx::DrawEventRecorderMemory> recorder = MakeAndAddRef<gfx::DrawEventRecorderMemory>();
    RefPtr<gfx::DrawTarget> dummyDt = gfx::Factory::CreateDrawTarget(gfx::BackendType::SKIA, imageSize, gfx::SurfaceFormat::B8G8R8X8);
    RefPtr<gfx::DrawTarget> dt = gfx::Factory::CreateRecordingDrawTarget(recorder, dummyDt);

    dt->ClearRect(Rect(0, 0, imageSize.width, imageSize.height));
    dt->SetTransform(Matrix().PreTranslate(-bounds.x, -bounds.y));
    RefPtr<gfxContext> ctx = gfxContext::CreatePreservingTransformOrNull(dt);
    MOZ_ASSERT(ctx); // already checked the target above

    WrManager()->GetPaintedLayerCallback()(this,
                                           ctx,
                                           visibleRegion.ToUnknownRegion(), visibleRegion.ToUnknownRegion(),
                                           DrawRegionClip::DRAW, nsIntRegion(), WrManager()->GetPaintedLayerCallbackData());

    if (gfxPrefs::WebRenderHighlightPaintedLayers()) {
      dt->SetTransform(Matrix());
      dt->FillRect(Rect(0, 0, imageSize.width, imageSize.height), ColorPattern(Color(1.0, 0.0, 0.0, 0.5)));
    }

    wr::ByteBuffer bytes;
    bytes.Allocate(recorder->RecordingSize());
    DebugOnly<bool> ok = recorder->CopyRecording((char*)bytes.AsSlice().begin().get(), bytes.AsSlice().length());
    MOZ_ASSERT(ok);

    //XXX: We should switch to updating the blob image instead of adding a new one
    //     That will get rid of this discard bit
    if (mImageKey.isSome()) {
      WrManager()->AddImageKeyForDiscard(mImageKey.value());
    }
    mImageKey = Some(GetImageKey());
    WrBridge()->SendAddBlobImage(mImageKey.value(), imageSize, size.width * 4, dt->GetFormat(), bytes);
  } else {
    MOZ_ASSERT(GetInvalidRegion().IsEmpty());
  }

  ScrollingLayersHelper scroller(this, aBuilder, aSc);
  StackingContextHelper sc(aSc, aBuilder, this);
  LayerRect rect = Bounds();
  DumpLayerInfo("PaintedLayer", rect);

  LayerRect clipRect = ClipRect().valueOr(rect);
  Maybe<WrImageMask> mask = BuildWrMaskLayer(&sc);
  WrClipRegionToken clip = aBuilder.PushClipRegion(
      sc.ToRelativeWrRect(clipRect),
      mask.ptrOr(nullptr));

  aBuilder.PushImage(sc.ToRelativeWrRect(rect), clip, wr::ImageRendering::Auto, mImageKey.value());
}