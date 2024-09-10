SOCKET WSASocketW(int af, int type, int protocol, LPWSAPROTOCOL_INFOW lpProtocolInfo, GROUP g, DWORD dwFlags)
{
	return WSASocketA(af, type, protocol, (LPWSAPROTOCOL_INFOA) lpProtocolInfo, g, dwFlags);
}