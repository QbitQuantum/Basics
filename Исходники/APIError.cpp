//-----------------------------------------------------------------------------
// Name: ShowLastError
// Object: show last windows api error
// Parameters :
//     in  :
//     out :
//     return : TRUE on success, FALSE on error
//-----------------------------------------------------------------------------
BOOL CAPIError::ShowLastError()
{
#if (defined(TOOLS_NO_MESSAGEBOX))
    return TRUE;
#else
    TCHAR pcError[MAX_PATH];
    DWORD dwLastError=GetLastError();
    DWORD dw=FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL,
                           dwLastError,
                           GetUserDefaultLangID(),//GetSystemDefaultLangID()
                           pcError,
                           MAX_PATH-1,
                           NULL);
    
    
    //If the function succeeds, the return value is the number of TCHARs stored in the output buffer,
    //  excluding the terminating null character.
    //If the function fails, the return value is zero
    if(dw==0)
        return FALSE;// FormatMessage failed
    else
    {
        return MessageBox(NULL,pcError,_T("Error"),MB_OK|MB_ICONERROR|MB_TOPMOST);
    }
#endif
}