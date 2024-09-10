HMODULE GetRemoteModuleHandle( char *szModuleName, HANDLE hProcess, bool bUsePath )
{
	HANDLE tlh = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, GetProcessId( hProcess ) );

	MODULEENTRY32 modEntry;
	
	modEntry.dwSize = sizeof( MODULEENTRY32 );

	Module32First( tlh, &modEntry );
	do
	{
		string comp;
		comp.clear();

		if(bUsePath){ comp = modEntry.szExePath; } else { comp = modEntry.szModule; }

		if( !strcmp( szModuleName, comp.c_str() ) )
		{
			CloseHandle( tlh );

			return modEntry.hModule;
		}
	}
	while(Module32Next( tlh, &modEntry ) );

	CloseHandle( tlh );

	return NULL;
}