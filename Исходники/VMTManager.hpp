	uint32_t CalculateLength() {
		uint32_t dwIndex = 0;
		if (!m_pOriginalVMTable) return 0;
		for (dwIndex = 0; m_pOriginalVMTable[dwIndex]; dwIndex++) {
			if (IsBadCodePtr((FARPROC)m_pOriginalVMTable[dwIndex])) {
				break;
			}
		}
		return dwIndex;
	}