void nsCaret::PaintCaret(DrawTarget& aDrawTarget,
                         nsIFrame* aForFrame,
                         const nsPoint &aOffset)
{
  int32_t contentOffset;
  nsIFrame* frame = GetFrameAndOffset(GetSelectionInternal(),
    mOverrideContent, mOverrideOffset, &contentOffset);
  if (!frame) {
    return;
  }
  NS_ASSERTION(frame == aForFrame, "We're referring different frame");

  int32_t appUnitsPerDevPixel = frame->PresContext()->AppUnitsPerDevPixel();

  nsRect caretRect;
  nsRect hookRect;
  ComputeCaretRects(frame, contentOffset, &caretRect, &hookRect);

  Rect devPxCaretRect =
    NSRectToSnappedRect(caretRect + aOffset, appUnitsPerDevPixel, aDrawTarget);
  Rect devPxHookRect =
    NSRectToSnappedRect(hookRect + aOffset, appUnitsPerDevPixel, aDrawTarget);
  ColorPattern color(ToDeviceColor(frame->GetCaretColorAt(contentOffset)));

  aDrawTarget.FillRect(devPxCaretRect, color);
  if (!hookRect.IsEmpty()) {
    aDrawTarget.FillRect(devPxHookRect, color);
  }
}