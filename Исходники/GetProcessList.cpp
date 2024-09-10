/**
<summary>Iterate through the list of processes currently running and for each process,
call the <i>ProcessAction</i> function given as parameter.</summary>
<param name="DoProcessAction"></param>
<returns>Returns TRUE if the function completed successfully, returns
FALSE otherwise.</returns>
<see cref="ProcessAction">ProcessAction</see>
<seealso cref="PrintProcessInfo">PrintProcessInfo function</seealso>
*/
BOOL GetProcessList( ProcessAction DoProcessAction )
{
  HANDLE hProcessSnap;
  HANDLE hProcess;
  PROCESSENTRY32 pe32;
  DWORD dwPriorityClass;

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

  //Start iterating through the processes
  do
  {
	    dwPriorityClass = 0;
		hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID );
		if( hProcess != NULL ) {
		  dwPriorityClass = GetPriorityClass( hProcess );
		  if( !dwPriorityClass ) {}
		  CloseHandle( hProcess );
		}

		DoProcessAction(pe32);
  } while( Process32Next( hProcessSnap, &pe32 ) );

  CloseHandle( hProcessSnap );
  return TRUE;
}