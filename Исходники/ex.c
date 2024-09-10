LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	POINT ar[]={25,10,125,10,140,30,10,30,25,10};
	HBRUSH BrR, BrB, BrY, OldBr;
	RECT rect;

	switch(iMessage) {
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		BrR=CreateSolidBrush(RGB(255,0,0));
		BrB=CreateSolidBrush(RGB(0,0,255));
		BrY=CreateSolidBrush(RGB(255,255,0));

		SetMapMode(hdc,MM_ANISOTROPIC);
		SetWindowExtEx(hdc,160,100,NULL);
		GetClientRect(hWnd, &rect);
		SetViewportExtEx(hdc,rect.right,rect.bottom,NULL);

		OldBr=(HBRUSH)SelectObject(hdc,BrR);
		Rectangle(hdc,20,30,130,90);
		SelectObject(hdc,BrB);
		Polygon(hdc,ar,5);

		SelectObject(hdc,BrY);
		Rectangle(hdc,30,40,60,70);
		Rectangle(hdc,90,40,120,70);
		Ellipse(hdc,135,5,155,25);

		SelectObject(hdc,OldBr);
		DeleteObject(BrR);
		DeleteObject(BrB);
		DeleteObject(BrY);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}