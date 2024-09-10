BOOL CSonicImage::InternalDraw(HDC hdc, int x, int y, DRAW_PARAM * pDp)
{
	CRect rtSrc, rtDest;
	rtDest = CalculateRectByDrawParam(x, y, pDp, rtSrc);

	if(IsAlphaChannelValid() || (pDp && (pDp->dwMask & DP_ALPHA)))
	{
		BLENDFUNCTION blend;
		blend.AlphaFormat = AC_SRC_ALPHA;
		blend.BlendFlags = 0;
		blend.BlendOp = AC_SRC_OVER;
		blend.SourceConstantAlpha = (pDp && (pDp->dwMask & DP_ALPHA)) ? pDp->cAlpha : 255;
		AlphaBlend(hdc, rtDest.left, rtDest.top, rtDest.Width(), rtDest.Height(), m_Dib.GetSafeHdc(), rtSrc.left, rtSrc.top, rtSrc.Width(), rtSrc.Height(), blend);
	}
	else
	{
		if(pDp && (pDp->dwMask & DP_COLOR_KEY))
		{
			TransparentBlt(hdc, rtDest.left, rtDest.top, rtDest.Width(), rtDest.Height(), m_Dib.GetSafeHdc(), rtSrc.left, rtSrc.top, rtSrc.Width(), rtSrc.Height(), pDp->dwColorKey);
		}
		else if(pDp && (pDp->dwMask & DP_DEST_LIMIT || pDp->dwMask & DP_SCALE))
		{
			StretchBlt(hdc, rtDest.left, rtDest.top, rtDest.Width(), rtDest.Height(), m_Dib.GetSafeHdc(), rtSrc.left, rtSrc.top, rtSrc.Width(), rtSrc.Height(), SRCCOPY);
		}
		else
		{
			BitBlt(hdc, rtDest.left, rtDest.top, rtDest.Width(), rtDest.Height(), m_Dib.GetSafeHdc(), rtSrc.left, rtSrc.top, SRCCOPY);
		}
	}
	return TRUE;
}