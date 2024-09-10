void fsClipboardCatchMgr::Enable(BOOL bEnable)
{
	

	if (bEnable)
	{
		if (m_bEnabled == FALSE)
		{
			m_hNextViewer = SetClipboardViewer ();
			m_bEnabled = TRUE;
		}
	}
	else
	{
		if (m_bEnabled)
		{
			ChangeClipboardChain (m_hNextViewer);
			m_bEnabled = FALSE;
		}
	}
}