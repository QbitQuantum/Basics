void CSimpleDcmViewerDlg::drawPictCtrl()
{
	if (TFileManager::getInst()->m_D == 0) return;

	static bool first = true;

	if (first)
	{
		CWnd *cwndPC = GetDlgItem(IDC_PC);
		first = false;
		CRect r;
		WINDOWPLACEMENT winplace;
		cwndPC->GetClientRect(&r);
		cwndPC->GetWindowPlacement(&winplace);

		m_pcW = m_pcH = PC_SIZE;//-2
		m_pcX = winplace.rcNormalPosition.left;
		m_pcY = winplace.rcNormalPosition.top;
	}


	// picture ControlのCWndを取得
	CWnd *pcWnd = GetDlgItem(IDC_PC);
	CDC  *pcDC = pcWnd->GetDC(); 


	BITMAPINFO binfo;
	ZeroMemory(&binfo, sizeof(binfo));
	binfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	binfo.bmiHeader.biBitCount = 32;//1pixel 32-bit (4-byte)
	binfo.bmiHeader.biPlanes   = 1;
	binfo.bmiHeader.biWidth    =  PC_SIZE;
	binfo.bmiHeader.biHeight   = -PC_SIZE; //if negative : origin --> left top 

	byte    *bmpbits; 
	HBITMAP  hbmp = CreateDIBSection(NULL, &binfo, DIB_RGB_COLORS, (void **)(&bmpbits), NULL, 0);

	CBitmap *cbmp = CBitmap::FromHandle(hbmp);
	CDC cbmpDC;
	cbmpDC.CreateCompatibleDC(pcDC);          
	CBitmap *oldBmp = cbmpDC.SelectObject(cbmp);

	const int    imgW = TFileManager::getInst()->m_W;
	const int    imgH = TFileManager::getInst()->m_H;
	const int    imgD = TFileManager::getInst()->m_D;
	const int    imgZ = m_slider_z       .GetPos();
	const float  vMax = (float)m_slider_winLvMax.GetPos();
	const float  vMin = (float)m_slider_winLvMin.GetPos();
	int x0 = m_spin_clipXmin.GetPos32(), x1 = m_spin_clipXmax.GetPos32();  t_cropI(x0, 0, imgW - 1);  t_cropI(x0, 0, imgW - 1);
	int y0 = m_spin_clipYmin.GetPos32(), y1 = m_spin_clipYmax.GetPos32();  t_cropI(y0, 0, imgH - 1);  t_cropI(y0, 0, imgH - 1);
	int z0 = m_spin_clipZmin.GetPos32(), z1 = m_spin_clipZmax.GetPos32();  t_cropI(z0, 0, imgD - 1);  t_cropI(z0, 0, imgD - 1);

	if (imgZ < 0 || imgZ > imgD - 1) return;


	const int WH = imgW * imgH;
	float *sliceImg = TFileManager::getInst()->m_volume[imgZ];

	double xCoef = imgW / (double)PC_SIZE;
	double yCoef = imgH / (double)PC_SIZE;

	for (int y = 0; y < PC_SIZE; ++y)
	{
		for (int x = 0; x < PC_SIZE; ++x)
		{
			int imgX = (int)((x + 0.5) * xCoef);
			int imgY = (int)((y + 0.5) * yCoef);
			int imgI = imgX + imgY * imgW;
			const float imgV = sliceImg[imgI];

			int bmpI = (x + y * PC_SIZE) * 4;
			if (x0 <= imgX && imgX <= x1 && y0 <= imgY && imgY <= y1 && z0 <= imgZ && imgZ <= z1)
			{
				byte c = (byte)(255.0 * min(1, max(0, (imgV - vMin) / (vMax - vMin))));
				bmpbits[bmpI + 0] = bmpbits[bmpI + 1] = bmpbits[bmpI + 2] = c;
			}
			else {
				bmpbits[bmpI + 0] = 192; bmpbits[bmpI + 1] = bmpbits[bmpI + 2] = 0;
			}
		}
	}

	pcDC->BitBlt(1, 1, PC_SIZE - 2, PC_SIZE - 2, &cbmpDC, 0, 0, SRCCOPY);


	//解放
	cbmpDC.SelectObject(oldBmp);
	DeleteDC(cbmpDC);
	DeleteObject(hbmp);
	pcWnd->ReleaseDC(pcDC);
}