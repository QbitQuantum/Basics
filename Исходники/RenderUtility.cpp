void CRenderUtility::UpdateLayerWnd( HWND& hWnd,HDC& hSrcDc,SIZE& size )
{
	if(NULL == hWnd || !::IsWindow(hWnd)) return;

	BLENDFUNCTION blend = { 0 };  
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.AlphaFormat = AC_SRC_ALPHA;
	blend.SourceConstantAlpha = 255;

	POINT ptSrc = { 0 };
	POINT ptDest = { 0 };
	HDC hDstDc = ::GetDC(hWnd);


	RECT rtWindowRect = { 0 };
	::GetWindowRect(hWnd,&rtWindowRect);
	ptDest.x = rtWindowRect.left;
	ptDest.y = rtWindowRect.top;

	//SIZE size = { RECT_WIDTH(rct),RECT_HEIGHT(rct)};
	UpdateLayeredWindow(hWnd,hDstDc,&ptDest,&size,hSrcDc,&ptSrc,NULL,&blend,ULW_ALPHA);
	::DeleteDC(hDstDc);
}