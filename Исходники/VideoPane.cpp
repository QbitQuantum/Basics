void CVideoPane::SetLanguage(int ilang)
{
	int iLangId = GetUserDefaultLangID();
	
	switch (ilang)
	{
	case eLTE_LANG_zh_CN:
		{
			iLangId = 2052;	// 中文
		}
		break;
	case eLTE_LANG_en_US:
		{
			iLangId = 1033;	// 英文
		}
		break;
	case eLTE_LANG_es_ES:
		{
			iLangId = 1034;	// 西班牙
		}
		break;
	default:
		{

		}
		break;
	}
	m_Language.LoadLanguage(iLangId);

	// 刷新提示文本
	if (NULL != m_hWnd)
	{
		m_SnapshotBtn.UpdateToolTip(m_Language.GetString(GET_STRING_PARAM(IDS_SNAPSHOT)));
		m_ReversePlayBtn.UpdateToolTip(m_Language.GetString(GET_STRING_PARAM(IDS_REVERSEPLAY)));
		m_AudioBtn.UpdateToolTip(m_Language.GetString(GET_STRING_PARAM(IDS_UNMUTE)));
		m_FullScreenBtn.UpdateToolTip(m_Language.GetString(GET_STRING_PARAM(IDS_FULLSCREEN)));
		m_CloseBtn.UpdateToolTip(m_Language.GetString(GET_STRING_PARAM(IDS_CLOSEVIDEO)));
		if (m_bHaveSound)
		{
			m_AudioBtn.UpdateToolTip(m_Language.GetString(GET_STRING_PARAM(IDS_MUTE)));
		}
		else
		{
			m_AudioBtn.UpdateToolTip(m_Language.GetString(GET_STRING_PARAM(IDS_UNMUTE)));
		}
	}
}