long CardControl(SCARDHANDLE hCard, DWORD dwControlCode,
	LPCVOID lpInBuffer, DWORD nInBufferSize,
	LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned)
{
#ifndef __OLD_PCSC_API__
	long lRet = SCardControl(hCard, dwControlCode,
		lpInBuffer, nInBufferSize,
		lpOutBuffer, nOutBufferSize, lpBytesReturned);

	//printf("SCardControl()\n");

	return lRet;
#else
        long lRet = SCardControl(hCard,
                (const unsigned char *) lpInBuffer, nInBufferSize,
                (unsigned char*) lpOutBuffer, lpBytesReturned);

	//printf("SCardControl()\n");

	return lRet;
#endif
}