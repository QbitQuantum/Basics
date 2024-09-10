int OSDRegion::DrawPixmap(DWORD x, DWORD y, DWORD w, DWORD h, void *pixmap, bool sprite, BYTE dataFormat )
{
	CDC* pDC = GetDC();
	if (dataFormat == OSD_256)
	{
		BYTE* data = (BYTE*) pixmap;
		int lutCount = Regions::GetLutLen();
		DWORD* lut = Regions::GetLut();
		for (unsigned int j = 0; j<h; j++)
		{
			for (unsigned int i = 0; i<w; i++)
			{
				int iIndex = *data;
				data++;
				if ((iIndex == 0) && sprite)
					continue;

				pDC->SetPixelV(i+x + GetXOffs(), y+j + GetYOffs(), lut[iIndex]);
			}
		}
	}
	else if (dataFormat == OSD_1555)
	{
		WORD* pSource = (WORD*) pixmap;
	
		CBitmap bm;
		bm.CreateCompatibleBitmap(pDC, w, h);
		BITMAPINFO bmInfo;
		ZeroMemory(&bmInfo, sizeof(BITMAPINFO));
		bmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmInfo.bmiHeader.biWidth = w;
		bmInfo.bmiHeader.biHeight = -((int)h);
		bmInfo.bmiHeader.biPlanes = 1;
		bmInfo.bmiHeader.biBitCount = 16;
		bmInfo.bmiHeader.biCompression = BI_RGB;

		::SetDIBits(pDC->m_hDC, (HBITMAP)bm.m_hObject, 0, h, pSource, &bmInfo, 0);

		CDC newDC;
		newDC.CreateCompatibleDC(pDC);
		newDC.SelectObject(&bm);
		if ( sprite )
			pDC->TransparentBlt(x + GetXOffs(), y + GetYOffs(), w, h, &newDC, 0, 0, w, h, 0);
		else
			pDC->BitBlt(x  + GetXOffs(), y + GetYOffs(), w, h, &newDC, 0, 0, SRCCOPY);
	}
	else
	{
		LogUnimplemented(__FUNCTION__ "(" __FUNCSIG__ ")");
		return 1;
	}

	ReleaseDC();
	return 0;
}