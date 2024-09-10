HL_PRIM void HL_NAME(ui_winlog_set_text)( wref *w, const uchar *txt, bool autoScroll ) {
	HWND text = (HWND)GetProp(w->h,PTEXT);
	DWORD a,b;
	SCROLLINFO sinf;
	POINT pt;
	sinf.cbSize = sizeof(sinf);
	sinf.fMask = SIF_RANGE | SIF_POS | SIF_PAGE;
	GetScrollInfo(text,SB_VERT,&sinf);
	SendMessage(text,EM_GETSCROLLPOS,0,(LPARAM)&pt);
	SendMessage(text,EM_GETSEL,(WPARAM)&a,(LPARAM)&b);
	SetWindowText(text,txt);
	SendMessage(text,EM_SETSEL,a,b);
	if( autoScroll ) {
		if( sinf.nPos + sinf.nPage == sinf.nMax || sinf.nMax == 1 ) {
			GetScrollInfo(text,SB_VERT,&sinf);
			pt.y = sinf.nMax - sinf.nPage;
		}
		SendMessage(text,EM_SETSCROLLPOS,0,(LPARAM)&pt);
	}
}