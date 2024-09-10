	uint32 GetSize() const
	{
		STATSTG pst;
		HRESULT hr = m_pStream->Stat(&pst,STATFLAG_NONAME);
		check(hr == S_OK && &pst != NULL);
		return (uint32)pst.cbSize.QuadPart;
	}