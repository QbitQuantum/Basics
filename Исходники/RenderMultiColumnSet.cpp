bool RenderMultiColumnSet::nodeAtPoint(const HitTestRequest& request, HitTestResult& result, const HitTestLocation& locationInContainer, const LayoutPoint& accumulatedOffset, HitTestAction action)
{
    LayoutPoint adjustedLocation = accumulatedOffset + location();

    // Check our bounds next. For this purpose always assume that we can only be hit in the
    // foreground phase (which is true for replaced elements like images).
    // FIXME: Once we support overflow, we need to intersect with that and not with the bounds rect.
    LayoutRect boundsRect = borderBoxRectInRegion(locationInContainer.region());
    boundsRect.moveBy(adjustedLocation);
    if (!visibleToHitTesting() || action != HitTestForeground || !locationInContainer.intersects(boundsRect))
        return false;
    
    // The point is in one specific column. Since columns can't overlap, we don't ever have to test
    // multiple columns. Put the 
    
    // FIXME: It would be nice to jump right to the specific column by just doing math on the point. Since columns
    // can't overlap, we shouldn't have to walk every column like this. The old column code walked all the columns, though,
    // so this is no worse. We'd have to watch out for rect-based hit testing, though, which actually could overlap
    // multiple columns.
    LayoutUnit colGap = columnGap();
    unsigned colCount = columnCount();
    for (unsigned i = 0; i < colCount; i++) {
        // First we get the column rect, which is in our local coordinate space, and we make it physical and apply
        // the hit test offset to it. That gives us the physical location that we want to paint the column at.
        LayoutRect colRect = columnRectAt(i);
        flipForWritingMode(colRect);
        colRect.moveBy(adjustedLocation);
        
        // Next we get the portion of the flow thread that corresponds to this column.
        LayoutRect flowThreadPortion = flowThreadPortionRectAt(i);
        
        // Now get the overflow rect that corresponds to the column.
        LayoutRect flowThreadOverflowPortion = flowThreadPortionOverflowRect(flowThreadPortion, i, colCount, colGap);

        // Do the hit test with the computed rects.
        if (flowThread()->hitTestFlowThreadPortionInRegion(this, flowThreadPortion, flowThreadOverflowPortion, request, result, locationInContainer, colRect.location()))
            return true;
    }
    
    updateHitTestResult(result, locationInContainer.point() - toLayoutSize(adjustedLocation));
    return !result.addNodeToRectBasedTestResult(node(), request, locationInContainer, boundsRect);
}