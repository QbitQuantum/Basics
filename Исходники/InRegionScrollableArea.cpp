InRegionScrollableArea::InRegionScrollableArea(WebPagePrivate* webPage, RenderLayer* layer)
    : m_webPage(webPage)
    , m_layer(layer)
    , m_document(0)
    , m_hasWindowVisibleRectCalculated(false)
{
    ASSERT(webPage);
    ASSERT(layer);
    m_isNull = false;

    // Add a pointer to the enclosing document as the pointer to layer or node along the way may become invalid.
    if (m_layer->enclosingElement())
        m_document = m_layer->enclosingElement()->document();

    // FIXME: Add an ASSERT here as the 'layer' must be scrollable.

    RenderObject* layerRenderer = layer->renderer();
    ASSERT(layerRenderer);

    if (layerRenderer->isRenderView()) { // #document case

        RenderView* renderView = toRenderView(layerRenderer);
        ASSERT(renderView);

        FrameView* view = toRenderView(layerRenderer)->frameView();
        ASSERT(view);

        Frame* frame = view->frame();
        ASSERT_UNUSED(frame, frame);

        m_scrollPosition = m_webPage->mapToTransformed(view->scrollPosition());
        m_contentsSize = m_webPage->mapToTransformed(view->contentsSize());
        m_viewportSize = m_webPage->mapToTransformed(view->visibleContentRect(ScrollableArea::ExcludeScrollbars)).size();
        m_documentViewportRect = view->frameRect();

        m_scrollsHorizontally = view->contentsWidth() > view->visibleWidth();
        m_scrollsVertically = view->contentsHeight() > view->visibleHeight();

        m_supportsCompositedScrolling = true;

        m_scrollTarget = InnerFrame;

        ASSERT(!m_cachedNonCompositedScrollableNode);

        m_camouflagedCompositedScrollableLayer = reinterpret_cast<unsigned>(renderView->compositor()->scrollLayer()->platformLayer());
        m_cachedCompositedScrollableLayer = renderView->compositor()->scrollLayer()->platformLayer();

    } else { // RenderBox-based elements case (scrollable boxes (div's, p's, textarea's, etc)).

        RenderBox* box = m_layer->renderBox();
        ASSERT(box);
        ASSERT(InRegionScrollerPrivate::canScrollRenderBox(box));

        ScrollableArea* scrollableArea = static_cast<ScrollableArea*>(m_layer);
        m_scrollPosition = m_webPage->mapToTransformed(scrollableArea->scrollPosition());
        m_contentsSize = m_webPage->mapToTransformed(scrollableArea->contentsSize());
        m_viewportSize = m_webPage->mapToTransformed(scrollableArea->visibleContentRect(ScrollableArea::ExcludeScrollbars)).size();
        m_documentViewportRect = enclosingIntRect(box->absoluteClippedOverflowRect());

        m_scrollsHorizontally = box->scrollWidth() != box->clientWidth();
        m_scrollsVertically = box->scrollHeight() != box->clientHeight();

        // Check the overflow if its not an input field because overflow can be set to hidden etc. by the content.
        if (!box->node() || !box->node()->rendererIsEditable()) {
            m_scrollsHorizontally = m_scrollsHorizontally && box->scrollsOverflowX();
            m_scrollsVertically = m_scrollsVertically && box->scrollsOverflowY();
        }

        m_scrollTarget = BlockElement;

        // Both caches below are self-exclusive.
        if (m_layer->usesCompositedScrolling()) {
            m_forceContentToBeVerticallyScrollable = true;
            m_supportsCompositedScrolling = true;
            ASSERT(m_layer->backing()->hasScrollingLayer());
            m_camouflagedCompositedScrollableLayer = reinterpret_cast<unsigned>(m_layer->backing()->scrollingContentsLayer()->platformLayer());
            m_cachedCompositedScrollableLayer = m_layer->backing()->scrollingContentsLayer()->platformLayer();
            ASSERT(!m_cachedNonCompositedScrollableNode);
        } else {
            m_camouflagedCompositedScrollableLayer = reinterpret_cast<unsigned>(m_layer->enclosingElement());
            m_cachedNonCompositedScrollableNode = m_layer->enclosingElement();
            ASSERT(!m_cachedCompositedScrollableLayer);
        }
    }
}