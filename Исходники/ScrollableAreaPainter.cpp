void ScrollableAreaPainter::paintResizer(GraphicsContext* context, const IntPoint& paintOffset, const IntRect& damageRect)
{
    if (m_scrollableArea.box().style()->resize() == RESIZE_NONE)
        return;

    IntRect absRect = m_scrollableArea.resizerCornerRect(m_scrollableArea.box().pixelSnappedBorderBoxRect(), ResizerForPointer);
    if (absRect.isEmpty())
        return;
    absRect.moveBy(paintOffset);

    if (m_scrollableArea.resizer()) {
        if (!absRect.intersects(damageRect))
            return;
        ScrollbarPainter::paintIntoRect(m_scrollableArea.resizer(), context, paintOffset, LayoutRect(absRect));
        return;
    }

    if (!RuntimeEnabledFeatures::slimmingPaintEnabled() && !absRect.intersects(damageRect))
        return;

    if (LayoutObjectDrawingRecorder::useCachedDrawingIfPossible(*context, m_scrollableArea.box(), DisplayItem::Resizer))
        return;

    LayoutObjectDrawingRecorder recorder(*context, m_scrollableArea.box(), DisplayItem::Resizer, absRect);

    drawPlatformResizerImage(context, absRect);

    // Draw a frame around the resizer (1px grey line) if there are any scrollbars present.
    // Clipping will exclude the right and bottom edges of this frame.
    if (!m_scrollableArea.hasOverlayScrollbars() && m_scrollableArea.hasScrollbar()) {
        GraphicsContextStateSaver stateSaver(*context);
        context->clip(absRect);
        IntRect largerCorner = absRect;
        largerCorner.setSize(IntSize(largerCorner.width() + 1, largerCorner.height() + 1));
        context->setStrokeColor(Color(217, 217, 217));
        context->setStrokeThickness(1.0f);
        context->setFillColor(Color::transparent);
        context->drawRect(largerCorner);
    }
}