LRESULT CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char sTitle[100]="title";
	PAINTSTRUCT ps;
	static HDC dc;
	static RECT r;
	LPDRAWITEMSTRUCT dItem;
	char text[20];
	int len;
	SIZE sz;

    HBRUSH hB;                  // brush handle
	static HINSTANCE hInst;
	static RECT btnrect;
	// The struct that WM_DRAWITEM needs:
	static DRAWITEMSTRUCT* pdis;
	// Width and height of the client area:
	static long cxClient, cyClient;
	TCHAR s[BUFFSIZE];
	int iResult;
	HWND hLevelUpButton,hLevelDnButton;
	HWND hButton;
	switch (uMsg)
	{

	case WM_INITDIALOG:// WM_INITDIALOG message is sent before dialog is displayed
		{
			hButton = CreateWindow(TEXT("button"), TEXT("Beep"),    
			WS_VISIBLE | WS_CHILD ,
			20, 50, 80, 25,        
			hwndDlg, (HMENU) 1, NULL, NULL);    
			GetWindowText(hButton,sTitle,sizeof(sTitle)/sizeof(char));
			//~ MessageBoxPrintf("hi",sTitle);
			
			hButton = CreateWindow(TEXT("button"), TEXT("Quit!"),    
			WS_VISIBLE | WS_CHILD|BS_OWNERDRAW,
			120, 50, 80, 25,        
			hwndDlg, (HMENU) 2, NULL, NULL);   	


						//~ // 2. A button with style BS_OWNERDRAW
			//~ // This is what the article is about :)
			//~ hLevelUpButton = CreateWindow(_T("button"), TEXT("Beep"),
				//~ WS_CHILD | WS_VISIBLE|BS_OWNERDRAW,
				//~ 0,0,40,30,
				//~ hwndDlg,
				//~ (HMENU) IDC_BUTTON1,
				//~ hInst,
				//~ NULL);
			//~ if (NULL == hLevelUpButton) {
				//~ _stprintf(s, _T("! hLevelUpButton NULL"));
				//~ myWriteToLog(s);
			//~ }
			//~ // 3. Second owner draw button:
			//~ hLevelDnButton = CreateWindow(_T("button"), NULL,
				//~ WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
				//~ 0,0,0,0,
				//~ hwndDlg,
				//~ (HMENU) IDC_BUTTON2,
				//~ hInst,
				//~ NULL);
			//~ if (NULL == hLevelDnButton) {
				//~ _stprintf(s, _T("! hLevelDnButton NULL"));
				//~ myWriteToLog(s);
			//~ }
			return TRUE;
		}
		break;
		case WM_DRAWITEM:

		dItem = (DRAWITEMSTRUCT*)lParam;
		
				SetBkColor(dItem->hDC, RGB(255,0,0));
                SetTextColor(dItem->hDC, RGB(0,0,0xFF));
				memset(text, '\0', 20);

				GetWindowText(dItem->hwndItem, text, 20);
				len=lstrlen(text);

				GetTextExtentPoint32(dItem->hDC, text, len, &sz);

				ExtTextOut( dItem->hDC, ((dItem->rcItem.right - dItem->rcItem.left) / 2) + dItem->rcItem.left - (sz.cx / 2), ((dItem->rcItem.bottom - dItem->rcItem.top) / 2) + dItem->rcItem.top - (sz.cy / 2), ETO_OPAQUE | ETO_CLIPPED, &dItem->rcItem, text, len, NULL);

				DrawEdge( dItem->hDC, &dItem->rcItem, (dItem->itemState & ODS_SELECTED ? BDR_SUNKENOUTER : BDR_RAISEDOUTER), BF_RECT);
                return DefWindowProc(hwndDlg, uMsg, wParam, lParam);
break;			
		case WM_CREATE:
		{

			
			//~ DRAWITEMSTRUCT *dis = (LPDRAWITEMSTRUCT)lParam;
			//~ HDC hDC = dis->hDC;
			//~ HWND hwndDlg = dis->hwndItem;
			//~ RECT r;
			//~ GetClientRect(hwndDlg, &r);
			//~ FrameRect(hDC,&r,(HBRUSH)GetStockObject(BLACK_BRUSH));		
		
			// 2. A button with style BS_OWNERDRAW
			// This is what the article is about :)		
		}
		break;
		case WM_COMMAND://
		{
			switch(wParam)
			{
				case IDC_BUTTON1:
					{
						//~ MessageBoxPrintf("hi","%s\n",buff);
					}
					break;
				case IDC_BUTTON2:
					{
						
					}					
					break;
				default:
					break;
			}
			return TRUE;
		}
		break;
	case WM_CLOSE://Massage for terminate/exit (may close button clicked on title bar)
		{
			//Close dialog
		EndDialog(hwndDlg,0);
			break;
		}
	//~ case WM_CTLCOLORDLG: //set its text and background colors using the specified display device context handle.
	case WM_CTLCOLORBTN: 
		{
			hB = CreateSolidBrush(RGB(255,0,0));
			return (LONG)hB;			
		 break;			
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			TRIVERTEX vert[2];
			RECT r;
			GRADIENT_RECT gRect;
			HDC hDC = BeginPaint(hwndDlg,&ps);
			GetClientRect(hwndDlg,&r);
			vert[0].Alpha = 0x0000;
			vert[0].Red = 0xff00;
			vert[0].Green = 0x0000;
			vert[0].Blue = 0x8800;
			vert[0].x = r.left;
			vert[0].y = r.top;
			vert[1].Alpha = 0x0000;
			vert[1].Red = 0xff00;
			vert[1].Green = 0xff00;
			vert[1].Blue = 0xff00;
			vert[1].x = r.right;
			vert[1].y = r.bottom;
			gRect.UpperLeft = 0;
			gRect.LowerRight = 1;
			GradientFill(hDC,vert,2,&gRect,1,GRADIENT_FILL_RECT_H);		
			EndPaint(hwndDlg,&ps);	
		break;
		}

	case WM_CTLCOLORSTATIC: //可以控制静态控件的颜色
		{
			
		break;
		}
	default:
		break;			

	}
	return FALSE;
}