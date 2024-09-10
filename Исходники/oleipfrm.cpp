BOOL COleIPFrameWnd::PreTranslateMessage(MSG* pMsg)
{
	// check server's accelerators first
	if (CFrameWnd::PreTranslateMessage(pMsg))
		return TRUE;

	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		// always check to see if they exist in the default accel table
		//  (they may exist but not be translated when disabled)
		HACCEL hAccel = GetDefaultAccelerator();
		if (hAccel != NULL && IsAccelerator(hAccel,
			CopyAcceleratorTable(hAccel, NULL, 0), pMsg, NULL))
		{
			return TRUE;
		}

		// check container's accelerators as last chance
		OLEINPLACEFRAMEINFO frameInfo = m_frameInfo;
		if (::OleTranslateAccelerator(m_lpFrame, &frameInfo, pMsg) == S_OK)
			return TRUE;
	}

	return FALSE;   // keystroke not processed.
}