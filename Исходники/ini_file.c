int clamp_window(RECT *rwin)
{
	HMONITOR hmon;
	hmon=MonitorFromRect(rwin,MONITOR_DEFAULTTONEAREST);
	if(hmon){
		MONITORINFO mi;
		mi.cbSize=sizeof(mi);
		if(GetMonitorInfo(hmon,&mi)){
			int x,y,cx,cy;
			RECT rmon;
			rmon=mi.rcWork;
			x=rwin->left;
			y=rwin->top;
			cx=rwin->right-rwin->left;
			cy=rwin->bottom-rwin->top;
			if(x<rmon.left)
				x=rmon.left;
			if(y<rmon.top)
				y=rmon.top;
			if(cx>(rmon.right-rmon.left))
				cx=rmon.right-rmon.left;
			if(cy>(rmon.bottom-rmon.top))
				cy=rmon.bottom-rmon.top;
			if((x+cx)>rmon.right)
				x=rmon.right-cx;
			if((y+cy)>rmon.bottom)
				y=rmon.bottom-cy;
			rwin->left=x;
			rwin->top=y;
			rwin->right=x+cx;
			rwin->bottom=y+cy;
		}
	}
	return 0;
}