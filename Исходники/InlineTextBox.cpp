bool InlineTextBox::nodeAtPoint(HitTestResult& result, const HitTestLocation& locationInContainer, const LayoutPoint& accumulatedOffset, LayoutUnit /* lineTop */, LayoutUnit /*lineBottom*/)
{
    if (isLineBreak())
        return false;

    LayoutPoint boxOrigin = locationIncludingFlipping();
    boxOrigin.moveBy(accumulatedOffset);
    LayoutRect rect(boxOrigin, size());
    // FIXME: both calls to rawValue() below is temporary and should be removed once the transition
    // to LayoutUnit-based types is complete (crbug.com/321237)
    if (m_truncation != cFullTruncation && visibleToHitTestRequest(result.hitTestRequest()) && locationInContainer.intersects(rect)) {
        lineLayoutItem().updateHitTestResult(result, flipForWritingMode(locationInContainer.point() - toLayoutSize(accumulatedOffset)));
        if (!result.addNodeToListBasedTestResult(lineLayoutItem().node(), locationInContainer, rect))
            return true;
    }
    return false;
}