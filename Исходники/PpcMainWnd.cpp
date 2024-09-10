void CPpcMainWnd::UnregisterHotKeys()
{
	if (!m_fHotKey)
		return;

	int i, j;
	if (m_fHold) {
		for (i = 0; i < sizeof(s_uHoldKeys) / sizeof(UINT) / 2; i++)
			UnregisterHotKey(m_hWnd, s_uHoldKeys[i][0]);

		CPpcOptions* pOptions = (CPpcOptions*)m_pOptions;
		for (i = 0; i < pOptions->m_listKeyMap.GetCount(); i++) {
			BOOL fHold = FALSE;
			ACCEL* p = (ACCEL*)pOptions->m_listKeyMap.GetAt(i);
			for (j = 0; j < sizeof(s_uHoldKeys) / sizeof(UINT) / 2; j++) {
				if (s_uHoldKeys[j][0] == p->key) {
					fHold = TRUE;
					break;
				}
			}

			if (!fHold) UnregisterHotKey(m_hWnd, p->key);
		}
	}
	else {
		CPpcOptions* pOptions = (CPpcOptions*)m_pOptions;
		for (i = 0; i < pOptions->m_listKeyMap.GetCount(); i++) {
			ACCEL* p = (ACCEL*)pOptions->m_listKeyMap.GetAt(i);
			UnregisterHotKey(m_hWnd, p->key);
		}
	}
	m_fHotKey = FALSE;
}