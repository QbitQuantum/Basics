void mxTab_resizeChild (HWND hwnd)
{
	TC_ITEM ti;

	int index = TabCtrl_GetCurSel (hwnd);
	if (index >= 0)
	{
		ti.mask = TCIF_PARAM;
		TabCtrl_GetItem (hwnd, index, &ti);
		mxWidget *widget = (mxWidget *) ti.lParam;
		if (widget)
		{
			RECT rc, rc2;

			GetWindowRect (hwnd, &rc);
			ScreenToClient (GetParent (hwnd), (LPPOINT) &rc.left);
			ScreenToClient (GetParent (hwnd), (LPPOINT) &rc.right);

			TabCtrl_GetItemRect (hwnd, index, &rc2);

			int ex = GetSystemMetrics (SM_CXEDGE);
			int ey = GetSystemMetrics (SM_CYEDGE);
			rc.top += (rc2.bottom - rc2.top) + 3 * ey;
			rc.left += 2 * ex;
			rc.right -= 2 * ex;
			rc.bottom -= 2 * ey;
			HDWP hdwp = BeginDeferWindowPos (2);
			DeferWindowPos (hdwp, hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
			DeferWindowPos (hdwp, (HWND) widget->getHandle (), HWND_TOP, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW);
			EndDeferWindowPos (hdwp);
		}
	}
}