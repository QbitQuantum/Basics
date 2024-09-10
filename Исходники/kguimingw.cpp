void kGUISystemMINGW::SetWindowPos(int x,int y)
{
	WINDOWPLACEMENT    wp;
	int w,h;

    wp.length = sizeof wp;

    if ( GetWindowPlacement(m_hWnd,&wp) )
	{
		w=wp.rcNormalPosition.right-wp.rcNormalPosition.left;
		h=wp.rcNormalPosition.bottom-wp.rcNormalPosition.top;

		/* clip */
		if((x+w)<25)
			x=25-w;
		else if(x>(GetSystemMetrics(SM_CXSCREEN)-25))
			x=GetSystemMetrics(SM_CXSCREEN)-25;
		if(y<0)
			y=0;
		else if(y>(GetSystemMetrics(SM_CYSCREEN)-25))
			y=GetSystemMetrics(SM_CYSCREEN)-25;

		wp.rcNormalPosition.left=x;
		wp.rcNormalPosition.top=y;
		wp.rcNormalPosition.right=x+w;
		wp.rcNormalPosition.bottom=y+h;
		SetWindowPlacement(m_hWnd,&wp);
	}
}