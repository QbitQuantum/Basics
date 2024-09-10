/////////////////////////////////////////////////////////////////////////////////////////
// Name      : GetFunc
// Full name : CLoadLib::GetFunc
// Access    : public 
// Brief     : 
// Parameter : const char* szFuncName
// Return    : FARPROC
// Notes     : 
FARPROC CLoadLib::GetFunc(const char* szFuncName)
{
    if (SUCCEEDED(mhModule))
    {
        FARPROC loProc = ::GetProcAddress(mhModule, szFuncName);
        if (loProc != NULL)
        {
            return loProc;
        }
        else
        {
            CWinError loErr;
            miLastError = loErr.GetErrorCode();
            mstrLastError = loErr.GetErrorInfo();
            return NULL;
        }
    }
    else
    {
        miLastError = -1;
        mstrLastError = "dll is unloaded!";
        return NULL;
    }
} // End of function GetFunc(...