unsigned int __stdcall CWinThread::RunThreadFunc( void* pParam )
{
	DWORD dwRet = RunThreadFuncNoCRT(pParam);

#ifndef _ATL_MIN_CRT
	_endthreadex(dwRet);
#endif//_ATL_MIN_CRT

	return DWORD(dwRet);
}