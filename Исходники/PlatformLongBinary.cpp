BOOL
LongBinary::SetBinarySize(DWORD sizeNew, void* lpDataCopy){
	if (m_hMemory == NULL){ // Allocate
		m_pBuffer = NULL;
		if (sizeNew == 0)
			return TRUE;
		m_hMemory = HeapCreate(0L, sizeNew, 0L);
		ASSERT(m_hMemory);
		m_pBuffer = HeapAlloc(m_hMemory, 0L, sizeNew);
		m_dwSize = sizeNew;
	}
	else{ // Reallocate
		if (sizeNew > m_dwSize){
			// Allocate or realocate memory . #####
			m_pBuffer = HeapReAlloc(m_hMemory, 0L, m_pBuffer, sizeNew);
			m_dwSize = sizeNew;
		}
		else
			if (sizeNew == 0){
				HeapFree(m_hMemory, 0L, m_pBuffer);
				HeapDestroy(m_hMemory);
				m_pBuffer = NULL;
				m_hMemory = NULL;
				m_dwSize = 0;
			}
		}

	if( lpDataCopy != NULL && m_hMemory ){
		memcpy(m_pBuffer, lpDataCopy, sizeNew);
		}
	return TRUE;
	}