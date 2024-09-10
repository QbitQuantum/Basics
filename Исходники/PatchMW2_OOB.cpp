void PatchMW2_OOB()
{
	if(version == 159)
	{
		// client-side OOB handler
		*(int*)0x65E454 = ((DWORD)CL_DeployOOBStub) - 0x65E452 - 6;
	}
	else
	{
		// client-side OOB handler
		*(int*)0x65BCE4 = ((DWORD)CL_DeployOOBStub) - 0x65BCE2 - 6;

		gsrCmpHookLoc = 0x65BCD8;
	}

	gsrCmpHook.initialize(gsrCmpHookLoc, GsrCmpHookStub);
	gsrCmpHook.installHook();
}