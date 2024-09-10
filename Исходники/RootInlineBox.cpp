void RootInlineBox::paintCustomHighlight(RenderObject::PaintInfo& paintInfo, int tx, int ty, const AtomicString& highlightType)
{
    if (!renderer()->shouldPaintWithinRoot(paintInfo) || renderer()->style()->visibility() != VISIBLE || paintInfo.phase != PaintPhaseForeground)
        return;

    Frame* frame = renderer()->document()->frame();
    if (!frame)
        return;
    Page* page = frame->page();
    if (!page)
        return;

    // Get the inflated rect so that we can properly hit test.
    FloatRect rootRect(tx + x(), ty + selectionTop(), width(), selectionHeight());
    FloatRect inflatedRect = page->chrome()->client()->customHighlightRect(renderer()->node(), highlightType, rootRect);
    if (inflatedRect.intersects(paintInfo.rect))
        page->chrome()->client()->paintCustomHighlight(renderer()->node(), highlightType, rootRect, rootRect, false, true);
}