void CEvolverDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == m_NotifyTimer)
	{
		if(m_Counter == 0)
		{
			// Show changelog
			CFrameMain* pFrame = (CFrameMain*) AfxGetApp()->GetMainWnd();
			pFrame->OpenBrowser("http://www.gnucleus.com/update2/ChangeLog.txt");
		}

		m_Counter++;
		m_progBar.SetPos(m_Counter);
		m_stcProgress.SetWindowText("Evolution in " + DWrdtoStr((150 - m_Counter) / 10) + " seconds...");
	
		if(m_Counter == 150)
			StartDownload();
	}

	if(nIDEvent == m_UpgradeTimer)
	{
		// Get File IDs
		std::vector<int> FileIDs;

		VARIANT var = m_autUpdate->GetFileIDs();
		SAFEARRAY* psa = var.parray;

		int* nArray;
		SafeArrayAccessData(psa, reinterpret_cast<void**> (&nArray));

		for(int i = 0; i < psa->rgsabound->cElements; i++)
			FileIDs.push_back(nArray[i]);

		SafeArrayUnaccessData(psa);
		VariantClear(&var);

		// Update status
		if(m_autUpdate->GetTotalCompleted())
			m_stcProgress.SetWindowText("Downloading Files...");

		if(m_autUpdate->GetTotalSize())
			m_progBar.SetPos(m_autUpdate->GetTotalCompleted() * 100 / m_autUpdate->GetTotalSize());
	}

	if(nIDEvent == m_CloseTimer)
	{
		m_Counter++;
		m_progBar.SetPos(m_Counter);
		m_stcProgress.SetWindowText("Restarting in " + DWrdtoStr((150 - m_Counter) / 10) + " seconds...");
	
		if(m_Counter == 150)
		{
			Restart();
			return;
		}
	}

	CDialog::OnTimer(nIDEvent);
}