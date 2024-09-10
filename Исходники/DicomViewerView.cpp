	void CDicomViewerView::DrawDicomImage(CDC* pDC)
	{
		CRect clientRect;
		this->GetClientRect(&clientRect);
		int nWidth=clientRect.Width(),nHeight=clientRect.Height();
		CDC MemDC; //首先定义一个显示设备对象
		CBitmap MemBitmap;//定义一个位图对象
		//随后建立与屏幕显示兼容的内存显示设备
		MemDC.CreateCompatibleDC(NULL);
		//这时还不能绘图，因为没有地方画 ^_^
		//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小
		MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);
		//将位图选入到内存显示设备中
		//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
		CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
		//先用背景色将位图清除干净，这里我用的是白色作为背景
		//你也可以用自己应该用的颜色
		MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(0,0,0));
		CDicomViewerDoc* pDoc = GetDocument();
		if(pDoc->m_pDicomImage != 0){
			E_DecompressionColorSpaceConversion opt_decompCSconversion = EDC_photometricInterpretation;
			E_UIDCreation opt_uidcreation = EUC_default;
			E_PlanarConfiguration opt_planarconfig = EPC_default;

			OFBool opt_verbose = OFFalse;
			DJDecoderRegistration::registerCodecs(
				opt_decompCSconversion,
				opt_uidcreation,
				opt_planarconfig,
				opt_verbose);
			//根据传输语法构造 DicomImage 从 fstart 帧开始一共 fcount 帧
			DicomImage *pDicomImg = pDoc->m_pDicomImage;//new DicomImage(pDoc->m_pFilePathName);
			//DicomImage *pNewDicomImg = pDicomImg->createScaledImage((const unsigned long)1024,1024);
			LPBITMAPINFOHEADER m_lpBMIH = (LPBITMAPINFOHEADER) new char [sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256];
			m_lpBMIH->biSize = sizeof(BITMAPINFOHEADER);
			m_lpBMIH->biWidth = pDicomImg->getWidth(); 
			m_lpBMIH->biHeight = pDicomImg->getHeight();
			m_lpBMIH->biPlanes = 1;
			m_lpBMIH->biBitCount = 24;
			m_lpBMIH->biCompression = BI_RGB;
			m_lpBMIH->biSizeImage = 0;
			m_lpBMIH->biXPelsPerMeter = 0;
			m_lpBMIH->biYPelsPerMeter = 0;
			pDicomImg->setWindow(pDoc->m_dCurrentWindowCenter, pDoc->m_dCurrentWindowWidth);
			//得到 DICOM文件第 frame 的 DIB数据(假设是 24 位的)
			unsigned long bufSize = 0;
			void* m_pDicomDibits;
			bufSize =pDicomImg->createWindowsDIB(m_pDicomDibits, bufSize, 0, 24, 1, 1);

			double originalX = (clientRect.Width() - m_lpBMIH->biWidth)/2;
			double originalY = (clientRect.Height() - m_lpBMIH->biHeight)/2;
			StretchDIBits (MemDC.GetSafeHdc(),originalX,originalY, m_lpBMIH->biWidth, m_lpBMIH ->biHeight,0,0,m_lpBMIH->biWidth,m_lpBMIH->biHeight,
				m_pDicomDibits, (LPBITMAPINFO) m_lpBMIH,DIB_RGB_COLORS,SRCCOPY);
			delete m_pDicomDibits;
		}
		//将内存中的图拷贝到屏幕上进行显示
		pDC->BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
		MemBitmap.DeleteObject();
		MemDC.DeleteDC();
	}