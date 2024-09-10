FilteredListBox::FilteredListBox( DWORD dwStyle,int x,int y,int nWidth,int nHeigth,HWND hWndParent,HMENU hMenu,HINSTANCE hInstance )
	:ListBox(dwStyle | LBS_OWNERDRAWVARIABLE | LBS_HASSTRINGS,WS_EX_CLIENTEDGE,x,y,nWidth,nHeigth,hWndParent,hMenu,hInstance)
{
	HDC dc = GetWindowDC();
	GetTextMetrics(dc,&m_TextMetrics);
	ReleaseDC(dc);
}