// =========   private helper functions
// ------------------------------------------
HENHMETAFILE COXMetaFile::LoadFile(LPVOID lpvData)
{	
	unsigned long lSize;
	ALDUSHEADER* pAldusMF;
    LPENHMETAHEADER pemh =(LPENHMETAHEADER) lpvData;
	ENHMETAHEADER EnhMetaHeader;

	if(m_hEMF)
	{
		DeleteEnhMetaFile(m_hEMF);
		m_hEMF=NULL;
	}

	// get size, if it makes sense
	// Obtain a handle to a reference device context  
	HDC hdcRef=::GetDC(NULL);  
	// Determine the picture frame dimensions. 
	// iWidthMM is the display width in millimeters. 
	// iHeightMM is the display height in millimeters. 
	// iWidthPels is the display width in pixels. 
	// iHeightPels is the display height in pixels  
	int iWidthMM=GetDeviceCaps(hdcRef,HORZSIZE); 
	int iHeightMM=GetDeviceCaps(hdcRef,VERTSIZE); 
	int iWidthPels=GetDeviceCaps(hdcRef,HORZRES); 
	int iHeightPels=GetDeviceCaps(hdcRef,VERTRES);  
	::ReleaseDC(NULL,hdcRef);


    // ============== 1) is it an enhanced MetaFile ==================================
	if(pemh->dSignature == META32_SIGNATURE) 
	{
		TRACE(_T("it's an Enhanced MetaFile\n"));
		lSize = pemh->nBytes;
		m_hEMF = SetEnhMetaFileBits(lSize,(CONST BYTE*) lpvData) ;
		m_strDescription.Empty();
		// MetaFileHeader lesen
		if(m_hEMF)
		{	
			GetEnhMetaFileHeader(m_hEMF,sizeof(EnhMetaHeader),&EnhMetaHeader);
			m_rectNormalized.SetRect(EnhMetaHeader.rclFrame.left, 
				EnhMetaHeader.rclFrame.top,EnhMetaHeader.rclFrame.right, 
				EnhMetaHeader.rclFrame.bottom);
			m_rectBounds.SetRect((m_rectNormalized.left*iWidthPels)/(iWidthMM*100),
				(m_rectNormalized.top*iHeightPels)/(iHeightMM*100),
				(m_rectNormalized.right*iWidthPels)/(iWidthMM*100),
				(m_rectNormalized.bottom*iHeightPels)/(iHeightMM*100));
			if(EnhMetaHeader.nDescription>0)
			{
				GetEnhMetaFileDescription(m_hEMF, EnhMetaHeader.nDescription, 
				m_strDescription.GetBufferSetLength(EnhMetaHeader.nDescription));
				m_strDescription.ReleaseBuffer();
			}
			else
				m_strDescription.Empty();

		}
		m_metafileType=OXMETAFILE_ENHANCED;
		return m_hEMF;
	}

	// ===============2) is is an Aldus MetaFile ==================================
	// If it has an ALDUS header skip it
    // Notice: APMSIZE is used instead of sizeof(ALDUSHEAD) because the 
	//	HANDLE and RECT of the structure
    //         depends on the environment and the align value
    if(*((LPDWORD)lpvData) == ALDUS_ID) 
	{	
		TRACE(_T("It's an Aldus MetaFile\n"));
		pAldusMF =(ALDUSHEADER*) lpvData;
        lSize = *((LPDWORD)((PBYTE)lpvData + APMSIZE + 6));
        // Notice: mtSize is size of the file in word.
        // if LPMETAFILEPICT is NULL
        //    MM_ANISOTROPIC mode and default device size will be used.
        m_hEMF=::SetWinMetaFileBits(lSize*2L,(PBYTE)lpvData+APMSIZE,NULL,NULL);
		VERIFY(m_strDescription.LoadString(IDS_OX_METAFILEALDUS)); //"WMF - Aldus Format"
		if(!m_hEMF) 
		{ 
			TRACE(_T("Error in SetWinMetaFileBits in Aldus MetaFile\n"));
			return 0L;
		}
		m_rectNormalized.SetRect(0,0,
			((pAldusMF->right-pAldusMF->left)*2540)/((int)pAldusMF->inch),
			((pAldusMF->bottom-pAldusMF->top)*2540)/((int)pAldusMF->inch));
		m_rectBounds.SetRect((m_rectNormalized.left*iWidthPels)/(iWidthMM*100),
			(m_rectNormalized.top*iHeightPels)/(iHeightMM*100),
			(m_rectNormalized.right*iWidthPels)/(iWidthMM*100),
			(m_rectNormalized.bottom*iHeightPels)/(iHeightMM*100));

		m_metafileType=OXMETAFILE_ALDUS;
		return m_hEMF;
    }
	// ================== 3) old Windows MetaFile ========================
    TRACE(_T("I try old Windows 3x MetaFile\n"));
	lSize = *((LPDWORD)((PBYTE)lpvData + 6));
    m_hEMF=::SetWinMetaFileBits(lSize*2L,(PBYTE)lpvData , NULL, NULL);
	VERIFY(m_strDescription.LoadString(IDS_OX_METAFILEWINDOWS)) ; //"Windows 3.x MetaFile"
	m_rectBounds.SetRect(0,0,::GetSystemMetrics(SM_CXSCREEN), 
		::GetSystemMetrics(SM_CYSCREEN));
	m_rectNormalized.SetRect(0,0,
		(m_rectBounds.Width()*iWidthMM*100)/iWidthPels,
		(m_rectBounds.Height()*iHeightMM*100)/iHeightPels);
	if(!m_hEMF) 
	{
	   TRACE(_T("Error on SetWinMetaFileBits in old windows MetaFile\n"));
	}
	else
		m_metafileType=OXMETAFILE_WIN16;
	return m_hEMF;
}