void CDlgFilterPanel::OnBnClickedStartQuery()
{
	// Get CTime from 1st DataTime Control on the dialog
	CTime SelTime;
	this->m_CtrlDataTime.GetTime(SelTime);

	// Get CTime from 2nd DataTime Control on the dialog
	CTime SaleWk1;
	this->m_CtrlDateTime2.GetTime(SaleWk1);

	// Check user select date, must be Monday
	if ( (SelTime.GetDayOfWeek() != 2) || (SaleWk1.GetDayOfWeek() != 2) )
	{
		::MessageBox(NULL,
			"Sorry, you selected date is not Monday.\nPlease try again.",
			"Warning", MB_OK | MB_ICONWARNING);
		return;
	}

	LPMAINWORKTHREADPARAM lpThreadParam = new MAINWORKTHREADPARAM;
	lpThreadParam->_StartingDate = SelTime.GetTime();
	lpThreadParam->_FirstWeekSale = SaleWk1.GetTime();
	CWinThread *pWinThread = AfxBeginThread(
		(AFX_THREADPROC) MainWorkThreadFunc, (LPVOID) lpThreadParam,
		THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	pWinThread->m_bAutoDelete = TRUE;
	pWinThread->ResumeThread();

	OnOK();
}