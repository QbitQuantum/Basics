NS_IMETHODIMP
nsMathMLmsqrtFrame::Paint(nsPresContext*      aPresContext,
                          nsIRenderingContext& aRenderingContext,
                          const nsRect&        aDirtyRect,
                          nsFramePaintLayer    aWhichLayer,
                          PRUint32             aFlags)
{
  /////////////
  // paint the content we are square-rooting
  nsresult rv = nsMathMLContainerFrame::Paint(aPresContext, aRenderingContext, 
                                              aDirtyRect, aWhichLayer);
  /////////////
  // paint the sqrt symbol
  if (!NS_MATHML_HAS_ERROR(mPresentationData.flags)) {
    mSqrChar.Paint(aPresContext, aRenderingContext,
                   aDirtyRect, aWhichLayer, this);

    if (NS_FRAME_PAINT_LAYER_FOREGROUND == aWhichLayer &&
        mStyleContext->GetStyleVisibility()->IsVisible() &&
        !mBarRect.IsEmpty()) {
      // paint the overline bar
      const nsStyleColor* color = GetStyleColor();
      aRenderingContext.SetColor(color->mColor);
      aRenderingContext.FillRect(mBarRect);
    }

#if defined(NS_DEBUG) && defined(SHOW_BOUNDING_BOX)
    // for visual debug
    if (NS_MATHML_PAINT_BOUNDING_METRICS(mPresentationData.flags)) {
      nsRect rect;
      mSqrChar.GetRect(rect);

      nsBoundingMetrics bm;
      mSqrChar.GetBoundingMetrics(bm);

      aRenderingContext.SetColor(NS_RGB(255,0,0));
      nscoord x = rect.x + bm.leftBearing;
      nscoord y = rect.y;
      nscoord w = bm.rightBearing - bm.leftBearing;
      nscoord h = bm.ascent + bm.descent;
      aRenderingContext.DrawRect(x,y,w,h);
    }
#endif
  }

  return rv;
}