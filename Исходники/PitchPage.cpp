void CPitchPage::OnTimer(UINT nIDEvent) 
{
	if (m_bIsNeedPressButton == true)
	{
		m_csResult += "Missed Note\r\n";
		UpdateData(FALSE);
		m_bIsNeedPressButton = false;

		DWORD dwLines = m_editResult.GetLineCount();
		m_editResult.LineScroll(dwLines);

	}

	if (!UpdateData(TRUE))
	{
		KillTimer(0);
		return;
	}

	DWORD dwRand = rand() * m_nSliderProbability / RAND_MAX;

	DWORD dwNote = dwRand == 0 ? GetComboPitch() : CNoteUtils::GetRandomNote(m_nComboPitchMin, m_nComboPitchMax);

	if (m_vNotes.size() > 0)
		CNoteUtils::MidiNoteOff(m_vNotes.back());
	CNoteUtils::MidiNoteOn(dwNote);
	m_vNotes.push_back(dwNote);
	if (abs((long)(dwNote - GetComboPitch())) % 12 == 0)
		m_bIsNeedPressButton = true;
	
	CWnd *pWndPress = GetDlgItem(IDC_BUTTON_PITCH_PRESS_IF_MATCHED);
	if (pWndPress->IsWindowEnabled() == 0)
		pWndPress->EnableWindow(TRUE);

	pWndPress->SetFocus();

	CString csTempo;
	GetDlgItemText(IDC_EDIT_PITCH_TEMPO, csTempo);
	DWORD dwTempo = atoi((LPCTSTR)csTempo);
	DWORD dwElapse = 1000*60/dwTempo;
	KillTimer(0);
	SetTimer(0, dwElapse, NULL);

	CPropertyPage::OnTimer(nIDEvent);
}