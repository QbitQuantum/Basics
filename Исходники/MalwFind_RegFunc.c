NTSTATUS  
RegProc_DeleteKey( HANDLE hKey, PVOID pRootObject, PUNICODE_STRING pSubKey )
{
	ULONG        ulLength = 0;
	NAME_BUFFER  RegPath  = {0};
	NTSTATUS     Status   = STATUS_SUCCESS;
	WCHAR        wzProcName[ MAX_PROCESS_LEN ] = L"";

	if(!hKey && !pRootObject) return Status;
	if(ExGetPreviousMode() == KernelMode) return Status;
	if(KeGetCurrentIrql() >= DISPATCH_LEVEL) return Status;


	if (FALSE == g_MalwFind.DrvConfig.bGlobalCtrl)
	{
		return Status;
	}
	RtlZeroMemory( wzProcName, sizeof(WCHAR)*MAX_PROCESS_LEN );
	GetProcessName( PsGetCurrentProcess(), wzProcName, MAX_PROCESS_LEN );
	// 전역기능 예외프로세스 판단.
	if(ISExpProcList_PolicyAll( wzProcName )) 
	{
		return Status;
	}

	ALLOCATE_N_REG_POOL( RegPath );
	if(!RegPath.pBuffer) return Status;
	SET_REG_POOL_ZERO( RegPath );

	ulLength = GetRegFullPath( hKey, pRootObject, pSubKey, &RegPath );
	if(ulLength <= 0) 
	{
		FREE_N_REG_POOL( RegPath );	
		return STATUS_SUCCESS;
	}

	_wcslwr( RegPath.pBuffer );
	if( wcsstr(RegPath.pBuffer, SVCNAME_AGENT) || wcsstr(RegPath.pBuffer, SVCNAME_DRIVER) )
	{
		KdPrint(("RegProc_DeleteKey=[%ws] \n", RegPath.pBuffer ));
		// SetupDir Control == FALSE:제어안함   TRUE: 제어함 
		if (g_MalwFind.DrvConfig.bGlobalCtrl)
		{
			Status = STATUS_ACCESS_DENIED;
			KdPrint(("Ret--STATUS_ACCESS_DENIED RegPath=%ws \n", RegPath.pBuffer));
		}			
	}
	FREE_N_REG_POOL( RegPath );	
	return Status;

}