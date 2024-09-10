VOID _PrintExit(const CHAR *psz, ...)
{
	DWORD dwErr = GetLastError();
	
	LONG nIndent = 0;
	LONG nThread = 0;
	if (s_nTlsIndent >= 0) {
		nIndent = (LONG)TlsGetValue(s_nTlsIndent) - 1;
        ASSERT(nIndent >= 0);
		TlsSetValue(s_nTlsIndent, (PVOID)nIndent);
	}
	if (s_nTlsThread >= 0) {
		nThread = (LONG)TlsGetValue(s_nTlsThread);
	}
		
	if (s_bLog && psz) {
		CHAR szBuf[1024];
        PCHAR pszBuf = szBuf;
		LONG nLen = (nIndent > 0) ? (nIndent < 35 ? nIndent * 2 : 70) : 0;
        *pszBuf++ = (CHAR)('0' + ((nThread / 100) % 10));
		*pszBuf++ = (CHAR)('0' + ((nThread / 10) % 10));
		*pszBuf++ = (CHAR)('0' + ((nThread / 1) % 10));
		*pszBuf++ = ' ';
        while (nLen-- > 0) {
            *pszBuf++ = ' ';
        }

		va_list  args;
		va_start(args, psz);

        while ((*pszBuf++ = *psz++) != 0) {
            // Copy characters.
        }
        SyelogV(SYELOG_SEVERITY_INFORMATION,
                szBuf, args);

		va_end(args);
	}
	SetLastError(dwErr);
}