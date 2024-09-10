void CNotificationWnd::DoTransitionIn(){
	RECT rect;
	GetWindowRect(&rect);
	int src_y=rect.top;
	int dst_y=-30;
	for(int i=0;i<50;i++){
		int y=EaseOut(i, src_y, dst_y+1, 50);
		SetWindowPos(NULL, rect.left, y, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
		CDC scrdc;
	scrdc.Attach(::GetDC(0));
		BLENDFUNCTION func;
	func.BlendOp=AC_SRC_OVER;
	func.AlphaFormat=AC_SRC_ALPHA;
	func.SourceConstantAlpha=EaseOut(i, 0, 255, 50);
	func.BlendFlags=0;
	UpdateLayeredWindow(&scrdc, &CPoint(rect.left, y), &CSize(200, 95), &bdc, &CPoint(0,0), 0, &func, ULW_ALPHA);
	::ReleaseDC(0, scrdc);

		_sleep(10);
	}

	for(int i=0;i<300;i++){
		_sleep(10);
		if(needClose)break;
	}

	while(mouseInside && !needClose){
		_sleep(10);
	}
	if(!this)return;

	for(int i=0;i<50;i++){
		CDC scrdc;
	scrdc.Attach(::GetDC(0));
		BLENDFUNCTION func;
	func.BlendOp=AC_SRC_OVER;
	func.AlphaFormat=AC_SRC_ALPHA;
	func.SourceConstantAlpha=EaseIn(i, 255, -255, 50);
	func.BlendFlags=0;
	UpdateLayeredWindow(&scrdc, &CPoint(rect.left, src_y+dst_y), &CSize(200, 95), &bdc, &CPoint(0,0), 0, &func, ULW_ALPHA);
	::ReleaseDC(0, scrdc);

		_sleep(10);
	}
	SendMessage(WM_CLOSE);
}