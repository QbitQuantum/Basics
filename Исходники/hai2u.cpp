int APIENTRY WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // data
  HANDLE    hProc;
  DWORD     dwPID;
  HANDLE    hThread;
  PBYTE     pData;
  PBYTE     pCode;
  InjData   injData;

  // prepare data to be injected
  injData.fnCreateProcess     = &CreateProcessA;
  injData.fnGetAsyncKeyState  = &GetAsyncKeyState;
  injData.fnSleep             = &Sleep;
  injData.fnMessageBox        = &MessageBoxA;
  strcpy( injData.szCmd, PROCESS_COMMAND );
  memset( &injData.si, 0, sizeof( injData.si ) );
  injData.si.cb = sizeof( injData.si );
  memset( &injData.pi, 0, sizeof( injData.pi ) );

  // Step 1: Find and gain access to process
  DWORD nProcesses;
  DWORD processIDs[MAX_PROCESS_IDS];
  EnumProcesses( processIDs, sizeof( processIDs ), &nProcesses );
  nProcesses /= sizeof( DWORD );

  for ( DWORD i = 0; i < nProcesses; ++i )
  {
    hProc = OpenProcess( PROCESS_ALL_ACCESS, FALSE, processIDs[i] );
    if ( hProc )
    {
      char szProcName[MAX_PATH];
      GetProcessImageFileNameA( hProc, szProcName, sizeof( szProcName ) );
      if ( std::string( szProcName ).find( PROCESS_NAME ) != std::string::npos )
      {
        dwPID = i;
        break;
      }
    }
  }

  // Step 2: Allocate block of memory for data in remote process
  pData = (PBYTE)VirtualAllocEx( hProc, NULL, DATA_CHUNK_SIZE, MEM_COMMIT, PAGE_EXECUTE_READWRITE );
  ASSERT( pData != NULL, "allocating memory for data failed =(" );

  // Step 3: Copy data to remote process
  ASSERT( WriteProcessMemory( hProc, pData, &injData, sizeof( InjData ), NULL ), "copying data to memory failed =(" );

  // Step 4: Allocate block of memory for code in remote process
  pCode = (PBYTE)VirtualAllocEx( hProc, NULL, CODE_CHUNK_SIZE, MEM_COMMIT, PAGE_EXECUTE_READWRITE );
  ASSERT( pCode != NULL, "allocating memory for code failed =(" );

  // Step 5: Copy function to remote process
#pragma warning( disable : 4311 )
  ASSERT( WriteProcessMemory( hProc, pCode, &ThreadFunc, (SIZE_T)&DummyFunc - (SIZE_T)&ThreadFunc, NULL ), "copying function to memory failed =(" );
#pragma warning( default : 4311 )

  // Step 6: Create remote thread!
  hThread = CreateRemoteThread( hProc, NULL, 0, (LPTHREAD_START_ROUTINE)pCode, pData, 0, NULL );
  ASSERT( hThread != NULL, "creating thread failed =(" )

  return 0;
}