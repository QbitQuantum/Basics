bool SVGInlineTextBox::nodeAtPoint(const HitTestRequest& request, HitTestResult& result, const HitTestLocation& locationInContainer, const LayoutPoint& accumulatedOffset, LayoutUnit, LayoutUnit, HitTestAction)
{
    // FIXME: integrate with InlineTextBox::nodeAtPoint better.
    ASSERT(!isLineBreak());

    PointerEventsHitRules hitRules(PointerEventsHitRules::SVG_TEXT_HITTESTING, request, renderer().style().pointerEvents());
    bool isVisible = renderer().style().visibility() == VISIBLE;
    if (isVisible || !hitRules.requireVisible) {
        if ((hitRules.canHitStroke && (renderer().style().svgStyle().hasStroke() || !hitRules.requireStroke))
            || (hitRules.canHitFill && (renderer().style().svgStyle().hasFill() || !hitRules.requireFill))) {
            FloatPoint boxOrigin(x(), y());
            boxOrigin.moveBy(accumulatedOffset);
            FloatRect rect(boxOrigin, size());
            if (locationInContainer.intersects(rect)) {

                float scalingFactor = renderer().scalingFactor();
                ASSERT(scalingFactor);
                
                float baseline = renderer().scaledFont().fontMetrics().floatAscent() / scalingFactor;

                AffineTransform fragmentTransform;
                for (auto& fragment : m_textFragments) {
                    FloatQuad fragmentQuad(FloatRect(fragment.x, fragment.y - baseline, fragment.width, fragment.height));
                    fragment.buildFragmentTransform(fragmentTransform);
                    if (!fragmentTransform.isIdentity())
                        fragmentQuad = fragmentTransform.mapQuad(fragmentQuad);
                    
                    if (fragmentQuad.containsPoint(locationInContainer.point())) {
                        renderer().updateHitTestResult(result, locationInContainer.point() - toLayoutSize(accumulatedOffset));
                        if (!result.addNodeToRectBasedTestResult(&renderer().textNode(), request, locationInContainer, rect))
                            return true;
                    }
                }
             }
        }
    }
    return false;
}