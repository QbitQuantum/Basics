int __stdcall AddClientDV ( LPDVINFO lpDVInfo )
{
    BOOL bRet = TRUE ;

    __try
    {
        __try
        {
            // Check all the parameters.
            ASSERT ( NULL != lpDVInfo ) ;
            ASSERT ( FALSE ==
                          IsBadCodePtr ( (FARPROC)lpDVInfo->pfnDump) ) ;
            ASSERT ( FALSE ==
                       IsBadCodePtr ( (FARPROC)lpDVInfo->pfnValidate ));
            ASSERT ( 0 == lpDVInfo->dwValue ) ;

            if ( ( NULL == lpDVInfo )                                ||
                 ( TRUE ==
                      IsBadCodePtr((FARPROC)lpDVInfo->pfnDump     ) )||
                 ( TRUE ==
                      IsBadCodePtr((FARPROC)lpDVInfo->pfnValidate ) )||
                 ( 0 != lpDVInfo->dwValue                           )  )
            {
                TRACE ( "Bad parameters to AddClientDV\n" );
                return ( FALSE ) ;
            }

            // Has everything been initialized?
            if ( FALSE == g_bLibInit )
            {
                InitializeLibrary ( ) ;
            }

            // Block access to the library.
            EnterCriticalSection ( &g_stCritSec ) ;

            // No matter what, bump up g_dwDVCount.
            g_dwDVCount++ ;

            // Check that this is not one bump too many.
            ASSERT ( (WORD)g_dwDVCount < (WORD)0xFFFF ) ;
            if ( (WORD)g_dwDVCount == (WORD)0xFFFF )
            {
                bRet = FALSE ;
                __leave ;
            }

            // Generate the client block ID.
            lpDVInfo->dwValue = CLIENT_BLOCK_VALUE ( g_dwDVCount ) ;

            // Is this the first time through?
            if ( 1 == g_dwDVCount )
            {
                ASSERT ( NULL == g_pstDVInfo ) ;

                // Allocate the array for the first time.
                g_pstDVInfo =
                       (LPDVINFO)HeapAlloc ( g_hHeap                  ,
                                             HEAP_GENERATE_EXCEPTIONS |
                                              HEAP_ZERO_MEMORY        ,
                                             sizeof ( DVINFO )        );
                g_pstDVInfo[ 0 ] = *lpDVInfo ;
            }
            else
            {
                // This is not the first time so reallocate the array
                // and tack this new puppy on the end.
                g_pstDVInfo =
                    (LPDVINFO)HeapReAlloc ( g_hHeap                     ,
                                            HEAP_GENERATE_EXCEPTIONS |
                                                HEAP_ZERO_MEMORY        ,
                                            g_pstDVInfo                 ,
                                            g_dwDVCount *
                                                      sizeof ( DVINFO));
                g_pstDVInfo[ g_dwDVCount - 1 ] = *lpDVInfo ;
            }
        }
        __except ( EXCEPTION_EXECUTE_HANDLER )
        {
            ASSERT ( !"Had a crash in AddClientDV!" ) ;
            bRet = FALSE ;
        }
    }
    __finally
    {
        LeaveCriticalSection ( &g_stCritSec ) ;
    }
    return ( bRet ) ;
}