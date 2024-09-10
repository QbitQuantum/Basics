//绘画函数
VOID CFlashWnd::Draw(HDC hdcDraw, LPCRECT rcDraw, BOOL bErase)
{
	//效验状态
	ASSERT(m_pIControl!=NULL);
	if (m_pIControl==NULL) return;

	//获取位置
	CRect rcRect;
	GetClientRect(m_hWnd,&rcRect);

	//绘画判断 
	if (rcRect.Width()==0) return;
	if (rcRect.Height()==0) return;

	//接口变量
	IOleObject * pIOleObject=m_pIOleObject;
	IViewObject * pIViewObject=(m_pIViewObjectEx!=NULL)?m_pIViewObjectEx:m_pIViewObject;

	if (m_hdcBack)			::DeleteDC(m_hdcBack);
	if (m_bmpBack)			::DeleteObject(m_bmpBack);

	//绘画对象
	/*if ((pIOleObject!=NULL)&&(pIViewObject!=NULL))
	{
		//创建缓冲
		CImage ImageBuffer;
		ImageBuffer.Create(rcRect.Width(),rcRect.Height(),32);

		//绘画对象
		CImageDC ImageDC(ImageBuffer);
		OleDraw(pIViewObject,DVASPECT_TRANSPARENT,ImageDC,&rcRect);
	}*/

	//变量定义
	BITMAPINFOHEADER BitmapInfoHeader;
	ZeroMemory(&BitmapInfoHeader,sizeof(BitmapInfoHeader));

	//设置变量
	BitmapInfoHeader.biSize=sizeof(BITMAPINFOHEADER);
	BitmapInfoHeader.biBitCount=32;
	BitmapInfoHeader.biCompression=BI_RGB;
	BitmapInfoHeader.biPlanes=1;
	BitmapInfoHeader.biWidth=rcRect.Width();
	BitmapInfoHeader.biHeight=-rcRect.Height();

	HDC hdc=::GetDC(m_hWnd);
	m_hdcBack=CreateCompatibleDC(hdc);
	m_bmpBack=CreateDIBSection(hdc, (BITMAPINFO *)&BitmapInfoHeader, DIB_RGB_COLORS, (VOID **)&m_lpBitsOnly, NULL, 0x0);
	SelectObject(m_hdcBack, m_bmpBack);
	::ReleaseDC(m_hWnd,hdc);

	if (m_iBPP==0) m_iBPP=GetDeviceCaps(m_hdcBack,BITSPIXEL);

	CPoint Point(rcRect.left, rcRect.top);
	CSize Size(rcRect.Width(),rcRect.Height());

	//绘画对象
	if ((pIOleObject!=NULL)&&(pIViewObject!=NULL))
	{
		CRect rcTotal;
		::GetClientRect(m_hWnd,&rcTotal);
		if (m_iBPP==32)
		{
			ZeroMemory(m_lpBitsOnly,Size.cx*Size.cy*sizeof(DWORD));
			OleDraw(pIViewObject,DVASPECT_TRANSPARENT,m_hdcBack,&rcTotal);
		}
		else //in 8/16/24 bit screen depth UpdateLayeredWindow produces wrong results - we use underlaying DC to paint to
		{
			//HWND hwndParent=::GetParent(hwnd);
			HWND hwndParent=::GetDesktopWindow();
			HDC hdcParent=::GetWindowDC(hwndParent);

			CRect rcClient;
			GetClientRect(m_hWnd,rcClient);
			
			CPoint pt;
			pt.x=rcClient.left;
			pt.y=rcClient.top;
			ClientToScreen(m_hWnd,&pt);

			BitBlt(m_hdcBack, 0, 0, rcTotal.right, rcTotal.bottom, hdcParent, pt.x, pt.y, SRCCOPY);
			::ReleaseDC(hwndParent, hdcParent);
			OleDraw(pIViewObject, DVASPECT_TRANSPARENT, m_hdcBack, &rcTotal);
		}
	}

/*	CPoint Point(rcRect.left, rcRect.top);
	CSize Size(rcRect.Width(),rcRect.Height());*/

	//变量定义
	BLENDFUNCTION BlendFunction;
	ZeroMemory(&BlendFunction,sizeof(BlendFunction));

	//设置变量
	BlendFunction.BlendOp=AC_SRC_OVER;
	BlendFunction.AlphaFormat=AC_SRC_ALPHA;
	BlendFunction.SourceConstantAlpha=255;

	return;
	//当前帧数
	LONG lCurrentFrame=-1;
	if (m_pIControl!=NULL)
	{
		lCurrentFrame=m_pIControl->CurrentFrame();
	}

	//完成判断
	if ((m_pIControl!=NULL)&&(((m_lCurrentFrame+1)==m_lTotalFrames)||(m_lCurrentFrame>lCurrentFrame)))
	{
		//停止播放
		m_pIControl->Stop();

		//事件通知
		if (m_pIFlashControlSink!=NULL)
		{
			m_pIFlashControlSink->OnEventFlashPlayFinish();
		}
	}

	//设置变量
	if (m_bStop)
		BlendFunction.SourceConstantAlpha=0;

	m_lCurrentFrame=lCurrentFrame;

	CPoint ImagePoint(0,0);
	UpdateLayeredWindow(m_hWnd, NULL, &Point, &Size, m_hdcBack, &ImagePoint, 0, &BlendFunction, m_iBPP==32 ? ULW_ALPHA : ULW_OPAQUE);

	return;
}