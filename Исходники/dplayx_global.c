/***************************************************************************
 * Called to initialize the global data. This will only be used on the
 * loading of the dll
 ***************************************************************************/
BOOL DPLAYX_ConstructData(void)
{
  SECURITY_ATTRIBUTES s_attrib;
  BOOL                bInitializeSharedMemory = FALSE;
  LPVOID              lpDesiredMemoryMapStart = (LPVOID)0x50000000;
  HANDLE              hInformOnStart;

  TRACE( "DPLAYX dll loaded - construct called\n" );

  /* Create a semaphore to block access to DPLAYX global data structs */

  s_attrib.bInheritHandle       = TRUE;
  s_attrib.lpSecurityDescriptor = NULL;
  s_attrib.nLength              = sizeof(s_attrib);

  hDplayxSema = CreateSemaphoreA( &s_attrib, 0, 1, lpszDplayxSemaName );

  /* First instance creates the semaphore. Others just use it */
  if( GetLastError() == ERROR_SUCCESS )
  {
    TRACE( "Semaphore %p created\n", hDplayxSema );

    /* The semaphore creator will also build the shared memory */
    bInitializeSharedMemory = TRUE;
  }
  else if ( GetLastError() == ERROR_ALREADY_EXISTS )
  {
    TRACE( "Found semaphore handle %p\n", hDplayxSema );
    DPLAYX_AcquireSemaphore();
  }
  else
  {
    ERR( ": semaphore error %d\n", GetLastError() );
    return FALSE;
  }

  SetLastError( ERROR_SUCCESS );

  hDplayxSharedMem = CreateFileMappingA( INVALID_HANDLE_VALUE,
                                         &s_attrib,
                                         PAGE_READWRITE | SEC_COMMIT,
                                         0,
                                         dwTotalSharedSize,
                                         lpszDplayxFileMapping );

  if( GetLastError() == ERROR_SUCCESS )
  {
    TRACE( "File mapped %p created\n", hDplayxSharedMem );
  }
  else if ( GetLastError() == ERROR_ALREADY_EXISTS )
  {
    TRACE( "Found FileMapping handle %p\n", hDplayxSharedMem );
  }
  else
  {
    ERR( ": unable to create shared memory (%d)\n", GetLastError() );
    DPLAYX_ReleaseSemaphore();
    return FALSE;
  }

  lpSharedStaticData = MapViewOfFileEx( hDplayxSharedMem,
                                        FILE_MAP_WRITE,
                                        0, 0, 0, lpDesiredMemoryMapStart );

  if( lpSharedStaticData == NULL )
  {
    ERR( ": unable to map static data into process memory space (%d)\n",
         GetLastError() );
    DPLAYX_ReleaseSemaphore();
    return FALSE;
  }
  else
  {
    if( lpDesiredMemoryMapStart == lpSharedStaticData )
    {
      TRACE( "File mapped to %p\n", lpSharedStaticData );
    }
    else
    {
      /* Presently the shared data structures use pointers. If the
       * files are not mapped into the same area, the pointers will no
       * longer make any sense :(
       * FIXME: In the future make the shared data structures have some
       *        sort of fixup to make them independent between data spaces.
       *        This will also require a rework of the session data stuff.
       */
      ERR( "File mapped to %p (not %p). Expect failure\n",
            lpSharedStaticData, lpDesiredMemoryMapStart );
    }
  }

  /* Dynamic area starts just after the static area */
  lpMemArea = (LPVOID)((BYTE*)lpSharedStaticData + dwStaticSharedSize);

  /* FIXME: Crude hack */
  lobbyData   = lpSharedStaticData;
  sessionData = (DPSESSIONDESC2*)((BYTE*)lpSharedStaticData + (dwStaticSharedSize/2));

  /* Initialize shared data segments. */
  if( bInitializeSharedMemory )
  {
    UINT i;

    TRACE( "Initializing shared memory\n" );

    /* Set all lobbies to be "empty" */
    for( i=0; i < numSupportedLobbies; i++ )
    {
      DPLAYX_InitializeLobbyDataEntry( &lobbyData[ i ] );
    }

    /* Set all sessions to be "empty" */
    for( i=0; i < numSupportedSessions; i++ )
    {
      sessionData[i].dwSize = 0;
    }

    /* Zero out the dynamic area */
    ZeroMemory( lpMemArea, dwDynamicSharedSize );

    /* Just for fun sync the whole data area */
    FlushViewOfFile( lpSharedStaticData, dwTotalSharedSize );
  }

  DPLAYX_ReleaseSemaphore();

  /* Everything was created correctly. Signal the lobby client that
   * we started up correctly
   */
  if( DPLAYX_GetThisLobbyHandles( &hInformOnStart, NULL, NULL, FALSE ) &&
      hInformOnStart
    )
  {
    BOOL bSuccess;
    bSuccess = SetEvent( hInformOnStart );
    TRACE( "Signalling lobby app start event %p %s\n",
             hInformOnStart, bSuccess ? "succeed" : "failed" );

    /* Close out handle */
    DPLAYX_GetThisLobbyHandles( &hInformOnStart, NULL, NULL, TRUE );
  }

  return TRUE;
}