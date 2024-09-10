BOOL CControlSocket::Connect(CString hostAddress, UINT nHostPort)
{
	hostAddress = ConvertDomainName(hostAddress);

	//Don't resolve host asynchronously when using proxies
	if (m_pProxyLayer)
	{
		//If using proxies, we can't use ident -> won't be reachable from outside
		
		return CAsyncSocketEx::Connect(hostAddress, nHostPort);
	}
	BOOL res = CAsyncSocketEx::Connect(hostAddress, nHostPort);
	int nLastError = WSAGetLastError();
	if (res || nLastError==WSAEWOULDBLOCK)
	{
#ifndef MPEXT_NO_IDENT
		if (COptions::GetOptionVal(OPTION_IDENT))
			m_pIdentControl = new CIdentServerControl(this);
#endif
		WSASetLastError(nLastError);
	}
	
	return res;
}