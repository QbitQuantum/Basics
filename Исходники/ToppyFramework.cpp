void ToppyFramework::Draw(CDC* pDC)
{
	CDC* pMemDC = GetDC();


	if (NeedsRepaint())
	{
		m_TheState.Draw(pMemDC);

		CDC osdDC;
		osdDC.CreateCompatibleDC(pDC);
		osdDC.SetBkColor(TRANSPARENT_COLOUR);
		CBitmap bmOsd;
		bmOsd.CreateCompatibleBitmap(pDC, 720, 576);
		osdDC.SelectObject(&bmOsd);
		osdDC.FillSolidRect(0,0,720,576,TRANSPARENT_COLOUR);
		if (m_OSDregions.Draw(&osdDC))
		{
			CDC monoDC;
			monoDC.CreateCompatibleDC(pDC);
			CBitmap maskBm;
			maskBm.CreateBitmap(720, 576, 1, 1, NULL);
			monoDC.SelectObject(maskBm);
			osdDC.SetBkColor(TRANSPARENT_COLOUR);
			monoDC.BitBlt(0, 0, 720, 576, &osdDC, 0, 0, SRCCOPY);

			CDC tempDC;
			tempDC.CreateCompatibleDC(pDC);
			CBitmap tempBM;
			tempBM.CreateCompatibleBitmap(pDC, 720, 576);
			tempDC.SelectObject(&tempBM);
			tempDC.BitBlt(0,0, 720, 576, pMemDC, 0, 0, SRCCOPY);

			BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255-(BYTE)(GetConfig()->GetOsdTransparency() * 255/100), 0};
			pMemDC->AlphaBlend(0, 0, 720, 576, &osdDC, 0, 0, 720, 576, bf );
	//
	////		 now contains correct over OSD area, wrong in background
	//
			pMemDC->MaskBlt(0,0, 720, 576, &tempDC, 0, 0, maskBm, 0, 0, MAKEROP4(SRCCOPY, DSTCOPY));
			//memDC.BitBlt(0, 0, 720, 576, &osdDC, 0, 0, SRCCOPY);
		}
	}

	pDC->BitBlt(0,0, 720, 576, pMemDC, 0, 0, SRCCOPY); 
	ReleaseDC();
}