int CResolver::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	ASSERT(socket);
CString hostName = socket->m_HostName;
int at = hostName.Find('@');
	if(at>=0)
		hostName=hostName.Mid(at+1);
	m_hAsync=WSAAsyncGetHostByName(m_hWnd,WM_RESOLVED,(LPCTSTR)hostName,(char*)socket->m_ResolveBuff,sizeof(socket->m_ResolveBuff));
	ASSERT(m_hAsync);
	return 0;
}