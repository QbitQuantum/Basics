//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
	RECT rect;
	SHORT vkShift=0;
	
	HFONT hfOld;
	long lfHeight;
	int iDevCap;
	LOGFONT logfont = { 0 };
    COLORREF oldTextColor;
	COPYDATASTRUCT* copyData;
	TCHAR* szTemp=new TCHAR(MAX_PATH);

	INITCOMMONCONTROLSEX InitCtrlEx;

	InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCtrlEx.dwICC  = ICC_PROGRESS_CLASS;
	InitCommonControlsEx(&InitCtrlEx);

	HPEN myPen, oldPen;

	switch (message) 
    {
        case WM_CREATE:
			//do font calculation
			hdc=GetWindowDC(hWnd);
			iDevCap=GetDeviceCaps(hdc, LOGPIXELSY);	//pixels per inch
			lfHeight = -((long)fontHeight * (long)iDevCap) / 72L;
			GetObject (GetStockObject (SYSTEM_FONT), sizeof (LOGFONT), (PTSTR) &logfont) ;
			//	HFONT hf = CreateFontIndirect(&logfont);
			logfont.lfHeight=lfHeight;
			hFont=CreateFontIndirect(&logfont);
			ReleaseDC(NULL,hdc);

			DEBUGMSG(1, (L"Create hWnd=%i\r\n", hWnd));
			if(iTimeOut>0)
				startThread(hWnd);

			if(bUseProgress){
				//progressBar
				hProgress = CreateWindowEx(0, PROGRESS_CLASS, NULL,
								WS_CHILD | WS_VISIBLE,
								xProgress, yProgress, xProgressWidth, yProgressHeight,
								hWnd, NULL, g_hInst, NULL);
				SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
				SendMessage(hProgress, PBM_SETPOS, iProgressVal, 0);
			}
			break;
		case WM_COPYDATA:
			copyData=(COPYDATASTRUCT*)lParam;
			myMsg _mymsg;
			if(copyData->dwData==1234)	//that's right
			{
				memcpy(&_mymsg, copyData->lpData, sizeof(myMsg));
			}
			if(_mymsg.iVal==0){		//text message
				if(wcslen(_mymsg.szText)>0)
					wcscpy(szMessageText, _mymsg.szText);
				GetClientRect(hWnd, &rect);
				InvalidateRect(hWnd, &rect, TRUE);
			}
			else if(_mymsg.iVal==1){		//progress message
				if(wcslen(_mymsg.szText)>0)
					wcscpy(szTemp, _mymsg.szText);
				iProgressVal=_wtoi(szTemp);
				SendMessage(hProgress, PBM_SETPOS, iProgressVal, 0);
			}
			break;			
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            
            // TODO: Add any drawing code here...
			GetClientRect(hWnd, &rect);
			//shrink text area if progressbar is there
			if(bUseProgress && hProgress!=NULL){
				rect.bottom-=yProgressHeight;
			}
			//draw rectangle
			myPen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
			oldPen = (HPEN)SelectObject(hdc,myPen);
			SelectObject(hdc, hBackcolor);
			Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
			//shrinkRect(&rect, 1);
			//Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
			//a drop shadow
			rect.right-=1;rect.bottom-=1;
			Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
			rect.right-=1;rect.bottom-=1;
			Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
			SelectObject(hdc, oldPen);

			SetBkMode(hdc, TRANSPARENT);
			oldTextColor = SetTextColor(hdc, RGB(fontColorRed, fontColorGreen, fontColorBlue));
			hfOld=(HFONT)SelectObject(hdc, hFont);
            DrawText(hdc, 
				szMessageText,	//text to draw
				-1,				//length of text
				&rect, 
				dwTextalign | DT_END_ELLIPSIS | DT_EXTERNALLEADING | DT_VCENTER // | DT_SINGLELINE		//text formatting
				);

            EndPaint(hWnd, &ps);
			SelectObject(hdc, hfOld);
			SetTextColor(hdc, oldTextColor);

			//if(hProgress!=NULL)

			DeleteObject(hFont);
            break;
		case WM_LBUTTONDBLCLK:
			vkShift=GetKeyState(VK_CAPITAL);
			if( (vkShift & 0x80) == 0x80 || (vkShift & 0x01) == 0x01 ){
				if(MessageBox(hWnd, L"Exit?", L"showWin", MB_OKCANCEL)==IDOK)
					DestroyWindow(hWnd);
			}
			break;
		case WM_QUIT:
			DEBUGMSG(1, (L"WM_QUIT \r\n"));
			break;
        case WM_DESTROY:
			stopThread();
            PostQuitMessage(0);
            break;


        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
	delete szTemp;
    return 0;
}