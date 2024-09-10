static void
ApplyAsyncTransformToScrollbarForContent(ContainerLayer* aScrollbar,
                                         Layer* aContent, bool aScrollbarIsChild)
{
  // We only apply the transform if the scroll-target layer has non-container
  // children (i.e. when it has some possibly-visible content). This is to
  // avoid moving scroll-bars in the situation that only a scroll information
  // layer has been built for a scroll frame, as this would result in a
  // disparity between scrollbars and visible content.
  if (aContent->AsContainerLayer() &&
      !LayerHasNonContainerDescendants(aContent->AsContainerLayer())) {
    return;
  }

  const FrameMetrics& metrics = aContent->GetFrameMetrics();
  AsyncPanZoomController* apzc = aContent->GetAsyncPanZoomController();

  Matrix4x4 asyncTransform = apzc->GetCurrentAsyncTransform();
  Matrix4x4 nontransientTransform = apzc->GetNontransientAsyncTransform();
  Matrix4x4 nontransientUntransform = nontransientTransform;
  nontransientUntransform.Invert();
  Matrix4x4 transientTransform = asyncTransform * nontransientUntransform;

  // |transientTransform| represents the amount by which we have scrolled and
  // zoomed since the last paint. Because the scrollbar was sized and positioned based
  // on the painted content, we need to adjust it based on transientTransform so that
  // it reflects what the user is actually seeing now.
  // - The scroll thumb needs to be scaled in the direction of scrolling by the inverse
  //   of the transientTransform scale (representing the zoom). This is because zooming
  //   in decreases the fraction of the whole scrollable rect that is in view.
  // - It needs to be translated in opposite direction of the transientTransform
  //   translation (representing the scroll). This is because scrolling down, which
  //   translates the layer content up, should result in moving the scroll thumb down.
  //   The amount of the translation to the scroll thumb should be such that the ratio
  //   of the translation to the size of the scroll port is the same as the ratio
  //   of the scroll amount to the size of the scrollable rect.
  Matrix4x4 scrollbarTransform;
  if (aScrollbar->GetScrollbarDirection() == Layer::VERTICAL) {
    float scale = metrics.CalculateCompositedSizeInCssPixels().height / metrics.mScrollableRect.height;
    scrollbarTransform = scrollbarTransform * Matrix4x4().Scale(1.f, 1.f / transientTransform._22, 1.f);
    scrollbarTransform = scrollbarTransform * Matrix4x4().Translate(0, -transientTransform._42 * scale, 0);
  }
  if (aScrollbar->GetScrollbarDirection() == Layer::HORIZONTAL) {
    float scale = metrics.CalculateCompositedSizeInCssPixels().width / metrics.mScrollableRect.width;
    scrollbarTransform = scrollbarTransform * Matrix4x4().Scale(1.f / transientTransform._11, 1.f, 1.f);
    scrollbarTransform = scrollbarTransform * Matrix4x4().Translate(-transientTransform._41 * scale, 0, 0);
  }

  Matrix4x4 transform = scrollbarTransform * aScrollbar->GetTransform();

  if (aScrollbarIsChild) {
    // If the scrollbar layer is a child of the content it is a scrollbar for, then we
    // need to do an extra untransform to cancel out the transient async transform on
    // the content. This is needed because otherwise that transient async transform is
    // part of the effective transform of this scrollbar, and the scrollbar will jitter
    // as the content scrolls.
    transientTransform.Invert();
    transform = transform * transientTransform;
  }

  // GetTransform already takes the pre- and post-scale into account.  Since we
  // will apply the pre- and post-scale again when computing the effective
  // transform, we must apply the inverses here.
  transform.Scale(1.0f/aScrollbar->GetPreXScale(),
                  1.0f/aScrollbar->GetPreYScale(),
                  1);
  transform = transform * Matrix4x4().Scale(1.0f/aScrollbar->GetPostXScale(),
                                            1.0f/aScrollbar->GetPostYScale(),
                                            1);
  aScrollbar->AsLayerComposite()->SetShadowTransform(transform);
}