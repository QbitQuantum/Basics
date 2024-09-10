void PatchMW2_Branding()
{
	#ifdef IW4M_OLD_CODE
	// displayed build tag in UI code
	*(DWORD*)0x43F73B = (DWORD)VERSIONSTRING;

	// console '%s: %s> ' string
	*(DWORD*)0x5A44B4 = (DWORD)(VERSIONSTRING "> ");

	// console version string
	//*(DWORD*)0x4B12BB = (DWORD)(VERSIONSTRING " " BUILDHOST " (built " __DATE__ " " __TIME__ ")");

	// version string
	*(DWORD*)0x60BD56 = (DWORD)(VERSIONSTRING " (built " __DATE__ " " __TIME__ ")");

	// set fs_basegame to 'm2demo' (will apply before fs_game, unlike the above line)
	*(DWORD*)0x6431D1 = (DWORD)"m2demo";

	// increase font sizes for chat on higher resolutions
	static float float13 = 13.0f;
	static float float10 = 10.0f;
	*(float**)0x5814AE = &float13;
	*(float**)0x5814C8 = &float10;
	#endif

	#ifndef IW4M_OLD_CODE
	drawDevStuffHook.initialize(drawDevStuffHookLoc, DrawDevStuffHookStub);
	drawDevStuffHook.installHook();

	// createwindowexa on winconsole
	static DWORD wcCWEx = (DWORD)CreateWindowExAWrap_WC;
	static DWORD wcGEx = (DWORD)CreateWindowExAWrap_G;
	*(DWORD**)0x4289CA = &wcCWEx;
	*(DWORD**)0x5076AC = &wcGEx;

	// displayed build tag in UI code
	*(DWORD*)0x43F73B = (DWORD)VERSIONSTRING;

	// console '%s: %s> ' string
	*(DWORD*)0x5A44B4 = (DWORD)("W2 MP> ");

	// console version string
	*(DWORD*)0x4B12BB = (DWORD)(VERSIONSTRING " " BUILDHOST " (built " __DATE__ " " __TIME__ ")");

	// version string
	*(DWORD*)0x60BD56 = (DWORD)(VERSIONSTRING " (built " __DATE__ " " __TIME__ ")");

	// add 'm2demo' game folder
	//customSearchPathHook.initialize(5, (PBYTE)customSearchPathHookLoc);
	//customSearchPathHook.installHook(CustomSearchPathStuff, true, false);

	// set fs_basegame to 'm2demo' (will apply before fs_game, unlike the above line)
	*(DWORD*)0x6431D1 = (DWORD)"GameData/ShipFiles";

	// main to GameData/VendorPaks
	*(DWORD*)0x461A84 = (DWORD)"GameData/VendorPaks";
	*(DWORD*)0x4825A9 = (DWORD)"GameData/VendorPaks";
	*(DWORD*)0x48265A = (DWORD)"GameData/VendorPaks";
	*(DWORD*)0x4290C2 = (DWORD)"GameData/VendorPaks";

	// players -> UserData
	*(DWORD*)0x47DCB6 = (DWORD)"UserData";
	*(DWORD*)0x482410 = (DWORD)"UserData";
	*(DWORD*)0x60B1E2 = (DWORD)"UserData";
	*(DWORD*)0x5AE106 = (DWORD)"UserData";
	*(DWORD*)0x642E8F = (DWORD)"UserData";
	*(DWORD*)0x682F76 = (DWORD)"UserData";

	// devraw -> DevData/devraw, and similar
	*(DWORD*)0x4823D7 = (DWORD)"DevData/devraw";
	*(DWORD*)0x4823C4 = (DWORD)"DevData/devraw_shared";
	*(DWORD*)0x4823EA = (DWORD)"DevData/raw_shared";
	*(DWORD*)0x4823FD = (DWORD)"DevData/raw";

	// video file path
	*(DWORD*)0x51C2A4 = (DWORD)"%s\\GameData\\Videos\\%s.bik";

	// always play the intro video
	nop(0x60BECF, 2);

	*(DWORD*)0x60BED2 = (DWORD)"unskippablecinematic fdoLogo\n";

	// increase font sizes for chat on higher resolutions
	//*(BYTE*)0x5814AA = 0xEB;
	//*(BYTE*)0x5814C4 = 0xEB;
	static float float13 = 10.0f;
	static float float10 = 7.0f;

	*(float**)0x5814AE = &float13;
	*(float**)0x5814C8 = &float10;

	// safe areas; set to 1 (changing the dvar has no effect later on as the ScrPlace viewport is already made)
	static float float1 = 1.0f;
	*(float**)0x42E3A8 = &float1;
	*(float**)0x42E3D9 = &float1;

	// related to above: default cg_debugInfoCornerOffset to 0 0 instead of 0 -30
	static float float0 = 0.0f;

	*(float**)0x4F8FDB = &float0;

	// always assume a localized pak file is english
	*(BYTE*)0x4D11F3 = 0xEB;
	#endif

#ifdef PRE_RELEASE_DEMO
	// disable private parties if demo
	//*(DWORD*)0x40554E = (DWORD)CL_XStartPrivateMatch_f;
	//*(DWORD*)0x5A992E = (DWORD)CL_XStartPrivateMatch_f;
	//*(DWORD*)0x4058B9 = (DWORD)CL_XStartPrivateMatch_f; // xpartygo
	//*(DWORD*)0x4152AA = (DWORD)CL_XStartPrivateMatch_f; // map

	// use M2 playlists
	strcpy((char*)0x6EE7AC, "mp_playlists_m2");
	*(DWORD*)0x4D47FB = (DWORD)"mp_playlists_m2.ff";
#endif
}