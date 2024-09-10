void CButtonAppearanceDlg::OnAddImage() 
{
	CBCGPLocalResource locaRes;

	ASSERT (m_pImages != NULL);

	CSize sizeImage = m_pImages->GetImageSize ();
	const BOOL bIsAlphaImage = m_pImages->GetBitsPerPixel() == 32;

	try
	{
		CClientDC	dc (&m_wndButtonList);
		CBitmap 	bitmap;
		CDC 		memDC;	

		memDC.CreateCompatibleDC(&dc);
		
		if (bIsAlphaImage)
		{
			HBITMAP hbmp = CBCGPDrawManager::CreateBitmap_32(sizeImage, NULL);
			if (hbmp == NULL)
			{
				return;
			}

			bitmap.Attach(hbmp);
		}
		else if (!bitmap.CreateCompatibleBitmap (&dc, sizeImage.cx, sizeImage.cy))
		{
			AfxMessageBox (IDP_BCGBARRES_CANNT_CREATE_IMAGE);
			return;
		}

		CBitmap* pOldBitmap = memDC.SelectObject (&bitmap);

		CRect rect (0, 0, sizeImage.cx, sizeImage.cy);
		memDC.FillRect (CRect (0, 0, sizeImage.cx, sizeImage.cy),
						&globalData.brBtnFace);

		if (bIsAlphaImage)
		{
			CBCGPDrawManager dm(memDC);
			dm.FillAlpha(CRect (0, 0, sizeImage.cx, sizeImage.cy), 255);
		}

		memDC.SelectObject (pOldBitmap);

		BITMAP bmp;
		::GetObject (m_pImages->GetImageWell (), sizeof (BITMAP), (LPVOID)&bmp);

		if (g_pWndCustomize != NULL)
		{
			ASSERT_VALID (g_pWndCustomize);

			if (!g_pWndCustomize->OnEditToolbarMenuImage (this, bitmap, bmp.bmBitsPixel))
			{
				return;
			}
		}
		else
		{
			CBCGPImageEditDlg dlg (&bitmap, this, bmp.bmBitsPixel);
			if (dlg.DoModal () != IDOK)
			{
				return;
			}
		}

		if (bIsAlphaImage)
		{
			CRect rectImage(0, 0, sizeImage.cx, sizeImage.cy);

			CBCGPDrawManager::FillAlpha(rectImage, (HBITMAP)bitmap, 255);
			CBCGPDrawManager::FillTransparentAlpha(rectImage, (HBITMAP)bitmap, globalData.clrBtnFace);
		}

		int iImageIndex = m_pImages->AddImage ((HBITMAP) bitmap);
		if (iImageIndex < 0)
		{
			AfxMessageBox (IDP_BCGBARRES_CANNT_CREATE_IMAGE);
			return;
		}

		RebuildImageList ();
		m_wndButtonList.SelectButton (iImageIndex);
	}
	catch (...)
	{
		AfxMessageBox (IDP_BCGBARRES_INTERLAL_ERROR);
	}
}