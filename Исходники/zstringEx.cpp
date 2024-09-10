void zstringEx::showCtl(int CtlID,BOOL isshow,HWND ParentWindowHwnd)
{
	HWND oh;					
	if(ParentWindowHwnd==NULL)
		{
		CWnd *w=::AfxGetMainWnd();
		oh=w->m_hWnd;
		}
	else oh=ParentWindowHwnd;

	CButton b;	
	b.Attach(GetDlgItem(oh,CtlID));
	if(isshow)b.ShowWindow(SW_SHOW);else b.ShowWindow(SW_HIDE);
    b.Detach();
}