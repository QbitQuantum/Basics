ULONG
WSARecvFromDecode(
	IN PBTR_FILTER_RECORD Record,
	IN ULONG MaxCount,
	OUT PWCHAR Buffer
	)
{
	PSK_WSARECVFROM Data;
	CHAR Address[MAX_PATH];

	if (Record->ProbeOrdinal != _WSARecvFrom) {
		return S_FALSE;
	}	

	Data = (PSK_WSARECVFROM)Record->Data;

	if (Data->lpFrom) {
		StringCchPrintfA(Address, MAX_PATH - 1, "%S:%d", 
			inet_ntoa(Data->Address.sin_addr), ntohs(Data->Address.sin_port));
	} else {
		Address[0] = 0;
	}

	StringCchPrintf(Buffer, MaxCount - 1, 
		L"socket=%d, lpBuffers=0x%p, lpNumberOfBytesRecvd=0x%p (%d), lpFlags=0x%p (%d),"
		L"lpFrom=0x%p (%S), lpFromLen=0x%p (%d), lpOverlapped=0x%p, lpCompletionRoutine=0x%p, return=%d, LastErrorStatus=0x%08x",
		Data->sk, Data->lpBuffer, Data->lpNumberOfBytesRecvd, Data->NumberOfBytesRecvd, 
		Data->lpFlags, Data->Flags, Data->lpFrom, Address, Data->lpFromLen, Data->AddressLength,
		Data->lpOverlapped, Data->lpCompletionRoutine, Data->ReturnValue, Data->Status);

	return S_OK;
}