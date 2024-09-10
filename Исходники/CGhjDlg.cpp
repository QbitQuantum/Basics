/// <summary>
/// Called when [bn execute_ clicked].
/// </summary>
void CGhjDlg::OnBnExecute_Clicked()
{
	DWORD textLength = m_tbWorkSpace.GetWindowTextLengthW();
	if(textLength==0)
	{ 
		AfxMessageBox(L"Please enter workspace path", MB_OK);
		return;
	}

	textLength = m_tbFileR.GetWindowTextLengthW();
	if(textLength==0)
	{ 
		AfxMessageBox(L"Please enter path for R relation", MB_OK);
		return;
	}

	textLength = m_tbKeyPosR.GetWindowTextLengthW();
	if(textLength==0)
	{ 
		AfxMessageBox(L"Please enter key attribute for R relation", MB_OK);
		return;
	}

	textLength =  m_tbFileS.GetWindowTextLengthW();
	if(textLength==0)
	{ 
		AfxMessageBox(L"Please enter path for S relation", MB_OK);
		return;
	}

	textLength = m_tbKeyPosS.GetWindowTextLengthW(); 
	if(textLength==0)
	{ 
		AfxMessageBox(L"Please enter key attribute for S relation", MB_OK);
		return;
	}

	textLength =  m_tbPoolSize.GetWindowTextLengthW();
	if(textLength==0)
	{ 
		AfxMessageBox(L"Please enter buffer pool size", MB_OK);
		return;
	}

	GHJ_PARAMS ghjParams;
	m_tbWorkSpace.GetWindowTextW(ghjParams.WORK_SPACE_PATH, MAX_PATH);

	UINT poolSize = GetDlgItemInt(IDC_TB_GHJ_BUFFER_POOL_SIZE, FALSE, FALSE);
	ghjParams.BUFFER_POOL_SIZE = poolSize * SSD_PAGE_SIZE * 256;

	m_tbFileR.GetWindowTextW(ghjParams.RELATION_R_PATH, MAX_PATH);
	_wsplitpath(ghjParams.RELATION_R_PATH, NULL, NULL, ghjParams.RELATION_R_NO_EXT, NULL); 
	ghjParams.R_KEY_POS = GetDlgItemInt(IDC_TB_GHJ_KEY_POS_1, FALSE, FALSE);

	m_tbFileS.GetWindowTextW(ghjParams.RELATION_S_PATH, MAX_PATH);
	_wsplitpath( ghjParams.RELATION_S_PATH, NULL, NULL, ghjParams.RELATION_S_NO_EXT, NULL);
	ghjParams.S_KEY_POS = GetDlgItemInt(IDC_TB_GHJ_KEY_POS_2, FALSE, FALSE);

	INT selectedIndex =-1;
	selectedIndex = m_cbbReadBufferSize.GetCurSel();

	for(UINT i = 0; i < g_ComboBoxBufferItems.size(); i++)
	{
		if(selectedIndex==i)
		{
			ghjParams.READ_BUFFER_SIZE = g_ComboBoxBufferItems[i]->Value;
			break;
		} 
	}

	selectedIndex = m_cbbWriteBufferSize.GetCurSel();

	for(UINT i = 0; i < g_ComboBoxBufferItems.size(); i++)
	{
		if(selectedIndex==i)
		{
			ghjParams.WRITE_BUFFER_SIZE = g_ComboBoxBufferItems[i]->Value;
			break;
		} 
	}

	ghjParams.FUDGE_FACTOR = 1.2;  
	ghjParams.BUCKET_SIZE = 4096 * 64; // 256 KB
	 

	m_btExecute.EnableWindow(FALSE);

	ThreadParams *myParams = new ThreadParams;
	myParams->_this = this;
	myParams->ghjParams = ghjParams;

	m_hGhjThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RunEx, myParams, CREATE_SUSPENDED, NULL); 
	SetThreadPriority(m_hGhjThread, THREAD_PRIORITY_NORMAL);
	m_Requestor.RequestNotification(m_hGhjThread, this, OP_GHJ);
	ResumeThread(m_hGhjThread); 
}