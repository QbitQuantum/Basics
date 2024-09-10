	void CRecognitionTextView::OnPaint()
	{
		CPaintDC dc(this); // device context for painting
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CScrollView::OnPaint()
		dc.SetWindowOrg(0,m_nVScrollPos);
		hBitmap=(HBITMAP)LoadImage(NULL,filePath,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);
		if(hBitmap != NULL)
		{
			//获取设备的上下文
			CDC* pdc = GetDC();
			pdc->SetWindowOrg(0, m_nVScrollPos);
			CBitmap   bitmap;
			//将bitmap对象与获取的句柄绑定起来
			bitmap.Detach();
			bitmap.Attach(hBitmap);
			CDC memDC;
			//根据已有的上下文，再度创建上下文
			memDC.CreateCompatibleDC(pdc);
			//选择GDI绘图对象
			memDC.SelectObject(&bitmap);
			BITMAP bitinfo;
			bitmap.GetBitmap(&bitinfo);
			srcWidth = bitinfo.bmWidth;
			srcHeight = bitinfo.bmHeight;
			//从指定设备上下文拷贝位图 
			//pdc->BitBlt(0, 0, srcWidth, srcHeight, &memDC, 0, 0, SRCCOPY);
			//获取窗体大小
			CRect rect;
			GetClientRect(&rect);

			int winWidth = rect.Width();
			//int winHeight = rect.Height;
			//计算为中间位置的起点
			xSt = 0 > (winWidth - bitinfo.bmWidth / resizeX)/2 ? 0:(winWidth - bitinfo.bmWidth / resizeX)/2;
			//设置图像拉伸模式
			pdc->SetStretchBltMode(HALFTONE);
			//拉伸图像
			pdc->StretchBlt(xSt,0,bitinfo.bmWidth / resizeX,bitinfo.bmHeight / resizeY,&memDC,0,0,
				bitinfo.bmWidth,bitinfo.bmHeight,SRCCOPY);
			//删除GDI对象
			bitmap.DeleteObject();
			//删除设备上下文环境
			memDC.DeleteDC();
			if(!isSized)
			{
				CRect rect;
				GetClientRect(&rect);
				//m_nViewWidth = rect.Width();
				m_nViewHeight = srcHeight/2;
				m_nVPageSize = rect.Height();
				si.fMask = SIF_ALL;
				si.nMin = 0;
				si.nMax = srcHeight / 2;
				si.nPos = 0;
				si.nPage = rect.Height();
				SetScrollInfo(SB_VERT, &si, TRUE);
				isSized = true;
			}
			drawRectangle(0, m_nVScrollPos);
		}

	}