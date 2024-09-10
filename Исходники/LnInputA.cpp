void CLcInputA::OnReset()
{
	// 키보드는 전부 0
	SetKeyboardState(m_KeyCur);
	
	memset(m_KeyCur, 0, sizeof m_KeyCur);
	memset(m_KeyOld, 0, sizeof m_KeyOld);
	memset(m_KeyMap, 0, sizeof m_KeyMap);
	
	memset(m_BtnCur, 0, sizeof m_BtnCur);
	memset(m_BtnOld, 0, sizeof m_BtnOld);
	memset(m_BtnMap, 0, sizeof m_BtnMap);

	// 마우스는 현재 위치 유지
	m_fWheel = 0;

	POINT	pt;

	::GetCursorPos(&pt);
	::ScreenToClient( m_hWnd, &pt);

	m_vMsCur[0] = FLOAT(pt.x);
	m_vMsCur[1] = FLOAT(pt.y);
	m_vMsCur[2] = 0.f;

	memcpy(m_vMsOld, m_vMsCur, sizeof m_vMsCur);
	memset(m_vDelta,        0, sizeof m_vDelta);
}