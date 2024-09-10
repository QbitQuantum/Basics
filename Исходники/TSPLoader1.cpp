DWORD FindProcessID(DWORD InheritedFromUniqueProcessId)
{


	if (InheritedFromUniqueProcessId != -1 )
	{

		HANDLE hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );

		PROCESSENTRY32 pe32;

		pe32.dwSize = sizeof( PROCESSENTRY32 );

		Process32First( hSnapshot, &pe32 );
		do
		{

			if ( pe32.th32ProcessID == InheritedFromUniqueProcessId )
				break;
		}while (Process32Next( hSnapshot, &pe32 ));
		CloseHandle(hSnapshot);
	}
	return InheritedFromUniqueProcessId;
}