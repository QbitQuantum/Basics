//---------------------------------------------------------------------
size_t TFile::Size()
{
	if (m_stream==NULL) return -1;
	switch(m_StorageType){
	case 0:
		{
			LONG_PTR pos,size;
#ifdef WIN64
			pos = _ftelli64(static_cast<FILE*>(m_stream));
			_fseeki64(static_cast<FILE*>(m_stream),0,SEEK_END);
			size = _ftelli64(static_cast<FILE*>(m_stream));
			_fseeki64(static_cast<FILE*>(m_stream),pos,SEEK_SET);
#else
			pos = ftell(static_cast<FILE*>(m_stream));
			fseek(static_cast<FILE*>(m_stream),0,SEEK_END);
			size = ftell(static_cast<FILE*>(m_stream));
			fseek(static_cast<FILE*>(m_stream),pos,SEEK_SET);
#endif
			return static_cast<size_t>(size);
		}
	case 1:
		return m_Size;
	}
	return -1;
}