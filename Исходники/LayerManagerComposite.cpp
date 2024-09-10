void
LayerManagerComposite::PostProcessLayers(Layer* aLayer,
                                         nsIntRegion& aOpaqueRegion,
                                         LayerIntRegion& aVisibleRegion,
                                         const Maybe<ParentLayerIntRect>& aClipFromAncestors)
{
  if (aLayer->Extend3DContext()) {
    // For layers participating 3D rendering context, their visible
    // region should be empty (invisible), so we pass through them
    // without doing anything.

    // Direct children of the establisher may have a clip, becaue the
    // item containing it; ex. of nsHTMLScrollFrame, may give it one.
    Maybe<ParentLayerIntRect> layerClip =
      aLayer->AsHostLayer()->GetShadowClipRect();
    Maybe<ParentLayerIntRect> ancestorClipForChildren =
      IntersectMaybeRects(layerClip, aClipFromAncestors);
    MOZ_ASSERT(!layerClip || !aLayer->Combines3DTransformWithAncestors(),
               "Only direct children of the establisher could have a clip");

    for (Layer* child = aLayer->GetLastChild();
         child;
         child = child->GetPrevSibling()) {
      PostProcessLayers(child, aOpaqueRegion, aVisibleRegion,
                        ancestorClipForChildren);
    }
    return;
  }

  nsIntRegion localOpaque;
  // Treat layers on the path to the root of the 3D rendering context as
  // a giant layer if it is a leaf.
  Matrix4x4 transform = GetAccTransformIn3DContext(aLayer);
  Matrix transform2d;
  Maybe<IntPoint> integerTranslation;
  // If aLayer has a simple transform (only an integer translation) then we
  // can easily convert aOpaqueRegion into pre-transform coordinates and include
  // that region.
  if (transform.Is2D(&transform2d)) {
    if (transform2d.IsIntegerTranslation()) {
      integerTranslation = Some(IntPoint::Truncate(transform2d.GetTranslation()));
      localOpaque = aOpaqueRegion;
      localOpaque.MoveBy(-*integerTranslation);
    }
  }

  // Compute a clip that's the combination of our layer clip with the clip
  // from our ancestors.
  LayerComposite* composite = static_cast<LayerComposite*>(aLayer->AsHostLayer());
  Maybe<ParentLayerIntRect> layerClip = composite->GetShadowClipRect();
  MOZ_ASSERT(!layerClip || !aLayer->Combines3DTransformWithAncestors(),
             "The layer with a clip should not participate "
             "a 3D rendering context");
  Maybe<ParentLayerIntRect> outsideClip =
    IntersectMaybeRects(layerClip, aClipFromAncestors);

  // Convert the combined clip into our pre-transform coordinate space, so
  // that it can later be intersected with our visible region.
  // If our transform is a perspective, there's no meaningful insideClip rect
  // we can compute (it would need to be a cone).
  Maybe<LayerIntRect> insideClip;
  if (outsideClip && !transform.HasPerspectiveComponent()) {
    Matrix4x4 inverse = transform;
    if (inverse.Invert()) {
      Maybe<LayerRect> insideClipFloat =
        UntransformBy(ViewAs<ParentLayerToLayerMatrix4x4>(inverse),
                      ParentLayerRect(*outsideClip),
                      LayerRect::MaxIntRect());
      if (insideClipFloat) {
        insideClipFloat->RoundOut();
        LayerIntRect insideClipInt;
        if (insideClipFloat->ToIntRect(&insideClipInt)) {
          insideClip = Some(insideClipInt);
        }
      }
    }
  }

  Maybe<ParentLayerIntRect> ancestorClipForChildren;
  if (insideClip) {
    ancestorClipForChildren =
      Some(ViewAs<ParentLayerPixel>(*insideClip, PixelCastJustification::MovingDownToChildren));
  }

  // Save the value of localOpaque, which currently stores the region obscured
  // by siblings (and uncles and such), before our descendants contribute to it.
  nsIntRegion obscured = localOpaque;

  // Recurse on our descendants, in front-to-back order. In this process:
  //  - Occlusions are computed for them, and they contribute to localOpaque.
  //  - They recalculate their visible regions, taking ancestorClipForChildren
  //    into account, and accumulate them into descendantsVisibleRegion.
  LayerIntRegion descendantsVisibleRegion;
  bool hasPreserve3DChild = false;
  for (Layer* child = aLayer->GetLastChild(); child; child = child->GetPrevSibling()) {
    PostProcessLayers(child, localOpaque, descendantsVisibleRegion, ancestorClipForChildren);
    if (child->Extend3DContext()) {
      hasPreserve3DChild = true;
    }
  }

  // Recalculate our visible region.
  LayerIntRegion visible = composite->GetShadowVisibleRegion();

  // If we have descendants, throw away the visible region stored on this
  // layer, and use the region accumulated by our descendants instead.
  if (aLayer->GetFirstChild() && !hasPreserve3DChild) {
    visible = descendantsVisibleRegion;
  }

  // Subtract any areas that we know to be opaque.
  if (!obscured.IsEmpty()) {
    visible.SubOut(LayerIntRegion::FromUnknownRegion(obscured));
  }

  // Clip the visible region using the combined clip.
  if (insideClip) {
    visible.AndWith(*insideClip);
  }
  composite->SetShadowVisibleRegion(visible);

  // Transform the newly calculated visible region into our parent's space,
  // apply our clip to it (if any), and accumulate it into |aVisibleRegion|
  // for the caller to use.
  ParentLayerIntRegion visibleParentSpace = TransformBy(
      ViewAs<LayerToParentLayerMatrix4x4>(transform), visible);
  if (const Maybe<ParentLayerIntRect>& clipRect = composite->GetShadowClipRect()) {
    visibleParentSpace.AndWith(*clipRect);
  }
  aVisibleRegion.OrWith(ViewAs<LayerPixel>(visibleParentSpace,
      PixelCastJustification::MovingDownToChildren));

  // If we have a simple transform, then we can add our opaque area into
  // aOpaqueRegion.
  if (integerTranslation &&
      !aLayer->HasMaskLayers() &&
      aLayer->IsOpaqueForVisibility()) {
    if (aLayer->IsOpaque()) {
      localOpaque.OrWith(composite->GetFullyRenderedRegion());
    }
    localOpaque.MoveBy(*integerTranslation);
    if (layerClip) {
      localOpaque.AndWith(layerClip->ToUnknownRect());
    }
    aOpaqueRegion.OrWith(localOpaque);
  }
}