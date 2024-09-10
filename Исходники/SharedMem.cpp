BOOL CSharedMemQueue::InitailizeMMF(DWORD dwOffsetsize, int maxcount, LPCTSTR lpname, BOOL bCreate )
{
	if( maxcount < 1 )
		return FALSE;
	DWORD dwfullsize = dwOffsetsize * maxcount + sizeof(_SMQ_HEADER);

	m_nMaxCount = maxcount;
	m_wOffset = dwOffsetsize;

	if( bCreate )
		m_hMMFile = CreateFileMapping( (HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, dwfullsize, lpname );
	else
		m_hMMFile = OpenFileMapping( FILE_MAP_ALL_ACCESS, TRUE, lpname );
	
	if( m_hMMFile == NULL )
		return FALSE;

    m_lpMMFile = (char *)MapViewOfFile(m_hMMFile, FILE_MAP_WRITE, 0, 0, 0);
	if( !m_lpMMFile )
		return FALSE;

	m_bMMFCreate = bCreate;
	m_pHeader = (_SMQ_HEADER *)m_lpMMFile;
	m_lReference = (LONG)(m_lpMMFile + sizeof(_SMQ_HEADER));		// 초기 위치 셋팅

	if( bCreate ) {
		memset( m_lpMMFile, 0x00, dwfullsize );
		m_pHeader->Rear = m_pHeader->Front = 0;
		m_pHeader->nCount = 0;
		m_pHeader->RearMode = m_pHeader->FrontMode = E;
		m_pHeader->CreatePid = _getpid();
	}

	return TRUE;
}