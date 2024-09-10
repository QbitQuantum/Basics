/*virtual*/ void
nsHTMLContainerFrame::PaintTextDecorationLines(
                   nsIRenderingContext& aRenderingContext, 
                   nscolor aColor, 
                   nscoord aOffset, 
                   nscoord aAscent, 
                   nscoord aSize) 
{
  nsMargin bp;
  CalcBorderPadding(bp);
  PRIntn skip = GetSkipSides();
  NS_FOR_CSS_SIDES(side) {
    if (skip & (1 << side)) {
      bp.side(side) = 0;
    }
  }
  aRenderingContext.SetColor(aColor);
  nscoord innerWidth = mRect.width - bp.left - bp.right;
  aRenderingContext.FillRect(bp.left, 
                             bp.top + aAscent - aOffset, innerWidth, aSize);
}