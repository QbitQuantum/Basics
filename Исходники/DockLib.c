HDWP DockWnd_DeferPanelPos(HDWP hdwp, HWND hwndMain, RECT *rect)
{
	DOCKSERVER *dsp = GetDockServer(hwndMain);
	DOCKPANEL *dpp;

	if(dsp == 0)
		return 0;

	CopyRect(&dsp->DockRect, rect);
	CopyRect(&dsp->ClientRect, rect);

	for(dpp = dsp->PanelListHead; dpp; dpp = dpp->flink)
	{
		RECT rc = *rect;
		RECT rc2;
	                 
		if(dpp->fDocked == FALSE || dpp->fVisible == FALSE)
		{
			continue;
		}

		GetPanelClientSize(dpp, &rc2, TRUE);
		
		if(dpp->dwStyle & DWS_DOCKED_LEFT)
		{
			rc.right = rc.left + RectWidth(&rc2);
		}
		else if(dpp->dwStyle & DWS_DOCKED_RIGHT)
		{
			rc.left = rc.right - RectWidth(&rc2);	
		}
		else if(dpp->dwStyle & DWS_DOCKED_TOP)
		{
			rc.bottom = rc.top + RectHeight(&rc2);
		}
		else if(dpp->dwStyle & DWS_DOCKED_BOTTOM)
		{
			rc.top = rc.bottom - RectHeight(&rc2);
		}

		SubtractRect(rect, rect, &rc);

		hdwp = DeferWindowPos(hdwp, dpp->hwndPanel, 0, rc.left, rc.top, rc.right-rc.left,rc.bottom-rc.top,
			SWP_NOACTIVATE|SWP_NOZORDER|SWP_SHOWWINDOW);
	}

    CopyRect(&dsp->ClientRect, rect);

	return hdwp;
}