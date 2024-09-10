DWORD getProcessWithParent(int pid)
{
  HANDLE hProcessSnap;
  PROCESSENTRY32 pe32;

  // Take a snapshot of all processes in the system.
  hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
  if( hProcessSnap == INVALID_HANDLE_VALUE )
  {
    return( FALSE );
  }

  // Set the size of the structure before using it.
  pe32.dwSize = sizeof( PROCESSENTRY32 );

  // Retrieve information about the first process,
  // and exit if unsuccessful
  if( !Process32First( hProcessSnap, &pe32 ) )
  {
    CloseHandle( hProcessSnap );          // clean the snapshot object
    return( FALSE );
  }

  // Now walk the snapshot of processes, and
  // display information about each process in turn
  DWORD parent = static_cast<DWORD>(pid);
  DWORD childID = 0xffffffff;
  do
  {
      if(pe32.th32ParentProcessID == parent)
         return static_cast<int>(pe32.th32ProcessID);
  } while( Process32Next( hProcessSnap, &pe32 ) );

  _tprintf( TEXT("Never found process with parent!") );
  return childID;
}