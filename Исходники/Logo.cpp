void CLogo::OnMouseMove(UINT nFlags, CPoint point) 
{	
	CBitmapButton::OnMouseMove(nFlags, point);

	TRACKMOUSEEVENT TrackMouseEventStructure;
	ZeroMemory(&TrackMouseEventStructure,sizeof(TrackMouseEventStructure));
	TrackMouseEventStructure.cbSize = sizeof(TrackMouseEventStructure);
	TrackMouseEventStructure.hwndTrack = m_hWnd;
	TrackMouseEventStructure.dwFlags = TME_LEAVE;
	TrackMouseEventStructure.dwHoverTime = HOVER_DEFAULT;

	_TrackMouseEvent(&TrackMouseEventStructure);

	if ((nFlags & MK_LBUTTON)!=0 ||
		(nFlags & MK_RBUTTON)!=0) 
	  return;
	
	CString MessageLine;
	if(MessageLine.LoadString(GetDlgCtrlID()))
	{
		int nDelPos = MessageLine.Find(_T('\n'));
		if(nDelPos != -1)
			MessageLine = MessageLine.Left(nDelPos);
	}

	CWnd*  pMainWnd = ::AfxGetMainWnd();
	if(pMainWnd)
		pMainWnd->SendMessage(WM_SETMESSAGESTRING,0,LPARAM(LPCTSTR(MessageLine)));
}