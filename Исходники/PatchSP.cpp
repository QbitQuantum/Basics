void PatchSP()
{
        // cg_fov unprotect
        *(DWORD*)0x4A3921 = DVAR_ARCHIVE;

        // small fix for infinite waiting for other players
        *(BYTE*)0x5026BC = 0x0;
        
        // function changes
        Com_Error = (Com_Error_t)0x651D90;
		Com_Printf = (Com_Printf_t)0x43BF30;

        // disable bandwidth testing / better match finding
        *(WORD*)0x693842 = 0x9090;
		
		// enable console (normally this check is !monkeytoy || blah; now it's only 'blah'
        *(BYTE*)0x58761C = 0xEB;

        // console toggling
        toggleConsoleHook1.initialize("", (PBYTE)toggleConsoleHook1Loc);
        toggleConsoleHook1.installHook((void(*)())Con_ToggleConsole, false);

        toggleConsoleHook2.initialize("", (PBYTE)toggleConsoleHook2Loc);
        toggleConsoleHook2.installHook((void(*)())Con_ToggleConsole, false);

        // player_sustainAmmo re-adding
        sustainAmmoHook.initialize("", 7, (PBYTE)sustainAmmoHookLoc);
        sustainAmmoHook.installHook(SustainAmmoHookFunc, true, false);
        
        // cg_drawVersion
        *(BYTE*)0x4A3D46 = 1; // default
        *(BYTE*)0x4A3D44 = 0x50; // flags
		
        // y 450, x 10
        *(DWORD*)0x4A3D7A = (DWORD)&drawVersionX;
        *(DWORD*)0x4A3DAF = (DWORD)&drawVersionY;

        *(DWORD*)0x9A33FC = (DWORD)customTimeBeginPeriod;

        // set port to 28960
        *(DWORD*)0x52E1D5 = 28960;

        // disable UPnP
        //*(WORD*)0x973C6B = 0x9090;

        // remove the windows hook setting function
        //*(BYTE*)0x8683D0 = 0xC3;

        // con stuff
        *(WORD*)0x79E6E5 = 0x9090; // dvar set 1

        *(BYTE*)0x5119B0 = 0xC3;   // dvar reset flag
        *(WORD*)0x4A87EB = 0x9090; // dvar exec
        *(WORD*)0x829CBE = 0x9090; // cmd  exec
        *(WORD*)0x5F5D4E = 0x9090; // dvar enum
        *(WORD*)0x610A94 = 0x9090; // cmd  enum

        windowedWindowStyleHook.initialize("aaaaa", 5, (PBYTE)windowedWindowStyleHookLoc);
        windowedWindowStyleHook.installHook(WindowedWindowStyleHookStub, false, false);

        // gethostbyname
        *(DWORD*)0x9A3470 = (DWORD)custom_gethostbyname;

        // small fix for infinite waiting for other players
        *(BYTE*)0x5026BC = 0x03;
}