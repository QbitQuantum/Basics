//#define LocalTest
//#define ServerTest
//#define Final
void LaunchRose( char* ip, int port )
{
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi;
	unsigned char myBuffer[ 0x200 ];

	
#if defined(ServerTest)
	sprintf( (char*)myBuffer, "TRose.exe @TRIGGER_SOFT@ _server 127.0.0.1 _port 29000");
#elif defined(LocalTest)
	sprintf( (char*)myBuffer, "TRose.exe @TRIGGER_SOFT@ _server 127.0.0.1 _port 29000");
#else
	sprintf( (char*)myBuffer, "TRose.exe @TRIGGER_SOFT@ _server %s _port %i", ip, port );
#endif
	if( CreateProcessA( 0, (char*)myBuffer, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi ) )
	{
		// Loaded OK
		char myDLLName[] = "AdventureRose.dll";
		DWORD dwWritten = 0;
		LPVOID myDLLSpace = VirtualAllocEx( pi.hProcess, 0, sizeof( myDLLName ), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
		WriteProcessMemory( pi.hProcess, myDLLSpace, myDLLName, sizeof( myDLLName ), &dwWritten );
		if( dwWritten != sizeof( myDLLName ) )
		{
			MessageBox( 0, "Failed to inject new game code", "WARNING", MB_ICONERROR | MB_OK );
			TerminateProcess( pi.hProcess, 0 );
		}
		else
		{
			{
				int tid = 0;
				HANDLE thread;

				CreateRemoteThread( pi.hProcess, 0, 0, (LPTHREAD_START_ROUTINE)GetProcAddress( GetModuleHandleA("kernel32.dll"), "LoadLibraryA"), myDLLSpace, 0, (LPDWORD)&tid );
				thread = OpenThread( THREAD_ALL_ACCESS, 0, tid );
				WaitForSingleObject( thread, 5000 );
				CloseHandle( thread );
			}

#if defined(ServerTest) || defined(Final)
			char myDLLName2[] = "RoseProtect.dll";
			dwWritten =0;
			myDLLSpace = VirtualAllocEx( pi.hProcess, 0, sizeof( myDLLName2 ), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
			WriteProcessMemory( pi.hProcess, myDLLSpace, myDLLName2, sizeof( myDLLName2 ), &dwWritten );
			if( dwWritten != sizeof( myDLLName2 ) )
			{
				MessageBox( 0, "Failed to inject protection code", "WARNING", MB_ICONERROR | MB_OK );
				TerminateProcess( pi.hProcess, 0 );
			}
			else
			{
				{
					int tid = 0;
					HANDLE thread;

					CreateRemoteThread( pi.hProcess, 0, 0, (LPTHREAD_START_ROUTINE)GetProcAddress( GetModuleHandleA("kernel32.dll"), "LoadLibraryA"), myDLLSpace, 0, (LPDWORD)&tid );
					thread = OpenThread( THREAD_ALL_ACCESS, 0, tid );
					WaitForSingleObject( thread, 5000 );
					CloseHandle( thread );
				}
#endif
				ResumeThread( pi.hThread );
#if defined(ServerTest) || defined(Final)
			}
#endif
		}
	} else {
		MessageBox( 0, "Could not find/load TRose.exe", "WARNING", MB_ICONERROR | MB_OK );
	}
}