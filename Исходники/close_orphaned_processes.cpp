void close_orphaned_processes( const std::list<std::string> &filenames )
{
	/*build absolute paths and convert to wide-char*/
	
	std::list<std::string> absolute_paths;

	for( std::list<std::string>::const_iterator i = filenames.begin(); i != filenames.end(); i++ )
	{
		char *absolute_path = build_absolute_path( i->c_str() );
		if( absolute_path )
		{
			absolute_paths.push_back( absolute_path );
			delete absolute_path;
		}
	}

	/*look for processes matching these absolute paths, and kill them*/

    PROCESSENTRY32 process_entry;
	process_entry.dwSize = sizeof( PROCESSENTRY32 );

    HANDLE process_snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );

	if( Process32First( process_snapshot, &process_entry ) == TRUE )
	{
		do{
			bool terminated = false;
			if( process_entry.th32ProcessID > 0 )
			{
				HANDLE module_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_entry.th32ProcessID);

				MODULEENTRY32 module_entry;
				module_entry.dwSize = sizeof( MODULEENTRY32 );
				if( Module32First( module_snapshot, &module_entry ) == TRUE )
				{
					for( std::list<std::string>::const_iterator i = absolute_paths.begin(); i != absolute_paths.end(); i++ )
					{
						std::wstring absolute_path_wide;
						absolute_path_wide.assign( i->begin(), i->end() );

						if( absolute_path_wide == module_entry.szExePath )
						{
							if( process_entry.th32ProcessID != GetCurrentProcessId() )
							{
								HANDLE process_handle = OpenProcess( PROCESS_TERMINATE, FALSE, process_entry.th32ProcessID );
								if( process_handle )
								{
									if( TerminateProcess( process_handle, 0 ) != 0 )
									{
										INTEGRA_TRACE_PROGRESS << "Killed orphaned process " << *i;
										terminated = true;
									}
									else
									{
										INTEGRA_TRACE_ERROR << "failed to terminate orphaned process.  Error:" << GetLastError();
									}

									CloseHandle( process_handle );
								}
								else
								{
									INTEGRA_TRACE_ERROR << "failed to kill orphaned process - couldn't open process handle.  Error: " << GetLastError();
								}
							}
						}

						if( terminated )
						{
							break;
						}

					}
					while( !terminated && Module32Next( module_snapshot, &module_entry ) == TRUE );
				}

				CloseHandle( module_snapshot );
			}
		}
		while( Process32Next( process_snapshot, &process_entry ) == TRUE );
	}

    CloseHandle( process_snapshot );
}