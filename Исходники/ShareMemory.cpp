	bool CShareMem::Open(std::string strSMName)
	{
		bool bResult = false;
		do 
		{
			if(strSMName.empty())
				break;

			m_strSMName = strSMName;

			if(!m_hMutexSyncData)
			{

				m_hFileMapObj = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, strSMName.c_str());
				if(NULL == m_hFileMapObj)
					break;

				m_pMapView = (char *)MapViewOfFile(m_hFileMapObj, FILE_MAP_ALL_ACCESS,0,0,0);
				if(NULL == m_pMapView)
					break;

				std::string strMutexName = strSMName + "Mutex";
				m_hMutexSyncData = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, strMutexName.c_str());
				if(NULL == m_hMutexSyncData)
					break;

				std::string strSemName = strSMName + "Recv";
					m_hWait[0] = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS , FALSE, strSemName.c_str());
				if(NULL == m_hWait[0])
					break;

				std::string strSemExit = strSMName + "Exit";
				m_hWait[1] = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, strSemExit.c_str());
				if(NULL == m_hWait[0])
					break;

				m_pWRPos = reinterpret_cast<PSWRPos>(m_pMapView);
				m_pUserBufBasePos = m_pMapView + sizeof(SWRPos);

			}

			m_bSMSuccess = bResult = true;
		} while (false);

		if(!bResult)
			close();

		return bResult;
	}