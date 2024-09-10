BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	const int INIT_ALPHA = 200;//窗口初始化alpha值
	RECT rcDialog;
	HBITMAP hBitmap;
	static BITMAP s_bm;
	static HDC s_hdcMem;
	static HBRUSH s_hBitmapBrush;//位图画刷
	static bool isReturnBrush = false;
	static bool needAlphaBlend = false;
	static bool isLayered = true;

	switch (message)
	{
	case WM_INITDIALOG:
		SetWindowText(hDlg, szDialogTitle);
		// 设置对话框大小可调节,需要设置MAXIZEBOX,MINSIZEBOX才有用
		SetWindowLong(hDlg, GWL_STYLE, GetWindowLong(hDlg, GWL_STYLE) | WS_SIZEBOX);
		//SetWindowLong(hDlg, GWL_STYLE, GetWindowLong(hDlg, GWL_STYLE) & ~WS_CAPTION);
		// 加载背景图片
		// LoadImage支持bmp,ico,cursor,LR_MONOCHROME会变为黑白
		//hBitmap = (HBITMAP)LoadImage(NULL, L"test4.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		// 相对路径，调试时，当前目录是工程目录而不是debug目录，所以图片要放在工程所在目录下
		hBitmap = LoadImageFromFile(L"0.png", needAlphaBlend);
		if (isLayered)
		{
			isReturnBrush = !(needAlphaBlend = false);

			// 注意是设置GWL_EXSTYLE而不是GWL_STYLE
			SetWindowLong(hDlg, GWL_EXSTYLE, GetWindowLong(hDlg, GWL_STYLE) | WS_EX_LAYERED);
			// 设置透明度 0 - completely transparent 255 - opaque，可设置半透明
			SetLayeredWindowAttributes(hDlg, 0, INIT_ALPHA, LWA_ALPHA);
			// 设置透明底色,颜色为指定色的像素变成全透明，其他颜色不透明
			//SetLayeredWindowAttributes(hDlg, RGB(0 , 0 , 0), 0, LWA_COLORKEY);

			// 设置滑块条变化范围
			SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_SETRANGE, (WPARAM)FALSE, MAKELONG(0, 255));
			// 设置滑块条初始位置
			SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_SETPOS, (WPARAM)TRUE, INIT_ALPHA);
		}
			

		if (hBitmap == NULL)
		{
			MessageBox(hDlg, L"LoadImage failed", L"Error", MB_ICONERROR);
			exit(0);
		}
		else
		{			
			if (!isReturnBrush)
			{
				// 将背景图片放入HDC
				HDC hdc;
				//获取当前对话框dc
				hdc = GetDC(hDlg);
				// 创建dc相关的内存dc
				s_hdcMem = CreateCompatibleDC(hdc);

				//把位图选择到兼容DC,之后这个兼容DC就拥有和hBitmap同样大小的绘图区域,超出位图返回的GDI输出都是无效的.
				//选择位图到内存dc,下一步再复制到窗口客户区dc
				SelectObject(s_hdcMem, hBitmap);
				ReleaseDC(hDlg, hdc);

				//通过位图句柄获取获取位图的大小等信息,位图大小事实上也是兼容DC绘图输出的范围
				GetObject(hBitmap, sizeof(s_bm), &s_bm);
			}
		}

		if (isReturnBrush)
		{
			// 创建位图画刷
			s_hBitmapBrush = CreatePatternBrush(hBitmap);
		}	

		return 0;


	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			DeleteDC(s_hdcMem);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;

	case WM_SIZE:
		InvalidateRect(hDlg, NULL, TRUE);
		return TRUE;

	case WM_HSCROLL:
	{
		int nTransparent = SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_GETPOS, 0, 0);
		SetLayeredWindowAttributes(hDlg, 0, nTransparent, LWA_ALPHA);//也会使颜色变暗
	}
	break;

	case WM_QUERYNEWPALETTE:
		return FALSE;
	break;

	case WM_CTLCOLORDLG:
		//needAlphaBlend = false;
		if (needAlphaBlend)//对位图进行alpha操作然后显示,否则用bitBlt对于有alpha通道的位图来说只是透明度为0的部分只会是一片黑色
		{		
			static LPALPHABLEND lpAlphaBlend = (LPALPHABLEND) ::GetProcAddress(::GetModuleHandle(L"msimg32.dll"), "AlphaBlend");

			if (lpAlphaBlend == NULL) 
				lpAlphaBlend = AlphaBitBlt;

			static BLENDFUNCTION ftn = { 0 };
			ftn.BlendOp = AC_SRC_OVER;
			ftn.AlphaFormat = AC_SRC_ALPHA;
			ftn.BlendFlags = 0;
			ftn.SourceConstantAlpha = 255;//整体透明度，与原位图进行alpha合成操作，使原本不透明的变为透明

			GetClientRect(hDlg, &rcDialog);
			lpAlphaBlend((HDC)wParam, 0, 0, rcDialog.right, rcDialog.bottom, s_hdcMem,
				0, 0, s_bm.bmWidth, s_bm.bmHeight, ftn);

			return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));

		}
		else
		{
			if (!isReturnBrush)
			{
				GetClientRect(hDlg, &rcDialog);
				//通过SetStretchBltMode的设置能使StrechBlt在缩放图像更加清晰
				SetStretchBltMode((HDC)wParam, HALFTONE);
				//SetStretchBltMode((HDC)wParam, COLORONCOLOR);
				//复制内存dc到dc,StretchBlt会自动拉伸缩放
				StretchBlt((HDC)wParam, 0, 0, rcDialog.right, rcDialog.bottom, s_hdcMem, 0, 0, s_bm.bmWidth, s_bm.bmHeight, SRCCOPY);
				return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
			}

			if (isReturnBrush) return (BOOL)s_hBitmapBrush;
		}

	}
	return FALSE;
}