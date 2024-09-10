bool hitTestFlow(const RenderBlockFlow& flow, const Layout& layout, const HitTestRequest& request, HitTestResult& result, const HitTestLocation& locationInContainer, const LayoutPoint& accumulatedOffset, HitTestAction hitTestAction)
{
    if (hitTestAction != HitTestForeground)
        return false;

    if (!layout.runCount())
        return false;

    RenderStyle& style = flow.style();
    if (style.visibility() != VISIBLE || style.pointerEvents() == PE_NONE)
        return false;

    RenderObject& renderer = *flow.firstChild();
    LayoutRect rangeRect = locationInContainer.boundingBox();
    rangeRect.moveBy(-accumulatedOffset);

    auto resolver = lineResolver(flow, layout);
    for (FloatRect lineRect : resolver.rangeForRect(rangeRect)) {
        lineRect.moveBy(accumulatedOffset);
        if (!locationInContainer.intersects(lineRect))
            continue;
        renderer.updateHitTestResult(result, locationInContainer.point() - toLayoutSize(accumulatedOffset));
        if (!result.addNodeToRectBasedTestResult(renderer.node(), request, locationInContainer, lineRect))
            return true;
    }

    return false;
}