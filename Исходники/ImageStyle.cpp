//****************************************************************************************
void CImageStyle::OnFillBarBackground  (CDC* pDC, CBCGPBaseControlBar* pBar,
										CRect rectClient, CRect /*rectClip*/,
										BOOL bNCArea)
{
	if (!bNCArea)
	{
		CRgn rgn;
		rgn.CreateRectRgnIndirect (&rectClient);

		pDC->SelectClipRgn (&rgn);
	}

	FillArea (pDC, rectClient, pBar, pBar->IsFloating (), bNCArea);
	pDC->SelectClipRgn (NULL);
}