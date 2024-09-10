void PatchMW2_Stats()
{
	writeStatsHook.initialize(writeStatsHookLoc, WriteStatsHookStub);
	writeStatsHook.installHook();

	loadOldStatsHook.initialize(loadOldStatsHookLoc, LoadOldStatsHookFunc);
	loadOldStatsHook.installHook();

	readStatsHook.initialize(readStatsHookLoc, ReadStatsHookStub);
	readStatsHook.installHook();

	// make statWriteNeeded ignored (kill stat saving?)
	//*(BYTE*)0x424BD0 = 0xEB;
}