void CCherryComboBox::OnMouseLeave()
{
	COMBOBOXINFO comboBoxInfo = { sizeof(COMBOBOXINFO) };
	GetComboBoxInfo(&comboBoxInfo);

	// 버튼이 눌린 상태면
	if (/* comboBoxInfo.stateButton == STATE_SYSTEM_PRESSED || */ !m_bDropDown)
	{
		// Normal
		m_pCurrentImage = &m_images[STATUS_NORMAL];
	}

	if (m_bTracking)
	{
		TRACKMOUSEEVENT trackMouseEvent;
		trackMouseEvent.cbSize = sizeof(TRACKMOUSEEVENT);
		trackMouseEvent.dwFlags = TME_CANCEL;
		trackMouseEvent.hwndTrack = GetSafeHwnd();
		trackMouseEvent.dwHoverTime = 1;
		_TrackMouseEvent(&trackMouseEvent);

		m_bTracking = FALSE;
	}

	m_bHover = FALSE;
	SetCurrentFont(GetNormalFont());

	if (m_bEnableHoverHandCursor)
		SetClassLong(GetSafeHwnd(), GCL_HCURSOR, (LONG)AfxGetApp()->LoadStandardCursor(IDC_ARROW));

	Invalidate(FALSE);

	CComboBox::OnMouseLeave();
}