HANDLE
MakeMutex(char *mutexname)
{
/*2000.9.4 add---------------------------------------------------------------*/
	HANDLE	hMutex;
	char	evtname[128];
	SECURITY_ATTRIBUTES	FileMappingAttributes;
	SECURITY_DESCRIPTOR	SecuDesc;

	InitializeSecurityDescriptor( &SecuDesc, SECURITY_DESCRIPTOR_REVISION );
	SetSecurityDescriptorDacl( &SecuDesc, TRUE, NULL, FALSE );
	FileMappingAttributes.nLength = sizeof(FileMappingAttributes);
	FileMappingAttributes.lpSecurityDescriptor = &SecuDesc;
/*2000.9.4 end---------------------------------------------------------------*/

	strcpy( evtname, mutexname );
#ifdef	TERMINAL_SERVICE
	if( osvi.dwMajorVersion >= 5 )	/* Windows 2000 */
		sprintf( evtname "Global\\%d", mutexname );
#endif	/* TERMINAL_SERVICE */

	hMutex=CreateMutex( &FileMappingAttributes, FALSE, evtname );
	if (hMutex==NULL)
	{
		sprintf(tbuf, "Create %s Mutex error = [%d]", evtname, GetLastError());
		MessageBox(NULL, tbuf, "IPC DAEMON", MB_OK);
		ExitProcess(1);
	}
	else
	{
		if (GetLastError()==ERROR_ALREADY_EXISTS)
		{
//			MessageBox(NULL, "IPC DAEMON is already active ...", 
//			"IPC DAEMON", MB_OK);
			CloseHandle(hMutex);
			ExitProcess(1);
		}
	}
	return hMutex;
}