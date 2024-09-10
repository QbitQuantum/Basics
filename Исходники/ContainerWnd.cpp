void CContainerWnd::PaintBuffer(HWND hwnd, HDC dc, int width, int height)
{
	PaintBufferPre(hwnd, dc, width, height);
	POINT prevPoint = { 0, 0 };
	int dcState = 0;
	for (auto comp : m_components)
	{
		if(RectVisible(dc, comp))
		{
			dcState = SaveDC(dc);
			SetViewportOrgEx(dc, comp->left, comp->top, &prevPoint);
			comp->Paint(hwnd, dc);
			GdiFlush();
			if(dcState)RestoreDC(dc, dcState);
		}
	}
//	SetViewportOrgEx(dc, 0, 0, &prevPoint);
	PaintBufferPost(hwnd, dc, width, height);
}