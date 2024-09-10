LPCSTR
CSockLpxAddr::ToStringA(DWORD radix)
{
	LPSTR lpBuffer = reinterpret_cast<LPSTR>(m_buffer);
	HRESULT hr = ::StringCchPrintfA(
		lpBuffer, RTL_NUMBER_OF(m_buffer), 
		(radix == 10) ? 
		"%02X:%02X:%02X:%02X:%02X:%02X(%05d)" :
		"%02X:%02X:%02X:%02X:%02X:%02X(%04X)",
		m_sockLpxAddr.LpxAddress.Node[0],
		m_sockLpxAddr.LpxAddress.Node[1],
		m_sockLpxAddr.LpxAddress.Node[2],
		m_sockLpxAddr.LpxAddress.Node[3],
		m_sockLpxAddr.LpxAddress.Node[4],
		m_sockLpxAddr.LpxAddress.Node[5],
		NTOHS(m_sockLpxAddr.LpxAddress.Port));
	_ASSERTE(SUCCEEDED(hr));
	return lpBuffer;
}