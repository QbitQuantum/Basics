bool InlineBox::nodeAtPoint(HitTestResult& result, const HitTestLocation& locationInContainer, const LayoutPoint& accumulatedOffset, LayoutUnit /* lineTop */, LayoutUnit /* lineBottom */)
{
    // Hit test all phases of replaced elements atomically, as though the replaced element established its
    // own stacking context.  (See Appendix E.2, section 6.4 on inline block/table elements in the CSS2.1
    // specification.)
    LayoutPoint childPoint = accumulatedOffset;
    if (parent()->lineLayoutItem().hasFlippedBlocksWritingMode()) // Faster than calling containingBlock().
        childPoint = layoutObject().containingBlock()->flipForWritingModeForChild(&toLayoutBox(layoutObject()), childPoint);

    if (lineLayoutItem().style()->hasBorderRadius()) {
        LayoutRect borderRect = logicalFrameRect();
        borderRect.moveBy(accumulatedOffset);
        FloatRoundedRect border = lineLayoutItem().style()->getRoundedBorderFor(borderRect);
        if (!locationInContainer.intersects(border))
            return false;
    }

    return lineLayoutItem().hitTest(result, locationInContainer, childPoint);
}