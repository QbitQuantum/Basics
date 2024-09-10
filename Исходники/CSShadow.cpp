void CSShadow::Draw()
{
	RECT WinRect;
	GetWindowRect(m_hWnd, &WinRect);

	int nWidth = WinRect.right-WinRect.left;
	int nHeight = WinRect.bottom-WinRect.top;

	HDC hdcScreen = GetDC(NULL); 
	HDC hDC = CreateCompatibleDC(hdcScreen); 
	HBITMAP hBmp = CreateCompatibleBitmap(hdcScreen, nWidth+10, nHeight+10); 
	HBITMAP hBmpOld = (HBITMAP)SelectObject(hDC, hBmp);

	
	DWORD dwColor;
	if (m_bActive)
		dwColor = dwActiveColor;
	else
		dwColor = dwInactiveColor;

	Pen* _Pen = new Pen(dwColor, 1);
	Graphics _Graphics(hDC);

	Rect rect = { 9, 9, nWidth - 19, nHeight - 19 };
	_Graphics.DrawLine(_Pen, 9, 9, nWidth - 10, 9);
	_Graphics.DrawLine(_Pen, 9, nHeight - 10, nWidth - 10, nHeight - 10);

	_Graphics.DrawLine(_Pen, 9, 9, 9, nHeight - 10);
	_Graphics.DrawLine(_Pen, nWidth - 10, 9, nWidth - 10, nHeight - 10);

	_Graphics.ExcludeClip(rect);

	GraphicsPath graphicsPath;
	int diameter = 2 * 2;

	graphicsPath.AddArc(Rect(rect.X, rect.Y, diameter, diameter), 180.0f, 90.0f);
	graphicsPath.AddArc(Rect(rect.X + rect.Width - diameter, rect.Y, diameter, diameter), 270.0f, 90.0f);
	graphicsPath.AddArc(Rect(rect.X + rect.Width - diameter, rect.Y + rect.Height - diameter, diameter, diameter), 0.0f, 90.0f);
	graphicsPath.AddArc(Rect(rect.X, rect.Y + rect.Height - diameter, diameter, diameter), 90.0f, 90.0f);
	graphicsPath.CloseFigure();

	int num_steps = 10;
	float delta = 2;
	float alpha = delta;
	for (int thickness = 10; thickness >= 0; thickness--)
	{
		Color color = Color((int)alpha, (BYTE)(dwColor>>16), (BYTE)(dwColor >> 8), (BYTE)(dwColor));
		Pen *pen = new Pen(color, thickness);

		_Graphics.DrawPath(pen, &graphicsPath);
		
		alpha += delta;
	}
	Pen *pen = new Pen(*new Color(1, 255, 255, 255), 20);
	_Graphics.DrawPath(pen, &graphicsPath);
	//Rect rect2 = { 9, 9, nWidth-19, nHeight-19};
	
	//graphicsPath.AddRectangle(rect2);


	BLENDFUNCTION blend = {0}; 
	blend.BlendOp				= AC_SRC_OVER; 
	blend.SourceConstantAlpha	= 255; 
	blend.AlphaFormat			= AC_SRC_ALPHA; 
	blend.BlendFlags			= 0;

	POINT ptPos = {WinRect.left, WinRect.top}; 
	SIZE sizeWnd = {nWidth, nHeight}; 
	POINT ptSrc = {0, 0}; 

	UpdateLayeredWindow(m_hWnd, hdcScreen, &ptPos, &sizeWnd, hDC, &ptSrc, 0, &blend, ULW_ALPHA); 
	
	SelectObject(hDC, m_OldMemBitmap);
	DeleteObject(m_MemBitmap);
	DeleteObject(hBmp);
	ReleaseDC(m_hWnd, m_MemDC);
	ReleaseDC(m_hWnd, hdcScreen);
	DeleteDC(hDC);
}