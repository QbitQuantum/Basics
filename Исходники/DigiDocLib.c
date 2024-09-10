//============================================================
// Gets a new temporary filename
// buf - filename buffer
//============================================================
EXP_OPTION int getTempFileName(char* szFileName, int len)
{
	char tbuf[200];
        int f = 0;
#ifdef WIN32
	char* pFileName = 0;
#endif
	RETURN_IF_NULL_PARAM(szFileName);
	memset(szFileName, 0, len);
#ifdef WIN32
	GetTempPath(sizeof(tbuf), tbuf);
	pFileName = _tempnam(tbuf, "ddoc");
	strncpy(szFileName, pFileName, len);
	free(pFileName);
#else
	strncpy(tbuf, "/tmp/ddocXXXXXX", sizeof(tbuf));
	f = mkstemp(tbuf);
	if (f > 0) // Maybe we should use the file instead of closing it and reopening later? 
          close(f);
	strncpy(szFileName, tbuf, len);
#endif
	return ERR_OK;
}