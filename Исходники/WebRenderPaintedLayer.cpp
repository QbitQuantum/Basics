bool
WebRenderPaintedLayer::UpdateImageClient()
{
  MOZ_ASSERT(WrManager()->GetPaintedLayerCallback());
  LayerIntRegion visibleRegion = GetVisibleRegion();
  LayerIntRect bounds = visibleRegion.GetBounds();
  LayerIntSize size = bounds.Size();
  IntSize imageSize(size.width, size.height);

  UpdateImageHelper helper(mImageContainer, mImageClient, imageSize);

  {
    RefPtr<DrawTarget> target = helper.GetDrawTarget();
    if (!target) {
      return false;
    }

    target->ClearRect(Rect(0, 0, imageSize.width, imageSize.height));
    target->SetTransform(Matrix().PreTranslate(-bounds.x, -bounds.y));
    RefPtr<gfxContext> ctx =
        gfxContext::CreatePreservingTransformOrNull(target);
    MOZ_ASSERT(ctx); // already checked the target above

    WrManager()->GetPaintedLayerCallback()(this,
                                           ctx,
                                           visibleRegion.ToUnknownRegion(), visibleRegion.ToUnknownRegion(),
                                           DrawRegionClip::DRAW, nsIntRegion(), WrManager()->GetPaintedLayerCallbackData());

    if (gfxPrefs::WebRenderHighlightPaintedLayers()) {
      target->SetTransform(Matrix());
      target->FillRect(Rect(0, 0, imageSize.width, imageSize.height), ColorPattern(Color(1.0, 0.0, 0.0, 0.5)));
    }
  }

  if (!helper.UpdateImage()) {
    return false;
  }

  return true;
}