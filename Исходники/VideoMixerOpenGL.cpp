HRESULT CVideoMixerOpenGL::Open(HWND hWndParent, DWORD dwNotifyID, DWORD dwMixerType, RECT *prPort)
{
	if(m_bOpen)
		return E_FAIL;

	memset(m_contextArrary,0,  sizeof(m_contextArrary));

	//Use m_hWndParent>prPort>(64,64)
	m_hWndParent = hWndParent;
	memset(&m_rViewPort, 0,sizeof(m_rViewPort));
	if(m_hWndParent)
	{
		::GetClientRect(m_hWndParent,&m_rViewPort);

		POINT p={0,0};
		::ClientToScreen(m_hWndParent , &p);
		OffsetRect(&m_rViewPort,p.x,p.y);
	}
	else if(prPort)
	{
		m_rViewPort = *prPort;
	}
	else
	{
		SetRect(&m_rViewPort , 0,0,64,64);
	}

	
	//Init dmcp
	m_pDMCP = FindDmcpDisplay();
	if(m_pDMCP != 0)
	{
		DMCP_DisplayOpenParams dmcp_params;
		ZeroMemory(&dmcp_params,sizeof(dmcp_params));
		dmcp_params.pInfoFunc = NULL;
		dmcp_params.pInfoFuncCtxt = NULL;
		HRESULT res = m_pDMCP->Open(&dmcp_params,sizeof(dmcp_params));
		if(FAILED(res))
		{
			DP("[GFXPRESENT]DMCP Open failed \n");
			m_pDMCP->Release();
			m_pDMCP = NULL;
			m_bCanDisp = true;
		}
		else
		{
			DMCP_DisplayState WrStatus;
			ZeroMemory(&WrStatus,sizeof(WrStatus));
			WrStatus.dwSize = sizeof(WrStatus);
			WrStatus.dwCPFlag = DMCP_CPFLAG_ACP | DMCP_CPFLAG_CGMSA | DMCP_CPFLAG_HDCP;
			WrStatus.dwACP = m_DMCP_ACP_flag;
			WrStatus.dwCGMSA= m_DMCP_CGMS_flag;
			WrStatus.dwHDCP= m_DMCP_HDCP_flag;
			
			res = m_pDMCP->SetDisplayState(&WrStatus);
			if(FAILED(res))
				DP("[GFXPRESENT]DMCP Set failed : res:%d __ %d \n",res, WrStatus.dwErrorCPFlag);

			/*SetDestination*/			
			HRESULT hr = m_pDMCP->SetTargetRect(&m_rViewPort);
			if(FAILED(hr))
				DP("[GFXPRESENT] SetTargetRect failed :0x%x \n",hr);
			m_bCanDisp= m_pDMCP->CanDisplay(FALSE);
	
		}

	}
	else
	{
		m_bCanDisp = true;
		DP("[GFXPRESENT_INFO]  DMCP isn't found \n");
	}

	m_bShow = FALSE;

	m_hThread = ::CreateThread(NULL, 0, glutThreadProc, this, 0, NULL);
	SetThreadPriority(m_hThread,THREAD_PRIORITY_HIGHEST);

	m_dwNotifyID = dwNotifyID;

	m_bOpen = true;
	return S_OK;
}