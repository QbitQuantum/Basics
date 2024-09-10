/////////////////////////////////////////////////////////////////////////////////////////
// Name      : Wait
// Full name : CProcess::Wait
// Access    : public 
// Brief     : 
// Parameter : DWORD timeoutMillis
// Return    : bool
// Notes     : 
bool CProcess::Wait(DWORD timeoutMillis) const
{
	bool ok;
	
	DWORD result = ::WaitForSingleObject(mProcessInfo.hProcess, timeoutMillis);
	
	if (result == WAIT_TIMEOUT)
	{
		ok = false;
	}
	else if ( result == WAIT_OBJECT_0 )
	{
		ok = true;
	} // end of else if
	else
	{
		CWinError loWinErr;
		throw CEXP( "CProcess::Wait(), WaitForSingleObject failed(%d:%s)!", loWinErr.GetErrorCode(), loWinErr.GetErrorInfo());
	} // end of if
	
	return ok;
} // End of function Wait(...