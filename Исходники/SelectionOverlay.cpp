void SelectionOverlay::paintContents(const GraphicsLayer* layer, GraphicsContext& c, GraphicsLayerPaintingPhase, const IntRect& inClip)
{
    if (!layer->platformLayer()->superlayer())
        return;

    Selection::iterator it = m_selection.find(layer->platformLayer()->superlayer()->owner());
    if (it == m_selection.end())
        return;

    const Vector<WebCore::FloatQuad>& quads = it->value;
    GraphicsLayer* parent = it->key;

    IntRect clip(inClip);
    clip.move(parent->offsetFromRenderer().width(), parent->offsetFromRenderer().height());

    c.save();

    c.translate(-parent->offsetFromRenderer().width(), -parent->offsetFromRenderer().height());

    Color color = RenderTheme::defaultTheme()->activeSelectionBackgroundColor();
    c.setFillColor(color, ColorSpaceDeviceRGB);

    for (unsigned i = 0; i < quads.size(); ++i) {
        FloatRect rectToPaint = quads[i].boundingBox();

        // Selection on non-composited sub-frames need to be adjusted.
        if (!m_page->focusedOrMainFrame()->contentRenderer()->isComposited()) {
            WebCore::IntPoint framePosition = m_page->frameOffset(m_page->focusedOrMainFrame());
            rectToPaint.move(framePosition.x(), framePosition.y());
        }

        rectToPaint.intersect(clip);
        if (rectToPaint.isEmpty())
            continue;

        c.fillRect(rectToPaint);
    }

    c.restore();
}