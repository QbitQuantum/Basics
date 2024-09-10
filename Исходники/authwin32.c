LPVOID QueryInfo
(JNIEnv * jenv, HANDLE hToken, TOKEN_INFORMATION_CLASS klass) 
{
	PORT_ACCESS_FROM_ENV (jenv);

	DWORD dwSize;
	LPVOID pData = NULL;

	if( !GetTokenInformation(hToken, klass, NULL, 0, &dwSize) ) {
		DWORD dwErr = GetLastError();
		if( ERROR_INSUFFICIENT_BUFFER != dwErr ) {
			return NULL;
		}
	}

	pData = hymem_allocate_memory(dwSize);
	if( !GetTokenInformation(hToken, klass, pData, dwSize, &dwSize) ) {
		DWORD dwErr = GetLastError();
		hymem_free_memory(pData);
		SetLastError(dwErr);
		return NULL;
	}
	return pData;
}