	BSTR SysAllocString() {
		if(m_length > 0)
			return SysAllocStringLen(m_buffer,m_length);
		return 0;
	}