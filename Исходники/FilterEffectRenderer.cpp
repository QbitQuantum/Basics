bool FilterEffectRendererHelper::prepareFilterEffect(RenderLayer* renderLayer, const LayoutRect& filterBoxRect, const LayoutRect& dirtyRect, const LayoutRect& layerRepaintRect)
{
    ASSERT(m_haveFilterEffect && renderLayer->filterRenderer());
    m_renderLayer = renderLayer;
    m_repaintRect = dirtyRect;

    FilterEffectRenderer* filter = renderLayer->filterRenderer();
    LayoutRect filterSourceRect = filter->computeSourceImageRectForDirtyRect(filterBoxRect, dirtyRect);

    if (filterSourceRect.isEmpty()) {
        // The dirty rect is not in view, just bail out.
        m_haveFilterEffect = false;
        return false;
    }

    // Get the zoom factor to scale the filterSourceRect input
    const RenderLayerModelObject* renderer = renderLayer->renderer();
    const RenderStyle* style = renderer ? renderer->style() : 0;
    float zoom = style ? style->effectiveZoom() : 1.0f;

    AffineTransform absoluteTransform;
    absoluteTransform.translate(filterBoxRect.x(), filterBoxRect.y());
    filter->setAbsoluteTransform(absoluteTransform);
    filter->setAbsoluteFilterRegion(AffineTransform().scale(zoom).mapRect(filterSourceRect));
    filter->setFilterRegion(absoluteTransform.inverse().mapRect(filterSourceRect));
    filter->lastEffect()->determineFilterPrimitiveSubregion();

    bool hasUpdatedBackingStore = filter->updateBackingStoreRect(filterSourceRect);
    if (filter->hasFilterThatMovesPixels()) {
        if (hasUpdatedBackingStore)
            m_repaintRect = filterSourceRect;
        else {
            m_repaintRect.unite(layerRepaintRect);
            m_repaintRect.intersect(filterSourceRect);
        }
    }
    return true;
}