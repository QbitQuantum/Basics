void
nsPageFrame::PaintPrintPreviewBackground(nsIRenderingContext& aRenderingContext,
                                         nsPoint aPt)
{
  // fill page with White
  aRenderingContext.SetColor(NS_RGB(255,255,255));
  // REVIEW: this used to have rect's width and height be the
  // mClipRect if specialClipIsSet ... but that seems completely bogus
  // and inconsistent with the painting of the shadow below
  nsRect rect(aPt, GetSize());
  rect.width  -= mPD->mShadowSize.width;
  rect.height -= mPD->mShadowSize.height;
  aRenderingContext.FillRect(rect);
  // draw line around outside of page
  aRenderingContext.SetColor(NS_RGB(0,0,0));
  aRenderingContext.DrawRect(rect);

  if (mPD->mShadowSize.width > 0 && mPD->mShadowSize.height > 0) {
    aRenderingContext.SetColor(NS_RGB(51,51,51));
    nsRect r(aPt.x,aPt.y, mRect.width, mRect.height);
    nsRect shadowRect;
    shadowRect.x = r.x + r.width - mPD->mShadowSize.width;
    shadowRect.y = r.y + mPD->mShadowSize.height;
    shadowRect.width  = mPD->mShadowSize.width;
    shadowRect.height = r.height - mPD->mShadowSize.height;
    aRenderingContext.FillRect(shadowRect);

    shadowRect.x = r.x + mPD->mShadowSize.width;
    shadowRect.y = r.y + r.height - mPD->mShadowSize.height;
    shadowRect.width  = r.width - mPD->mShadowSize.width;
    shadowRect.height = mPD->mShadowSize.height;
    aRenderingContext.FillRect(shadowRect);
  }
}