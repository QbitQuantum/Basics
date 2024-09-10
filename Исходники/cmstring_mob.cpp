CMString& CMString::Format(const WCHAR *fmt,...)
{
    ASSERT(fmt!=NULL);
    if(m_sData)
    {
        delete []m_sData;
        m_sData = NULL;
    }
    va_list va;
    va_start(va, fmt);
    INT32 len = 1023;//vwprintf(NULL,fmt,va);
    m_sData = new WCHAR[len+1];
    ASSERT(m_sData!=NULL);
    _vsnwprintf(m_sData,1023,fmt,va);
	len = wcslen(m_sData);
	if(len < 512)
	{
		WCHAR *pstr = new WCHAR[len+1];
		if(pstr)
		{
			wcscpy(pstr,m_sData);
			delete []m_sData;
			m_sData = pstr;
		}
	}
    va_end(va);
    return *this;
}