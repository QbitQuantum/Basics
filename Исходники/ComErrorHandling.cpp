//*****************************************************************************
//* Function Name: ThrowComErrorException
//*   Description: 
//*****************************************************************************
void ThrowComErrorException (
	LPCTSTR		p_lpszFile,
	UINT		p_uLine,
	HRESULT		p_hr,
	UINT		p_uResourceId,
	...)
{
	TCHAR l_szFormatString[1024] = {0};
	if (::LoadString (_Module.GetResourceInstance (), p_uResourceId, l_szFormatString, 1024) > 0) {

		va_list l_varargs;
		va_start (l_varargs, p_uResourceId);

		TCHAR l_szDescription[1024]  = {0};

#if _MSC_VER >= 1400
		(void) _vsntprintf_s (l_szDescription, 1024, l_szFormatString, l_varargs);
#else
		(void) _vsntprintf (l_szDescription, 1024, l_szFormatString, l_varargs);
#endif

		va_end (l_varargs);

		ThrowComErrorException (p_lpszFile, p_uLine, p_hr, l_szDescription);
	}
	else {
		DWORD l_dwLastError = ::GetLastError ();
		_com_issue_error (HRESULT_FROM_WIN32 (l_dwLastError));
	}
}