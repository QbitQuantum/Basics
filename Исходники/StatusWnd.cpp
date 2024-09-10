void Status_OnCaptureMouse(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	POINT	pt;
	RECT	rcInner;
	int		Offest;

	if ( HIWORD(lParam) == WM_LBUTTONDOWN )
	{
		
		SetCapture(hWnd);	
		GetCursorPos(&pt);
		GetWindowRect(hWnd,&drc);
		

		rcInner.left = drc.left;
		rcInner.top=drc.top;
		rcInner.bottom=drc.bottom;
		rcInner.right=rcInner.left+60;


		if (PtInRect(&rcInner,pt))			//电击可移动区域
		{
			ptdif.x = pt.x - drc.left;		//计算鼠标坐标与矩形左上角x坐标的距离
			ptdif.y = pt.y - drc.top;		//算鼠标坐标与矩形左上角y坐标的距离
								
			sz.cx = drc.right - drc.left;	//矩形宽度大小
			sz.cy = drc.bottom - drc.top;	//矩形高度大小 
		
			RECT	m_drc = drc;
			DrawUIBorder(&m_drc);
			SetCursor(LoadCursor(NULL, IDC_SIZEALL));
			fCanMove = TRUE;
		
		}

		else								//点击按钮 
		{
			Offest=pt.x-drc.left;
			Offest=Offest/20;
			
			switch(Offest)
			{
			case 3:				//英 中
				{
					if (dwType & TYPE_ZHONGWEN)
					{
						dwType=dwType&~TYPE_ZHONGWEN;
						dwType|=TYPE_YINGYU;
					}
					else if (dwType & TYPE_YINGYU)
					{
						dwType=dwType&~TYPE_YINGYU;
						dwType|=TYPE_ZHONGWEN;
					}
				}
				break;
			case 4:			//全 半
				{
					if (dwType & TYPE_CHUANGJIAO)
					{
						dwType=dwType&~TYPE_CHUANGJIAO;
						dwType|=TYPE_BANJIAO;
					}
					else if (dwType & TYPE_BANJIAO)
					{
						dwType=dwType&~TYPE_BANJIAO;
						dwType|=TYPE_CHUANGJIAO;
					}
				}
				break;
			case 5:			//标点
				{
					if (dwType & TYPE_BIAO1)
					{
						dwType=dwType&~TYPE_BIAO1;
						dwType|=TYPE_BIAO2;
					}
					else if (dwType & TYPE_BIAO2)
					{
						dwType=dwType&~TYPE_BIAO2;
						dwType|=TYPE_BIAO1;
					}
				}
				break;
			case 6:		//小键盘
				{
					HWND hDlg=CreateDialog(hInst,(LPSTR)IDD_SOFTKETBOARD,hStatus,(DLGPROC)KeyBoardProc);
					ShowWindow(hDlg,SW_NORMAL);
				}
				break;
			case 7:		//设置
				{
					SendMessage(hWnd,WM_RBUTTONDOWN,wParam,lParam);
				}//case
				break;
			default:
				break;
			}

			HDC hStatusDC=GetDC(hStatus);
			Status_OnPaint(hStatus,hStatusDC);
			ReleaseDC(hStatus,hStatusDC);

		}

	}
	
	else  if (HIWORD(lParam) == WM_RBUTTONDOWN )
	{
		SetCapture(hWnd);		
	}
	else if (HIWORD(lParam) == WM_MOUSEMOVE)
	{
		
		GetCursorPos(&pt);
		GetWindowRect(hWnd,&drc);
				
		rcInner.left = drc.left;
		rcInner.top=drc.top;
		rcInner.bottom=drc.bottom;
		rcInner.right=rcInner.left+60;

		
		if (PtInRect(&rcInner,pt))					//在移动窗口区域
		{
			SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		}
		else										//在其它区域
		{
			SetCursor(LoadCursor(NULL,IDC_ARROW));
			Offest=pt.x-drc.left;
			Offest=Offest/20;
			switch(Offest)
			{
			case 3:
				{
					if (dwType & TYPE_ZHONGWEN)
					{

					}
					else if (dwType & TYPE_YINGYU)
					{

					}
				}
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			default:
				break;
			}
			
		}
	}
}