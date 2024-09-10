static Layer*
FindBackgroundLayer(ReadbackLayer* aLayer, nsIntPoint* aOffset)
{
  gfx::Matrix transform;
  if (!aLayer->GetTransform().Is2D(&transform) ||
      transform.HasNonIntegerTranslation())
    return nullptr;
  nsIntPoint transformOffset(int32_t(transform._31), int32_t(transform._32));

  for (Layer* l = aLayer->GetPrevSibling(); l; l = l->GetPrevSibling()) {
    gfx::Matrix backgroundTransform;
    if (!l->GetTransform().Is2D(&backgroundTransform) ||
        gfx::ThebesMatrix(backgroundTransform).HasNonIntegerTranslation())
      return nullptr;

    nsIntPoint backgroundOffset(int32_t(backgroundTransform._31), int32_t(backgroundTransform._32));
    IntRect rectInBackground(transformOffset - backgroundOffset, aLayer->GetSize());
    const nsIntRegion visibleRegion = l->GetEffectiveVisibleRegion().ToUnknownRegion();
    if (!visibleRegion.Intersects(rectInBackground))
      continue;
    // Since l is present in the background, from here on we either choose l
    // or nothing.
    if (!visibleRegion.Contains(rectInBackground))
      return nullptr;

    if (l->GetEffectiveOpacity() != 1.0 ||
        l->HasMaskLayers() ||
        !(l->GetContentFlags() & Layer::CONTENT_OPAQUE))
    {
      return nullptr;
    }

    // cliprects are post-transform
    const Maybe<ParentLayerIntRect>& clipRect = l->GetEffectiveClipRect();
    if (clipRect && !clipRect->Contains(ViewAs<ParentLayerPixel>(IntRect(transformOffset, aLayer->GetSize()))))
      return nullptr;

    Layer::LayerType type = l->GetType();
    if (type != Layer::TYPE_COLOR && type != Layer::TYPE_PAINTED)
      return nullptr;

    *aOffset = backgroundOffset - transformOffset;
    return l;
  }

  return nullptr;
}