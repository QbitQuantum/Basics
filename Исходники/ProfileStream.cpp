	STDMETHODIMP Stat(STATSTG* pstatstg, DWORD grfStatFlag)
	{
		return m_spMemStream->Stat(pstatstg, grfStatFlag);
	};