HDC CMouseTracker::GetDC()
{
	HDC hDC=GetDCEx(m_hWnd, NULL, DCX_PARENTCLIP|DCX_LOCKWINDOWUPDATE);
	POINT pt=GetScrollOffset();
	SetWindowOrgEx(hDC, pt.x, pt.y, NULL);
	return hDC;
}