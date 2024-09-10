int CMenuListBox::ChooseValue()
{
	nTracking=1;
	// do popup menu message loop
	CWnd *pPrev=SetFocus();
	SetCapture();
	while( nTracking>0 )
	{
		WaitMessage();
		MSG msg;
		while( ::PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
		{
			if(msg.message==WM_KEYDOWN&&msg.wParam==VK_ESCAPE)
			{
				nTracking=-1;
			}
			if( ! ::GetMessage( &msg, NULL, 0, 0 ) )
				break;
			::DispatchMessage( &msg );
		}
	}
	ReleaseCapture();
	if(pPrev)
		pPrev->SetFocus();

	if(nTracking<0)
		return -1;
	else
		return GetCurSel();
}