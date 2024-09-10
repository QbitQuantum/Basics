NS_IMETHODIMP
nsPlaceholderFrame::Paint(nsPresContext*      aPresContext,
                          nsIRenderingContext& aRenderingContext,
                          const nsRect&        aDirtyRect,
                          nsFramePaintLayer    aWhichLayer,
                          PRUint32             aFlags)
{
  if ((NS_FRAME_PAINT_LAYER_DEBUG == aWhichLayer) && GetShowFrameBorders()) {
    float p2t;
    p2t = aPresContext->PixelsToTwips();
    aRenderingContext.SetColor(NS_RGB(0, 255, 255));
    nscoord x = NSIntPixelsToTwips(-5, p2t);
    aRenderingContext.FillRect(x, 0, NSIntPixelsToTwips(13, p2t),
                               NSIntPixelsToTwips(3, p2t));
    nscoord y = NSIntPixelsToTwips(-10, p2t);
    aRenderingContext.FillRect(0, y, NSIntPixelsToTwips(3, p2t),
                               NSIntPixelsToTwips(10, p2t));
  }
  DO_GLOBAL_REFLOW_COUNT_DSP("nsPlaceholderFrame", &aRenderingContext);
  return NS_OK;
}