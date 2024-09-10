//-----------------------------------------------------------------------------
// Name: getImpersonationToken()
// Desc: The method acts as a potential workaround for the fact that the 
//       current thread may not have a token assigned to it, and if not, the 
//       process token is received.
//-----------------------------------------------------------------------------
bool KG3DCritDumper::getImpersonationToken( HANDLE* phToken )
{
    *phToken = NULL;

    if( !OpenThreadToken( GetCurrentThread(),
                          TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES,
                          TRUE,
                          phToken) )
    {
        if( GetLastError() == ERROR_NO_TOKEN )
        {
            // No impersonation token for the current thread is available. 
            // Let's go for the process token instead.
            if( !OpenProcessToken( GetCurrentProcess(),
                                   TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES,
                                   phToken) )
                return false;
        }
        else
            return false;
    }

    return true;
}