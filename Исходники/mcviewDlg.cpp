void CMcviewDlg::OnLoop() 
{
	// test code for bug-2003-7-19
	// TerminateProcess(GetCurrentProcess(), 0);
	// no use, not caused by this
	
	theView.SetFocus();		
	CWnd *pWndLoop = GetDlgItem(IDC_LOOP);

	if(m_bShowLoop){
		m_bShowLoop = false;
		KillTimer(2);
		pWndLoop->SetWindowText("循环");
		return;
	}

	CDlgLoop dlgLoop;
	dlgLoop.m_interval = m_loopInterval;

	if(dlgLoop.DoModal() != IDOK){
		return;
	}
	
	m_loopCurrent = 0;
	m_loopCount = 0;

	CString sLoopFile = ((CMcviewApp*)::AfxGetApp())->m_path+"loops";
	FILE *pLoops = fopen((LPCTSTR)sLoopFile, "r");
	ASSERT(pLoops != NULL);
	CString sItem;
	char buf[1024];
	while(fgets(buf, 1024, pLoops)){
		sItem = buf;
		sItem.Remove(10);
		sItem.Remove(13);
		m_viewLoop[m_loopCount] = sItem + ".gdf";
		m_loopCount++;
		if(m_loopCount >= 32){
			break;
		}
	}
	fclose(pLoops);

	if(m_loopCount < 2){
		return;
	}
	m_loopInterval = dlgLoop.m_interval;

	m_bShowLoop = true;
	SetTimer(2, m_loopInterval * 1000, NULL);
	pWndLoop->SetWindowText("停止");

	theView.LoadFile(m_viewLoop[m_loopCurrent]);
	m_loopCurrent++;
	if(m_loopCurrent >= m_loopCount){
		m_loopCurrent = 0;
	}
}