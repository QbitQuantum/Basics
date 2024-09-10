RoundedRect RenderStyle::getRoundedInnerBorderFor(const LayoutRect& borderRect,
    int topWidth, int bottomWidth, int leftWidth, int rightWidth, bool includeLogicalLeftEdge, bool includeLogicalRightEdge) const
{
    LayoutRect innerRect(borderRect.x() + leftWidth,
               borderRect.y() + topWidth,
               borderRect.width() - leftWidth - rightWidth,
               borderRect.height() - topWidth - bottomWidth);

    RoundedRect roundedRect(pixelSnappedIntRect(innerRect));

    if (hasBorderRadius()) {
        RoundedRect::Radii radii = getRoundedBorderFor(borderRect).radii();
        radii.shrink(topWidth, bottomWidth, leftWidth, rightWidth);
        roundedRect.includeLogicalEdges(radii, includeLogicalLeftEdge, includeLogicalRightEdge);
    }
    return roundedRect;
}