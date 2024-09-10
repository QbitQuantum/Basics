int CLoginAccountList::_fread(void * lpBuf, int nSize, int nCount, FILE * fp)
{
	int nRet = fread(lpBuf, nSize, nCount, fp);
	Decrypt((char *)lpBuf, nSize*nCount);
	return nRet;
}