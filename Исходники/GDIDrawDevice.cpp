//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPGDIDrawDevice::SetTargetWindow(HWND wnd, bool is_main)
{
	TVPInitGDIOptions();
	if( wnd ) {
		// 描画用 DC を取得する
		TargetDC = ::GetDC(wnd);
	} else {
		// 描画用 DC を開放する
		if(TargetDC) ::ReleaseDC(TargetWindow, TargetDC), TargetDC = NULL;
	}

	if(DrawDibHandle) ::DrawDibClose(DrawDibHandle), DrawDibHandle = NULL;
	TargetWindow = wnd;
	IsMainWindow = is_main;
	DrawDibHandle = DrawDibOpen();

	CreateBitmap();
}