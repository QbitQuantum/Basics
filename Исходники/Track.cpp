void CTrack::Draw(bool bOn, HDC hDC)
{
	if (!m_pAGDC)
		return;

	m_bIsDrawn = bOn;

	if (!hDC)
		hDC = m_pAGDC->GetHDC();

	POINT pt[4];
	pt[0] = m_Distort.p[0];
	pt[1] = m_Distort.p[1];
	pt[2] = m_Distort.p[2];
	pt[3] = m_Distort.p[3];

	CAGMatrix Matrix = m_Matrix * m_ViewToDeviceMatrix;

	// A trick to draw the selection rectangle outside of a transformed object
	if (!(m_iWhatCanDo & TR_DRAWASLINE))
	{
		RECT Offset = {-1, -1, 0, 0};
		Matrix.Inverse().Transform((POINT*)&Offset, 2, false);

		pt[0].x += Offset.left;
		pt[0].y += Offset.top;
		pt[1].x += Offset.right;
		pt[1].y += Offset.top;
		pt[2].x += Offset.right;
		pt[2].y += Offset.bottom;
		pt[3].x += Offset.left;
		pt[3].y += Offset.bottom;
	}

	Matrix.Transform(pt[0]);
	Matrix.Transform(pt[1]);
	Matrix.Transform(pt[2]);
	Matrix.Transform(pt[3]);

	// Before drawing the transform border, open up the clipping to include a border pixel
	HRGN hClipRegion = m_pAGDC->SaveClipRegion();
	RECT rClipRect = m_PageRect;	
	::InflateRect(&rClipRect, 1, 1); // Add a border pixel
	m_pAGDC->SetClipRect(rClipRect, false/*bIncludeRawDC*/);

	if (m_iWhatCanDo & TR_DRAWASLINE)
	{
		Dline(hDC, pt[0].x, pt[0].y, pt[2].x, pt[2].y, bOn);
	}
	else
	{
		Hline(hDC, pt[0].x, pt[0].y, pt[1].x, pt[1].y, bOn);
		Hline(hDC, pt[1].x, pt[1].y, pt[2].x, pt[2].y, bOn);
		Hline(hDC, pt[2].x, pt[2].y, pt[3].x, pt[3].y, bOn);
		Hline(hDC, pt[3].x, pt[3].y, pt[0].x, pt[0].y, bOn);
	}

	DrawHandles(hDC, bOn, pt);

	m_pAGDC->RestoreClipRegion(hClipRegion);
}