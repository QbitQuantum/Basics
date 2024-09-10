void PatchMW2_RemoteConsoleServer()
{
	// maximum size in NET_OutOfBandPrint
	*(DWORD*)0x4AEF08 = 0x1FFFC;
	*(DWORD*)0x4AEFA3 = 0x1FFFC;

	// client-side OOB handler
	*(int*)0x5AA715 = ((DWORD)SVC_RemoteCommandStub) - 0x5AA713 - 6;

	gsrCmpHook.initialize((PBYTE)gsrCmpHookLoc);
	gsrCmpHook.installHook(GsrCmpHookStub, false);
}