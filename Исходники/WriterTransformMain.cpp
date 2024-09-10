	RM_ThirdReader(int iProcessIndex, u_int uMaxNumRandomSegments, u_int uMaxNumPoolThreads, u_int uNumStagingSegments) :
		RM_StagingReader(iProcessIndex,uMaxNumRandomSegments,uMaxNumPoolThreads,uNumStagingSegments) 
	{
		RM_InitData xInitData;
		{
			RM_SharedMemory xSharedMemory;
			std::string xSharedInitDataName(SHARED_INIT_DATA_NAME);
			void* pSharedMemory = xSharedMemory.OpenMemory(RM_ACCESS_WRITE | RM_ACCESS_READ, SHARED_INIT_DATA_MAX_SIZE, xSharedInitDataName, m_iPID);
			RM_SharedInitDataLayout xInitDataLayout;
			xInitDataLayout.MapMemory(pSharedMemory);
			xInitData = xInitDataLayout.GetInitData(m_iProcessIndex);
		}

		//the duplicate buffer
		{
			RM_SharedMemory xSharedMemory;
			std::string xSharedBuffName(xInitData.pSharedBufferMemNameOut);
			void* pSharedMemory = xSharedMemory.OpenMemory(RM_ACCESS_WRITE, SHARED_MEMORY_MAX_SIZE, xSharedBuffName, m_iPID);
			
			RM_SharedMemory xSharedMemoryLabels;
			std::string xLablesObjName(xSharedBuffName);
			xLablesObjName.append("Lables");
			void* pSharedMemoryLabels = xSharedMemoryLabels.OpenMemory(RM_ACCESS_WRITE | RM_ACCESS_READ, SHARED_MEMORY_LABESLS_MAX_SIZE, xLablesObjName, m_iPID);

			m_xSharedBufferDuplicate.MapMemory(pSharedMemory, pSharedMemoryLabels);

			const int iPID = _getpid();
			std::string xMsgQName(xInitData.pMessageQueueNameOut);
			m_xMessageManagerDuplicate.Initialise(iPID, xMsgQName);
		}
	}