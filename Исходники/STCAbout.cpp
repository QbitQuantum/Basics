// ----------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
 HRSRC   hResource;
 HGLOBAL resPoints;
 DWORD   resSize;
 LPVOID  rgnPoints;
 HRGN    hWindowRegion;
 static  CFont fntTitle;
 static  CFont fntDescr;
 static  HWND  hCloseButton = NULL;
 HDC     hdc;
 PAINTSTRUCT pt;
	
 switch (message) 
 {
  case WM_CREATE:		 
   hResource = FindResource(d_about.hInstance,d_about.d_lprgnname,ABOUT_STC_RGN_RESOURCE_TYPE);
   if (NULL==hResource) 
    AfxMessageBox(_T("Can't find resource!"),MB_OK|MB_ICONSTOP);

   resPoints = LoadResource(d_about.hInstance,hResource);
   if (NULL==resPoints)
    AfxMessageBox(_T("Can't load resource!"),MB_OK|MB_ICONSTOP);

   resSize = SizeofResource(d_about.hInstance,hResource);
   if (0==resSize)
    AfxMessageBox(_T("Size of resource = 0 !"),MB_OK|MB_ICONSTOP);

   rgnPoints = LockResource(resPoints);
   hWindowRegion = ExtCreateRegion(NULL,resSize,(RGNDATA*)rgnPoints);
   SetWindowRgn(hWnd,hWindowRegion,TRUE);

   hCloseButton = CreateWindowEx(NULL,_T("button"),_T("close"),
                WS_CHILD | (d_about.showCloseButton ? WS_VISIBLE : 0),
                280,186,45,16,hWnd,(HMENU)IDC_BUTTON_CLOSE,
				d_about.hInstance,NULL);

   if (d_about.modal)
    ::SetFocus(hCloseButton);

   fntDescr.CreateFont(
   12,                        // nHeight
   0,                         // nWidth
   0,                         // nEscapement
   0,                         // nOrientation
   FW_NORMAL,                 // nWeight
   FALSE,                     // bItalic
   FALSE,                     // bUnderline
   0,                         // cStrikeOut
   ANSI_CHARSET,              // nCharSet
   OUT_DEFAULT_PRECIS,        // nOutPrecision
   CLIP_DEFAULT_PRECIS,       // nClipPrecision
   DEFAULT_QUALITY,           // nQuality
   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
   _T("Arial"));

   fntTitle.CreateFont(
   14,                        // nHeight
   0,                         // nWidth
   0,                         // nEscapement
   0,                         // nOrientation
   FW_NORMAL,                 // nWeight
   FALSE,                     // bItalic
   FALSE,                     // bUnderline
   0,                         // cStrikeOut
   ANSI_CHARSET,              // nCharSet
   OUT_DEFAULT_PRECIS,        // nOutPrecision
   CLIP_DEFAULT_PRECIS,       // nClipPrecision
   DEFAULT_QUALITY,           // nQuality
   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
   _T("Arial"));

   SendMessage(hCloseButton,WM_SETFONT,(LPARAM)fntDescr.m_hObject,TRUE);

   if (d_about.autoClose > 0)
     SetTimer(hWnd, AUTOCLOSE_TIMER_ID, d_about.autoClose, NULL);
   break;
  case WM_LBUTTONDOWN:
   SendMessage(hWnd,WM_NCLBUTTONDOWN,HTCAPTION,lParam); 		
   break;
  case WM_COMMAND:
   if (LOWORD(wParam)==IDC_BUTTON_CLOSE)
    DestroyWindow(hWnd);
   break;
  case WM_DESTROY:
   fntTitle.DeleteObject();
   fntDescr.DeleteObject();
   //we again ready for create a new instance!
   is_instance = false;
   break;
  case WM_KILLFOCUS:
   if (d_about.modal) 
    if ((HWND)wParam!=hCloseButton)
     SetFocus(hWnd);
   break;
  case WM_PAINT:
   hdc = BeginPaint(hWnd,&pt);
   SetBkColor(hdc,RGB(0,0,0));
   //draw title
   SetTextColor(hdc,RGB(40,250,50));
   SelectObject(hdc,fntTitle.m_hObject);
   TextOut(hdc,195,16,d_about.about_product,_tcslen(d_about.about_product));
   //draw description
   SelectObject(hdc,fntDescr.m_hObject);
   SetTextColor(hdc,RGB(250,240,250));
   SetBkMode(hdc, TRANSPARENT);
   DrawText(hdc,d_about.about_description,-1,CRect(203,45,433,170),DT_EDITCONTROL |DT_WORD_ELLIPSIS);

   EndPaint(hWnd,&pt); 
   break;
  case WM_TIMER:
   ASSERT(KillTimer(hWnd, AUTOCLOSE_TIMER_ID));
   DestroyWindow(hWnd);
   break;
  default:
   return DefWindowProc(hWnd, message, wParam, lParam);
 }
 return 0;
}