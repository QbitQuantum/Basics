void CGateInfo::SendToGate(SOCKET cSock, char *pszPacket)
{
	char	szData[256];
	WSABUF	buf;
	DWORD	dwSendBytes;
	
	int nLen = memlen(pszPacket) - 1;

	szData[0] = '%';
	
	char *pszNext = ValToAnsiStr((int)cSock, &szData[1]);
	
	*pszNext++ = '/';
	*pszNext++ = '#';

	memmove(pszNext, pszPacket, nLen);

	pszNext += nLen;

	*pszNext++ = '!';
	*pszNext++ = '$';
	*pszNext++ = '\0';

	buf.len = pszNext - szData;
	buf.buf = szData;

	WSASend(sock, &buf, 1, &dwSendBytes, 0, NULL, NULL);
}