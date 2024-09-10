eUpdateResult NotificationIcon::UpdateIcon(NID_INTERNAL & p_nid)
{
	bool newIcon = (m_hWnd == NULL);
	bool wasVisible = IsVisible();
	m_hWnd = p_nid.hWnd;
	m_uID = p_nid.uID;
	if (p_nid.uFlags & NIF_MESSAGE)
	{
		m_uCallbackMessage = p_nid.uCallbackMessage;
	}

	bool useSharedIcon = false;
	if (p_nid.uFlags & NIF_STATE)
	{
		if (p_nid.dwStateMask & NIS_SHAREDICON)
		{
			if (p_nid.dwState & NIS_SHAREDICON)
			{
				useSharedIcon = true;
			}
		}
		if (p_nid.dwStateMask & NIS_HIDDEN)
		{
			if (p_nid.dwState & NIS_HIDDEN)
			{
				m_hidden = true;
			}
			else
			{
				m_hidden = false;
			}
		}
	}
	if (p_nid.uFlags & NIF_ICON)
	{
		if (m_sharedIcon)
		{
			m_sharedIcon->ShareIcon(this, false);
			m_sharedIcon = NULL;
		}
		if (useSharedIcon)
		{
			m_sharedIcon = m_handler->FindIconToShare(p_nid.hIcon);
			if (m_sharedIcon)
			{
				m_hIconOrig = p_nid.hIcon;
				m_hIcon = m_sharedIcon->m_hIcon;
				m_sharedIcon->ShareIcon(this, true);
			}
			else
			{
				m_hIcon = NULL;
				m_hIconOrig = NULL;
				return ICON_FAILURE;
			}
		}
		else
		{
			m_hIconOrig = p_nid.hIcon;
			if (m_hIcon)
			{
				DestroyIcon(m_hIcon);
			}
			m_hIcon = CopyIcon(p_nid.hIcon);
		}
	}

	if (p_nid.uFlags & NIF_TIP)
	{
		StripAmp(m_szTip, p_nid.szTip);
		m_showTip = true;
	}
	if (p_nid.uFlags & NIF_INFO)
	{
		wcscpy(m_szInfo, p_nid.szInfo);
		wcscpy(m_szInfoTitle, p_nid.szInfoTitle);
		m_uTimeout = p_nid.uTimeout;
		m_dwInfoFlags = p_nid.dwInfoFlags;
		if (m_hBalloonIcon)
		{
			DestroyIcon(m_hBalloonIcon);
			m_hBalloonIcon = NULL;
		}
		if (p_nid.hBalloonIcon)
		{
			m_hBalloonIcon = CopyIcon(p_nid.hBalloonIcon);
		}
	}
	else
	{
		ZeroMemory(&m_szInfo, sizeof(m_szInfo));
		ZeroMemory(&m_szInfoTitle, sizeof(m_szInfoTitle));
		m_uTimeout = 0;
		m_dwInfoFlags = 0;
		if (m_hBalloonIcon)
		{
			DestroyIcon(m_hBalloonIcon);
			m_hBalloonIcon = NULL;
		}
	}
	if (p_nid.uFlags & NIF_GUID)
	{
		m_guidItem = p_nid.guidItem;
	}
	if (p_nid.uFlags & NIF_SHOWTIP)
	{
		m_showTip = true;
	}
	else
	{
		if (m_uVersion == 4)
		{
			m_showTip = false;
		}
	}
	if (m_legacyData)
	{
		m_legacyData->updateLegacy(this);
	}
	bool nowVisible = IsVisible();
	return static_cast<eUpdateResult>((newIcon ? ICON_ADDED : ICON_MODIFIED) | (wasVisible ? (nowVisible?0:ICON_HIDE) : (nowVisible?ICON_SHOW:0)));
}