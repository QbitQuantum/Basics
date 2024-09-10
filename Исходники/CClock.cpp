void CClock::DrawTime( CDC *pDc )
{
	CRect  rtClient;
	GetClientRect(&rtClient);
	CDC  dcTransparent;
	dcTransparent.CreateCompatibleDC(pDc);
	CBitmap bitTransParent;
	bitTransParent.CreateCompatibleBitmap(pDc, rtClient.Width(),rtClient.Height());
	dcTransparent.SelectObject(&bitTransParent);

	// 		CRect rectReal(ix1, iy1, ix2, iy2);
	dcTransparent.FillSolidRect(rtClient, RGB(255, 255, 255));
	// 		dcTransparent.Draw3dRect(rectReal, RGB(111, 147, 188), RGB(111, 147, 188));

	dcTransparent.BeginPath();
	dcTransparent.MoveTo(rtClient.Width()/2, rtClient.Height()/2);
	dcTransparent.LineTo(rtClient.Width()/2-80, rtClient.Height()/2);

	float   fEnd = 90.0f;
	dcTransparent.AngleArc(rtClient.Width()/2, rtClient.Height()/2, 120, -180.0f, 270.0f);
	dcTransparent.LineTo(rtClient.Width()/2, rtClient.Height()/2);

	dcTransparent.EndPath();
	CRgn rgn;
	rgn.CreateFromPath(&dcTransparent);
	dcTransparent.FillRgn(&rgn, &CBrush(RGB(188, 199, 216)));

	//内
	dcTransparent.BeginPath();
	dcTransparent.MoveTo(rtClient.Width()/2, rtClient.Height()/2);
	dcTransparent.LineTo(rtClient.Width()/2-40, rtClient.Height()/2);

	dcTransparent.AngleArc(rtClient.Width()/2, rtClient.Height()/2, 40, -180.0f, 270.0f);
	dcTransparent.LineTo(rtClient.Width()/2, rtClient.Height()/2);

	dcTransparent.EndPath();
	CRgn rgn1;
	rgn1.CreateFromPath(&dcTransparent);
	dcTransparent.FillRgn(&rgn1, &CBrush(RGB(255, 255, 0)));

	if( ::AlphaBlend == 0 )
	{
		pDc->StretchBlt(0, 0, rtClient.Width(), rtClient.Height(), 
			&dcTransparent, 0, 0, rtClient.Width(), rtClient.Height(), SRCINVERT );

	}else{

		BLENDFUNCTION bf;    
		memset( &bf, 0, sizeof( bf ) );
		bf.SourceConstantAlpha = 0x9f; //半透明
		bf.BlendOp = AC_SRC_OVER;

		::TransparentBlt(pDc->GetSafeHdc(), 0, 0, rtClient.Width(), rtClient.Height(), 
			dcTransparent.GetSafeHdc( ), 0, 0, rtClient.Width(), rtClient.Height(), RGB(255, 255, 255));
		// 			::AlphaBlend( memDC.GetSafeHdc(), 0, 0, rtClient.Width(), rtClient.Height(), 
		// 				dcTransparent.GetSafeHdc( ), 0, 0, rtClient.Width(), rtClient.Height(), bf );  
	}
	bitTransParent.DeleteObject();
	dcTransparent.DeleteDC();
}