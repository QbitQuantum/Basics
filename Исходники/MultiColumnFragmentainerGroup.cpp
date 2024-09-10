LayoutRect MultiColumnFragmentainerGroup::fragmentsBoundingBox(const LayoutRect& boundingBoxInFlowThread) const
{
    // Find the start and end column intersected by the bounding box.
    LayoutRect flippedBoundingBoxInFlowThread(boundingBoxInFlowThread);
    LayoutFlowThread* flowThread = m_columnSet.flowThread();
    flowThread->flipForWritingMode(flippedBoundingBoxInFlowThread);
    bool isHorizontalWritingMode = m_columnSet.isHorizontalWritingMode();
    LayoutUnit boundingBoxLogicalTop = isHorizontalWritingMode ? flippedBoundingBoxInFlowThread.y() : flippedBoundingBoxInFlowThread.x();
    LayoutUnit boundingBoxLogicalBottom = isHorizontalWritingMode ? flippedBoundingBoxInFlowThread.maxY() : flippedBoundingBoxInFlowThread.maxX();
    if (boundingBoxLogicalBottom <= logicalTopInFlowThread() || boundingBoxLogicalTop >= logicalBottomInFlowThread())
        return LayoutRect(); // The bounding box doesn't intersect this fragmentainer group.
    unsigned startColumn;
    unsigned endColumn;
    columnIntervalForBlockRangeInFlowThread(boundingBoxLogicalTop, boundingBoxLogicalBottom, startColumn, endColumn);

    LayoutRect startColumnFlowThreadOverflowPortion = flowThreadPortionOverflowRectAt(startColumn);
    flowThread->flipForWritingMode(startColumnFlowThreadOverflowPortion);
    LayoutRect startColumnRect(boundingBoxInFlowThread);
    startColumnRect.intersect(startColumnFlowThreadOverflowPortion);
    startColumnRect.move(flowThreadTranslationAtOffset(logicalTopInFlowThreadAt(startColumn)));
    if (startColumn == endColumn)
        return startColumnRect; // It all takes place in one column. We're done.

    LayoutRect endColumnFlowThreadOverflowPortion = flowThreadPortionOverflowRectAt(endColumn);
    flowThread->flipForWritingMode(endColumnFlowThreadOverflowPortion);
    LayoutRect endColumnRect(boundingBoxInFlowThread);
    endColumnRect.intersect(endColumnFlowThreadOverflowPortion);
    endColumnRect.move(flowThreadTranslationAtOffset(logicalTopInFlowThreadAt(endColumn)));
    return unionRect(startColumnRect, endColumnRect);
}