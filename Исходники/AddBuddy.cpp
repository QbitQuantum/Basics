BOOL AddBuddy(HWND hwndTarget, HWND hwndBuddy, UINT uStyle)
{
	if(uStyle == BDS_LEFT || uStyle == BDS_RIGHT || uStyle == BDS_TOP || uStyle == BDS_BOTTOM)
	{
		if(::IsWindow(hwndTarget) && ::IsWindow(hwndBuddy))
		{
			FARPROC lpfnWndProc = reinterpret_cast<FARPROC>(SetWindowLong(hwndTarget, GWL_WNDPROC, (long)SubClassedProc));
			ASSERT(lpfnWndProc != NULL);
			VERIFY(::SetProp(hwndTarget, g_szOldProc, reinterpret_cast<HANDLE>(lpfnWndProc)));
			
			CData *pData = new CData;
			pData->m_uStyle = uStyle;

			CRect rcBuddy;
			::GetWindowRect(hwndBuddy, rcBuddy);

			pData->m_uBuddyWidth = rcBuddy.Width();
			pData->m_uBuddyHeight = rcBuddy.Height();
			pData->m_hwndBuddy = hwndBuddy;
			pData->m_bVisible = -1;

			VERIFY(::SetProp(hwndTarget, g_szData, reinterpret_cast<HANDLE>(pData)));

			::SetWindowPos(hwndTarget, NULL, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED);
			
			return TRUE;
		}
		else
		{
			SetLastErrorEx(ERROR_INVALID_WINDOW_HANDLE, SLE_ERROR);
		}
	}
	else
	{
		SetLastErrorEx(ERROR_INVALID_DATA, SLE_ERROR);
	}

	return FALSE;
}