void
nsDisplayCanvasBackgroundColor::Paint(nsDisplayListBuilder* aBuilder,
                                      nsRenderingContext* aCtx)
{
  nsCanvasFrame* frame = static_cast<nsCanvasFrame*>(mFrame);
  nsPoint offset = ToReferenceFrame();
  nsRect bgClipRect = frame->CanvasArea() + offset;
  if (NS_GET_A(mColor) > 0) {
    DrawTarget* drawTarget = aCtx->GetDrawTarget();
    int32_t appUnitsPerDevPixel = mFrame->PresContext()->AppUnitsPerDevPixel();
    Rect devPxRect =
      NSRectToSnappedRect(bgClipRect, appUnitsPerDevPixel, *drawTarget);
    drawTarget->FillRect(devPxRect, ColorPattern(ToDeviceColor(mColor)));
  }
}