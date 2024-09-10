void
TclpSetVariables(
    Tcl_Interp *interp)		/* Interp to initialize. */
{
    const char *ptr;
    char buffer[TCL_INTEGER_SPACE * 2];
    SYSTEM_INFO sysInfo, *sysInfoPtr = &sysInfo;
    OemId *oemId;
    OSVERSIONINFOA osInfo;
    Tcl_DString ds;
    WCHAR szUserName[UNLEN+1];
    DWORD cchUserNameLen = UNLEN;

    Tcl_SetVar2Ex(interp, "tclDefaultLibrary", NULL,
	    TclGetProcessGlobalValue(&defaultLibraryDir), TCL_GLOBAL_ONLY);

    osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
    GetVersionExA(&osInfo);

    oemId = (OemId *) sysInfoPtr;
    GetSystemInfo(&sysInfo);

    /*
     * Define the tcl_platform array.
     */

    Tcl_SetVar2(interp, "tcl_platform", "platform", "windows",
	    TCL_GLOBAL_ONLY);
    if (osInfo.dwPlatformId < NUMPLATFORMS) {
	Tcl_SetVar2(interp, "tcl_platform", "os",
		platforms[osInfo.dwPlatformId], TCL_GLOBAL_ONLY);
    }
    wsprintfA(buffer, "%d.%d", osInfo.dwMajorVersion, osInfo.dwMinorVersion);
    Tcl_SetVar2(interp, "tcl_platform", "osVersion", buffer, TCL_GLOBAL_ONLY);
    if (oemId->wProcessorArchitecture < NUMPROCESSORS) {
	Tcl_SetVar2(interp, "tcl_platform", "machine",
		processors[oemId->wProcessorArchitecture],
		TCL_GLOBAL_ONLY);
    }

#ifdef _DEBUG
    /*
     * The existence of the "debug" element of the tcl_platform array
     * indicates that this particular Tcl shell has been compiled with debug
     * information. Using "info exists tcl_platform(debug)" a Tcl script can
     * direct the interpreter to load debug versions of DLLs with the load
     * command.
     */

    Tcl_SetVar2(interp, "tcl_platform", "debug", "1",
	    TCL_GLOBAL_ONLY);
#endif

    /*
     * Set up the HOME environment variable from the HOMEDRIVE & HOMEPATH
     * environment variables, if necessary.
     */

    Tcl_DStringInit(&ds);
    ptr = Tcl_GetVar2(interp, "env", "HOME", TCL_GLOBAL_ONLY);
    if (ptr == NULL) {
	ptr = Tcl_GetVar2(interp, "env", "HOMEDRIVE", TCL_GLOBAL_ONLY);
	if (ptr != NULL) {
	    Tcl_DStringAppend(&ds, ptr, -1);
	}
	ptr = Tcl_GetVar2(interp, "env", "HOMEPATH", TCL_GLOBAL_ONLY);
	if (ptr != NULL) {
	    Tcl_DStringAppend(&ds, ptr, -1);
	}
	if (Tcl_DStringLength(&ds) > 0) {
	    Tcl_SetVar2(interp, "env", "HOME", Tcl_DStringValue(&ds),
		    TCL_GLOBAL_ONLY);
	} else {
	    Tcl_SetVar2(interp, "env", "HOME", "c:\\", TCL_GLOBAL_ONLY);
	}
    }

    /*
     * Initialize the user name from the environment first, since this is much
     * faster than asking the system.
     * Note: cchUserNameLen is number of characters including nul terminator.
     */

    Tcl_DStringInit(&ds);
    if (TclGetEnv("USERNAME", &ds) == NULL) {
	if (tclWinProcs->getUserName((LPTSTR)szUserName, &cchUserNameLen) != 0) {
	    int cbUserNameLen = cchUserNameLen - 1;
	    if (tclWinProcs->useWide) cbUserNameLen *= sizeof(WCHAR);
	    Tcl_WinTCharToUtf((LPTSTR)szUserName, cbUserNameLen, &ds);
	}
    }
    Tcl_SetVar2(interp, "tcl_platform", "user", Tcl_DStringValue(&ds),
	    TCL_GLOBAL_ONLY);
    Tcl_DStringFree(&ds);

    /*
     * Define what the platform PATH separator is. [TIP #315]
     */

    Tcl_SetVar2(interp, "tcl_platform","pathSeparator", ";", TCL_GLOBAL_ONLY);
}