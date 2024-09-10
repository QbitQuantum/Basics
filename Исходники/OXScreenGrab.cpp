// Protected member functions
BOOL COXScreenGrabber::PrepareWindow(BOOL bClient, CRect& ScrRect, CWnd* pWnd)
{
	if (pWnd == NULL)
		pWnd = CWnd::GetForegroundWindow();
	if (pWnd == NULL)
		pWnd = CWnd::GetDesktopWindow();

	ASSERT(pWnd != NULL);
	if (!pWnd->IsWindowVisible())
		return FALSE;

	if (pWnd == CWnd::GetDesktopWindow())
	{
		// create a DC for the screen and create
		CDC SreenDC;
		if (!SreenDC.CreateDC(_T("DISPLAY"), NULL, NULL, NULL))
			return FALSE;

		// get screen resolution and set Rect
		ScrRect.left = 0;
		ScrRect.top = 0;
		ScrRect.right = SreenDC.GetDeviceCaps(HORZRES);
		ScrRect.bottom = SreenDC.GetDeviceCaps(VERTRES);

		SreenDC.DeleteDC();
	}
	else
	{
		// Move window which was selected to top of Z-order for
		// the capture, and make it redraw itself
		pWnd->SetWindowPos(NULL, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOSIZE | SWP_NOMOVE);
		pWnd->UpdateWindow();

		if (bClient)
		{
			// get the client area dimensions
			pWnd->GetClientRect(&ScrRect);

			// convert client coords to screen coords
			CPoint pt1(ScrRect.left, ScrRect.top); 
			CPoint pt2(ScrRect.right, ScrRect.bottom); 

			pWnd->ClientToScreen(&pt1);
			pWnd->ClientToScreen(&pt2);

			ScrRect.left = pt1.x;
			ScrRect.top = pt1.y;
			ScrRect.right = pt2.x;
			ScrRect.bottom = pt2.y;
		}
		else
			pWnd->GetWindowRect(&ScrRect);
	}

	return TRUE;
}