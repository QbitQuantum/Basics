WinRegKeyExeption::WinRegKeyExeption(LONG errorcode, HKEY rootkey, wstring subkey, wstring label=L"")
:m_errorcode(errorcode),m_key(towstring<HKEY>(rootkey))
{
	m_key.append(L"\\");
	m_key.append(subkey);
	if(label.length()>0)
	{
		m_key.append(L"\\");
		m_key.append(label);
	}
}