LayoutRect RenderReplaced::clippedOverflowRectForRepaint(const RenderLayerModelObject* repaintContainer) const
{
    if (style()->visibility() != VISIBLE && !enclosingLayer()->hasVisibleContent())
        return LayoutRect();

    // The selectionRect can project outside of the overflowRect, so take their union
    // for repainting to avoid selection painting glitches.
    LayoutRect r = unionRect(localSelectionRect(false), visualOverflowRect());

    RenderView* v = view();
    if (!RuntimeEnabledFeatures::repaintAfterLayoutEnabled() && v) {
        // FIXME: layoutDelta needs to be applied in parts before/after transforms and
        // repaint containers. https://bugs.webkit.org/show_bug.cgi?id=23308
        r.move(v->layoutDelta());
    }

    if (style()) {
        if (v)
            r.inflate(style()->outlineSize());
    }
    computeRectForRepaint(repaintContainer, r);
    return r;
}