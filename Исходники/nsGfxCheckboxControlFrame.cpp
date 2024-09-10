static void
PaintIndeterminateMark(nsIFrame* aFrame,
                       nsRenderingContext* aCtx,
                       const nsRect& aDirtyRect,
                       nsPoint aPt)
{
  DrawTarget* drawTarget = aCtx->GetDrawTarget();
  int32_t appUnitsPerDevPixel = aFrame->PresContext()->AppUnitsPerDevPixel();

  nsRect rect(aPt, aFrame->GetSize());
  rect.Deflate(aFrame->GetUsedBorderAndPadding());
  rect.y += (rect.height - rect.height/4) / 2;
  rect.height /= 4;

  Rect devPxRect = NSRectToSnappedRect(rect, appUnitsPerDevPixel, *drawTarget);

  drawTarget->FillRect(devPxRect,
                    ColorPattern(ToDeviceColor(aFrame->StyleColor()->mColor)));
}