VOID OnProcessQuit(HANDLE ParentId, HANDLE ProcessId, BOOLEAN Create)
{
	if(Create == TRUE)
	{
		PEPROCESS  p=PsGetCurrentProcess();
		
		ANSI_STRING ascallCode;
		RtlInitAnsiString(&ascallCode,(char *)p+g_processNameOffset);
		UNICODE_STRING  uni;
		RtlAnsiStringToUnicodeString(&uni,&ascallCode,true);	
		_wcslwr(uni.Buffer);

		if(RtlCompareMemory(BEGINOPERATEREG,uni.Buffer,uni.Length))
		{		
			if(SetReg(AUTORUN,REGNAME) == false)
				WriteSysLog(LOG_TYPE_DEBUG,L" is userinital create reg : %s","error");
		}
		RtlFreeUnicodeString(&uni);
		return;
	}
    

	kdP(("OnProcessQuit \n"));
	
	if(IsProcessProtected((ULONG)ProcessId))
		RemoveProtectPID((ULONG)ProcessId);
}