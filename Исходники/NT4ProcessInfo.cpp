/*----------------------------------------------------------------------
FUNCTION        :   NT4GetLoadedModules
DISCUSSION      :
    The NT4 specific version of GetLoadedModules.  This function assumes
that GetLoadedModules does the work to validate the parameters.
PARAMETERS      :
    dwPID        - The process ID to look into.
    uiCount      - The number of slots in the paModArray buffer.  If
                   this value is 0, then the return value will be TRUE
                   and pdwRealCount will hold the number of items
                   needed.
    paModArray   - The array to place the HMODULES into.  If this buffer
                   is too small to hold the result and uiCount is not
                   zero, then FALSE is returned, but pdwRealCount will
                   be the real number of items needed.
    pdwRealCount - The count of items needed in paModArray, if uiCount
                   is zero, or the real number of items in paModArray.
RETURNS         :
    FALSE - There was a problem, check GetLastError.
    TRUE  - The function succeeded.  See the parameter discussion for
            the output parameters.
----------------------------------------------------------------------*/
BOOL NT4GetLoadedModules ( DWORD     dwPID        ,
                           UINT      uiCount      ,
                           HMODULE * paModArray   ,
                           LPDWORD   pdwRealCount   )
{

    // Initialize PSAPI.DLL, if needed.
    if ( FALSE == InitPSAPI ( ) )
    {
        ASSERT ( FALSE ) ;
        SetLastErrorEx ( ERROR_DLL_INIT_FAILED , SLE_ERROR ) ;
        return ( FALSE ) ;
    }

    // Convert the process ID into a process handle.
    HANDLE hProc = OpenProcess ( PROCESS_QUERY_INFORMATION |
                                    PROCESS_VM_READ         ,
                                 FALSE                      ,
                                 dwPID                       ) ;
    ASSERT ( NULL != hProc ) ;
    if ( NULL == hProc )
    {
        TRACE1 ( "Unable to OpenProcess on %08X\n" , dwPID ) ;
        return ( FALSE ) ;
    }

    // Now get the modules for the specified process.
    ASSERT ( NULL != g_pEnumProcessModules ) ;
    // Because of possible DLL unload order differences, make sure that
    //  PSAPI.DLL is still loaded in case this function is called during
    //  shutdown.
    ASSERT ( FALSE == IsBadCodePtr ( (FARPROC)g_pEnumProcessModules ) );
    if ( TRUE == IsBadCodePtr ( (FARPROC)g_pEnumProcessModules ) )
    {
        TRACE0 ( "PSAPI.DLL has been unloaded on us!\n" ) ;

        // Close the process handle used.
        VERIFY ( CloseHandle ( hProc ) ) ;

        SetLastErrorEx ( ERROR_INVALID_DLL , SLE_ERROR ) ;

        return ( FALSE ) ;
    }

    DWORD dwTotal = 0 ;
    BOOL bRet = g_pEnumProcessModules ( hProc                        ,
                                        paModArray                   ,
                                        uiCount * sizeof ( HMODULE ) ,
                                        &dwTotal                      );

    // Close the process handle used.
    VERIFY ( CloseHandle ( hProc ) ) ;

    // Convert the count from bytes to HMODULE values.
    *pdwRealCount = dwTotal / sizeof ( HMODULE ) ;

    // If bRet was FALSE, and the user was not just asking for the
    //  total, there was a problem.
    if ( ( ( FALSE == bRet ) && ( uiCount > 0 ) ) || ( 0 == dwTotal ) )
    {
        ASSERT ( FALSE ) ;
        TRACE0 ( "EnumProcessModules failed!\n" ) ;
        return ( FALSE ) ;
    }

    // If the total returned in pdwRealCount is larger than the value in
    //  uiCount, then return an error.  If uiCount is zero, then it is
    //  not an error.
    if ( ( *pdwRealCount > uiCount ) && ( uiCount > 0 ) )
    {
        ASSERT ( FALSE ) ;
        TRACE0 ( "Buffer is too small in NT4GetLoadedModules!\n" ) ;
        SetLastErrorEx ( ERROR_INSUFFICIENT_BUFFER , SLE_ERROR ) ;
        return ( FALSE ) ;
    }

    // All OK, Jumpmaster!
    SetLastError ( ERROR_SUCCESS ) ;
    return ( TRUE ) ;
}