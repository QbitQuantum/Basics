LRESULT CDebugView::OnCaptrueTreeOpened(){


	OPENFILENAME ofn ;

	ofn.lStructSize 				= sizeof (OPENFILENAME) ;
	ofn.hwndOwner					= NULL ;
	ofn.hInstance					= NULL ;
	ofn.lpstrFilter 				= _T("bmp");
	ofn.lpstrCustomFilter	= NULL ;
	ofn.nMaxCustFilter		= 0 ;
	ofn.nFilterIndex		= 0 ;
	ofn.nMaxFile				= MAX_PATH ;
	ofn.nMaxFileTitle			= MAX_PATH ;
	ofn.lpstrInitialDir 		= NULL ;
	ofn.lpstrTitle				= NULL ;
	ofn.nFileOffset 			= 0 ;
	ofn.nFileExtension			= 0 ;
	ofn.lpstrDefExt 			= 0;
	ofn.lCustData				= 0L ;
	ofn.lpfnHook				= NULL ;
	ofn.lpTemplateName			= NULL ;

	TCHAR   szFileName[MAX_PATH], szFileTitle[MAX_PATH];
	*szFileTitle = 0;
	*szFileName  = 0;

	//strcpy(szFileName,".bmp");
	ofn.hwndOwner               = GetGUI()->GetHwnd();
	ofn.lpstrFile         		= szFileName ;
	ofn.lpstrFileTitle    		= szFileTitle ;
	ofn.Flags             		= OFN_OVERWRITEPROMPT ;

	if(!::GetSaveFileName (&ofn)){
		int ret = ::GetLastError();
		return 0;
	}
	tstring FileName = szFileName;
	FileName+=_T(".bmp");

	OpenAllTree();
	Layout(FALSE);

	RECT rcOld;
	::GetClientRect(GetHwnd(),&rcOld);

	::SetWindowPos(GetHwnd(),HWND_TOP,0,0,m_SizeX,m_SizeY,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	RECT rc;
	::GetClientRect(GetHwnd(),&rc);


	HDC hDC = ::GetDC(GetHwnd());
	HBITMAP hBmpCapture = CreateCompatibleBitmap(hDC,m_SizeX,m_SizeY); 

	HDC DCMem = ::CreateCompatibleDC(hDC);

	HBITMAP OldBitmap = (HBITMAP)::SelectObject(DCMem, hBmpCapture);


	if(m_State & SPACE_SHOWBKG){
		FillRect(DCMem,rc,m_crViewBkg);
	}

	UINT	OldMode	= ::SetBkMode(DCMem,TRANSPARENT);

	Draw(DCMem);

	if(m_UseSystemScrollbar == false){
		DrawScrollbar(DCMem);
	};
	::SetBkMode(DCMem, OldMode );


	if(m_State & SPACE_SHOWWINBORDER){
		DrawEdge(DCMem,rc,m_crWinBorder);
	}


	::SelectObject(DCMem, OldBitmap);
	DeleteObject(DCMem);
	::ReleaseDC(GetHwnd(),hDC);


	::SetWindowPos(GetHwnd(),HWND_TOP,0,0,rcOld.right-rcOld.left,rcOld.bottom-rcOld.top,SWP_NOZORDER|SWP_NOMOVE);

	SaveBitmapToFile(hBmpCapture,FileName.c_str());
	DeleteObject(hBmpCapture);
	return 0;
}