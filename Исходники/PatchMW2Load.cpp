void PatchMW2_Load()
{
	// rawfile moddability
	rawFileHook1.initialize(rawFileHook1Loc, LoadModdableRawfileStub);
	rawFileHook1.installHook();

	rawFileHook2.initialize(rawFileHook2Loc, LoadModdableRawfileStub);
	rawFileHook2.installHook();

	rawFileHook3.initialize(rawFileHook3Loc, LoadModdableRawfileStub);
	rawFileHook3.installHook();

	rawFileHook4.initialize(rawFileHook4Loc, LoadModdableRawfileStub2);
	rawFileHook4.installHook();

	rawFileHook5.initialize(rawFileHook5Loc, LoadModdableRawfileStub);
	rawFileHook5.installHook();

	rawFileHook6.initialize(rawFileHook6Loc, LoadModdableRawfileStub);
	rawFileHook6.installHook();

	rawFileHook7.initialize(rawFileHook7Loc, LoadModdableRawfileStub);
	rawFileHook7.installHook();

	rawFileHook8.initialize(rawFileHook8Loc, LoadModdableRawfileStub);
	rawFileHook8.installHook();

	//rawFileHook9.initialize(rawFileHook9Loc, LoadModdableRawfileStub);
	//rawFileHook9.installHook();

	//rawFileHook10.initialize(rawFileHook10Loc, LoadModdableRawfileStub);
	//rawFileHook10.installHook();

	// fastfile loading hooks
	uiLoadHook1.initialize(uiLoadHook1Loc, UILoadHook1Stub);
	uiLoadHook1.installHook();

	ffLoadHook1.initialize(ffLoadHook1Loc, FFLoadHook1Stub);
	ffLoadHook1.installHook();

	ffLoadHook2.initialize(ffLoadHook2Loc, FFLoadHook2Stub);
	ffLoadHook2.installHook();

	zoneLoadHook1.initialize(zoneLoadHook1Loc, ZoneLoadHook1Stub);
	zoneLoadHook1.installHook();

	zoneLoadHook2.initialize(zoneLoadHook2Loc, ZoneLoadHook2Stub);
	zoneLoadHook2.installHook();

	getZoneRootHook.initialize(getZoneRootHookLoc, GetZoneRootHookFunc);
	getZoneRootHook.installHook();

	// disable 'ignoring asset' notices
	memset((void*)0x5BB902, 0x90, 5);

	// ignore 'no iwd files found in main'
	memset((void*)0x642A4B, 0x90, 5);

	if (strstr(GetCommandLine(), "fs_cdpath") != NULL)
	{
		// fs_basepath for 'players' -> fs_cdpath
		*(DWORD*)0x482408 = 0x63D0BB0;
	}

	// zone folders -> remove absolute stuff
	zoneTestHook.initialize(zoneTestHookLoc, ZoneTestHookFunc);
	zoneTestHook.installHook();

	zoneSprintfHook.initialize(zoneSprintfHookLoc, ZoneSprintfHookFunc);
	zoneSprintfHook.installHook();
}