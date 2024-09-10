bool CompositingReasonFinder::requiresCompositingForPositionFixed(RenderObject* renderer, const RenderLayer* layer, RenderLayer::ViewportConstrainedNotCompositedReason* viewportConstrainedNotCompositedReason, bool* needToRecomputeCompositingRequirements) const
{
    if (!(m_compositingTriggers & ViewportConstrainedPositionedTrigger))
        return false;

    if (renderer->style()->position() != FixedPosition)
        return false;

    RenderObject* container = renderer->container();
    // If the renderer is not hooked up yet then we have to wait until it is.
    if (!container) {
        ASSERT(m_renderView.document().lifecycle().state() < DocumentLifecycle::InCompositingUpdate);
        // FIXME: Remove this and ASSERT(container) once we get rid of the incremental
        // allocateOrClearCompositedLayerMapping compositing update. This happens when
        // adding the renderer to the tree because we setStyle before addChild in
        // createRendererForElementIfNeeded.
        *needToRecomputeCompositingRequirements = true;
        return false;
    }

    // Don't promote fixed position elements that are descendants of a non-view container, e.g. transformed elements.
    // They will stay fixed wrt the container rather than the enclosing frame.
    if (container != &m_renderView) {
        if (viewportConstrainedNotCompositedReason)
            *viewportConstrainedNotCompositedReason = RenderLayer::NotCompositedForNonViewContainer;
        return false;
    }

    // If the fixed-position element does not have any scrollable ancestor between it and
    // its container, then we do not need to spend compositor resources for it. Start by
    // assuming we can opt-out (i.e. no scrollable ancestor), and refine the answer below.
    bool hasScrollableAncestor = false;

    // The FrameView has the scrollbars associated with the top level viewport, so we have to
    // check the FrameView in addition to the hierarchy of ancestors.
    FrameView* frameView = m_renderView.frameView();
    if (frameView && frameView->isScrollable())
        hasScrollableAncestor = true;

    RenderLayer* ancestor = layer->parent();
    while (ancestor && !hasScrollableAncestor) {
        if (ancestor->scrollsOverflow())
            hasScrollableAncestor = true;
        if (ancestor->renderer() == &m_renderView)
            break;
        ancestor = ancestor->parent();
    }

    if (!hasScrollableAncestor) {
        if (viewportConstrainedNotCompositedReason)
            *viewportConstrainedNotCompositedReason = RenderLayer::NotCompositedForUnscrollableAncestors;
        return false;
    }

    // Subsequent tests depend on layout. If we can't tell now, just keep things the way they are until layout is done.
    // FIXME: Get rid of this codepath once we get rid of the incremental compositing update in RenderLayer::styleChanged.
    if (m_renderView.document().lifecycle().state() < DocumentLifecycle::LayoutClean) {
        *needToRecomputeCompositingRequirements = true;
        return layer->hasCompositedLayerMapping();
    }

    bool paintsContent = layer->isVisuallyNonEmpty() || layer->hasVisibleDescendant();
    if (!paintsContent) {
        if (viewportConstrainedNotCompositedReason)
            *viewportConstrainedNotCompositedReason = RenderLayer::NotCompositedForNoVisibleContent;
        return false;
    }

    // Fixed position elements that are invisible in the current view don't get their own layer.
    if (FrameView* frameView = m_renderView.frameView()) {
        ASSERT(m_renderView.document().lifecycle().state() == DocumentLifecycle::InCompositingUpdate);
        LayoutRect viewBounds = frameView->viewportConstrainedVisibleContentRect();
        LayoutRect layerBounds = layer->boundingBoxForCompositing(layer->compositor()->rootRenderLayer(), RenderLayer::ApplyBoundsChickenEggHacks);
        if (!viewBounds.intersects(enclosingIntRect(layerBounds))) {
            if (viewportConstrainedNotCompositedReason)
                *viewportConstrainedNotCompositedReason = RenderLayer::NotCompositedForBoundsOutOfView;
            return false;
        }
    }

    return true;
}