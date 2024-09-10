BOOL CSchedule_HTSPage::OnApply()
{
	SYSTEMTIME time;
	m_wndTime.GetTime (&time);

	if (IsDlgButtonChecked (IDC_ONCE) == BST_CHECKED)
	{
		SYSTEMTIME date;
		m_wndDate.GetTime (&date);

		date.wHour   = time.wHour;
		date.wMinute = time.wMinute;
		date.wSecond = time.wSecond;

		SystemTimeToFileTime (&date, &m_task->hts.next);
		m_task->hts.enType = HTS_ONCE;
	}
	else if (IsDlgButtonChecked (IDC_DAILY) == BST_CHECKED)
	{
		UINT nIDs [] = {IDC_SUN, IDC_MON, IDC_TUE, IDC_WED, IDC_THU, IDC_FRI, IDC_SAT};
		BOOL bOk = FALSE;
		for (int i = 0; i < 7; i++)
		{
			m_task->hts.aWeeklyDays [i] = IsDlgButtonChecked (nIDs [i]) == BST_CHECKED;
			bOk = bOk || m_task->hts.aWeeklyDays [i];
		}
		if (bOk == FALSE)
		{
			
			MessageBox (LS (L_ENTERDAYS), LS (L_INPERR), MB_ICONEXCLAMATION);
			return FALSE;
		}
		m_task->hts.enType = HTS_DAILY;
		SystemTimeToFileTime (&time, &m_task->hts.next);
		
	}
	else if (IsDlgButtonChecked (IDC_ONEVERY) == BST_CHECKED)
	{
		UINT u = GetDlgItemInt (IDC_EVERY);
		if (u == 0)
		{
			CString str; str.Format (LS (L_ENTERGREATER), 0);
			MessageBox (str, LS (L_ERR), MB_ICONEXCLAMATION);
			return FALSE;
		}

		int i = m_wndEveryDim.GetCurSel ();
		int mul [] = {1, 60, 60*24};	
		u *= mul [i];
		m_task->hts.interval = u;
		m_task->hts.enType = HTS_CONTINUOUSLY;
		SystemTimeToFileTime (&time, &m_task->hts.next);
	}
	else
	{
		m_task->hts.enType = (fsWhenToStartType) (HTS_WHENISTART + m_wndEvent.GetCurSel ());
		if (m_task->hts.enType == HTS_WHENSPEEDLOW)
		{
			m_task->hts.speedLow.uTimeInterval = GetDlgItemInt (IDC_DURING);
			m_task->hts.speedLow.uLowSpeed = GetDlgItemInt (IDC_LOWSPEED);
		}
		else if (m_task->hts.enType == HTS_NOTHINGRECEIVED || m_task->hts.enType == HTS_WHENDONE)
		{
			m_task->hts.uTimeNothingReceived = GetDlgItemInt (IDC_DURING);
		}
	}
	
	return CPropertyPage::OnApply();
}