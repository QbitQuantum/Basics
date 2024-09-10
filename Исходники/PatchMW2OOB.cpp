void PatchMW2_OOB()
{
	// maximum size in NET_OutOfBandPrint
	*(DWORD*)0x4AEF08 = 0x1FFFC;
	*(DWORD*)0x4AEFA3 = 0x1FFFC;

	// client-side OOB handler
	*(int*)0x5AA715 = ((DWORD)CL_DeployOOBStub) - 0x5AA713 - 6;

	gsrCmpHook.initialize(gsrCmpHookLoc, GsrCmpHookStub);
	gsrCmpHook.installHook();
}