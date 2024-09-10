void ScrollTo(HWND hwnd,struct ClcData *dat,int desty,int noSmooth)
{
	DWORD startTick,nowTick;
	int oldy=dat->yScroll;
	RECT clRect,rcInvalidate;
	int maxy,previousy;

	if(dat->iHotTrack!=-1 && dat->yScroll != desty) {
		InvalidateItem(hwnd,dat,dat->iHotTrack);
		dat->iHotTrack=-1;
		ReleaseCapture();
	}
	GetClientRect(hwnd,&clRect);
	rcInvalidate=clRect;
	//maxy=dat->rowHeight*GetGroupContentsCount(&dat->list,2)-clRect.bottom;
	maxy=RowHeights_GetTotalHeight(dat)-clRect.bottom;
	if(desty>maxy) desty=maxy;
	if(desty<0) desty=0;
	if(abs(desty-dat->yScroll)<4) noSmooth=1;
	if(!noSmooth && dat->exStyle&CLS_EX_NOSMOOTHSCROLLING) noSmooth=1;
	previousy=dat->yScroll;
	if(!noSmooth) {
		startTick=GetTickCount();
		for(;;) {
			nowTick=GetTickCount();
			if(nowTick>=startTick+dat->scrollTime) break;
			dat->yScroll=oldy+(desty-oldy)*(int)(nowTick-startTick)/dat->scrollTime;
			if(/*dat->backgroundBmpUse&CLBF_SCROLL || dat->hBmpBackground==NULL &&*/FALSE)
				ScrollWindowEx(hwnd,0,previousy-dat->yScroll,NULL,NULL,NULL,NULL,SW_INVALIDATE);
			else
      {
        UpdateFrameImage((WPARAM) hwnd, (LPARAM) 0); 
				//InvalidateRectZ(hwnd,NULL,FALSE);
      }
			previousy=dat->yScroll;
		  SetScrollPos(hwnd,SB_VERT,dat->yScroll,TRUE);
      UpdateFrameImage((WPARAM) hwnd, (LPARAM) 0); 
			UpdateWindow(hwnd);
		}
	}
	dat->yScroll=desty;
	if((dat->backgroundBmpUse&CLBF_SCROLL || dat->hBmpBackground==NULL) && FALSE)
		ScrollWindowEx(hwnd,0,previousy-dat->yScroll,NULL,NULL,NULL,NULL,SW_INVALIDATE);
	else
		InvalidateRectZ(hwnd,NULL,FALSE);
	SetScrollPos(hwnd,SB_VERT,dat->yScroll,TRUE);
}