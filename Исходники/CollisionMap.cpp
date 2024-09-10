BOOL CCollisionMap::RemoveRoomData(DWORD LevelNo, DWORD x, DWORD y)
{
	BYTE AsmStub[] = {
	0x68, 00,00,00,00, // Pushing the pAct to the Stack
	0x68, 00,00,00,00, // Pushing the LevelId to the Stack
	0x68, 00,00,00,00, // Pushing the xPos to the Stack
	0x68, 00,00,00,00, // Pushing the yPos to the Stack
	0x68, 00,00,00,00, // Pushing the pRoom to the Stack
	0xB8, 00,00,00,00, // MOV EAX, 0x00
	0xFF, 0xD0,		   // Call Eax
	0xC3,
	};

	*(DWORD*)&AsmStub[1] = PlayerInfo.dwRoomAddr;
	*(DWORD*)&AsmStub[6] = y;
	*(DWORD*)&AsmStub[11] = x;
	*(DWORD*)&AsmStub[16] = LevelNo;
	*(DWORD*)&AsmStub[21] = PlayerInfo.dwActAddr;
	*(DWORD*)&AsmStub[26] = CCollisionMap::DLLInfo.D2Common + 0x56830;

	LPVOID Address = VirtualAllocEx(Memory.WindowHandle, NULL, sizeof(AsmStub), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	Memory.WriteMemory((DWORD)Address,AsmStub,sizeof(AsmStub));
	HANDLE pHandle = CreateRemoteThread(Memory.WindowHandle,NULL,sizeof(DWORD),(LPTHREAD_START_ROUTINE)Address,NULL,NULL,NULL);
	WaitForSingleObject(pHandle,INFINITE);
	CloseHandle(pHandle);
	VirtualFreeEx(Memory.WindowHandle,(LPVOID)Address,sizeof(AsmStub),MEM_RELEASE);

	return TRUE;
}