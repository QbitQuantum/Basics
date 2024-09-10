/*----------------------------------------------------------------------
FUNCTION        :   TLHELPGetLoadedModules
DISCUSSION      :
    The TOOLHELP32 specific version of GetLoadedModules.  This function
assumes that GetLoadedModules does the work to validate the parameters.
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
BOOL __stdcall TLHELPGetLoadedModules ( DWORD     dwPID        ,
                                        UINT      uiCount      ,
                                        HMODULE * paModArray   ,
                                        LPDWORD   pdwRealCount   )
{

    // Always set pdwRealCount to a know value before anything else.
    *pdwRealCount = 0 ;

    if ( FALSE == InitTOOLHELP32 ( ) )
    {
        ASSERT ( !"InitTOOLHELP32 failed" ) ;
        SetLastErrorEx ( ERROR_DLL_INIT_FAILED , SLE_ERROR ) ;
        return ( FALSE ) ;
    }

    // The snapshot handle.
    HANDLE        hModSnap     = NULL ;
    // The module structure.
    MODULEENTRY32 stME32              ;
    // A flag kept to report if the buffer was too small.
    BOOL          bBuffToSmall = FALSE ;


    // Get the snapshot for the specified process.
    hModSnap = g_pCreateToolhelp32Snapshot ( TH32CS_SNAPMODULE ,
                                             dwPID              ) ;
    ASSERT ( INVALID_HANDLE_VALUE != hModSnap ) ;
    if ( INVALID_HANDLE_VALUE == hModSnap )
    {
        TRACE1 ( "Unable to get module snapshot for %08X\n" , dwPID ) ;
        return ( FALSE ) ;
    }

    FillMemory ( &stME32 , sizeof ( MODULEENTRY32 ), NULL ) ;
    stME32.dwSize = sizeof ( MODULEENTRY32 ) ;

    // Start getting the module values.
    if ( TRUE == g_pModule32First ( hModSnap , &stME32 ) )
    {
        do
        {
            // If uiCount is not zero, copy values.
            if ( 0 != uiCount )
            {
                // If the passed in buffer is to small, set the flag.
                // This is so we match the functionality of the NT4
                // version of this function which will return the
                // correct total needed.
                if ( ( TRUE == bBuffToSmall     ) ||
                     ( *pdwRealCount == uiCount )   )
                {
                    bBuffToSmall = TRUE ;
                    break ;
                }
                else
                {
                    // Copy this value in.
                    paModArray[ *pdwRealCount ] =
                                         (HINSTANCE)stME32.modBaseAddr ;
                }
            }
            // Bump up the real total count.
            *pdwRealCount += 1 ;
        }
        while ( ( TRUE == g_pModule32Next ( hModSnap , &stME32 ) ) ) ;
    }
    else
    {
        DWORD dwLastErr = GetLastError ( ) ;
        ASSERT ( !"Failed to get first module!\n" ) ;
        SetLastErrorEx ( dwLastErr , SLE_ERROR ) ;
        return ( FALSE ) ;
    }

    // Close the snapshot handle.
    VERIFY ( CloseHandle ( hModSnap ) ) ;

    // Check if the buffer was too small.
    if ( TRUE == bBuffToSmall )
    {
        ASSERT ( !"Buffer to small in TLHELPGetLoadedModules\n" ) ;
        SetLastErrorEx ( ERROR_INSUFFICIENT_BUFFER , SLE_ERROR ) ;
        return ( FALSE ) ;
    }

    // All OK, Jumpmaster!
    SetLastError ( ERROR_SUCCESS ) ;
    return ( TRUE ) ;
}