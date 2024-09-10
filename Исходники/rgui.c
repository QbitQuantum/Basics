int AppMain(int argc, char **argv)
{
    CharacterMode = RGui;
    if(strcmp(getDLLVersion(), getRVersion()) != 0) {
	MessageBox(0, "R.DLL version does not match", "Terminating",
		   MB_TASKMODAL | MB_ICONSTOP | MB_OK);
	exit(1);
    }
    cmdlineoptions(argc, argv);
    if (!setupui()) {
        MessageBox(0, "Error setting up console.  Try --vanilla option.",
                      "Terminating", MB_TASKMODAL | MB_ICONSTOP | MB_OK);
        GA_exitapp();
    }

/* C writes to stdout/stderr get set to the launching terminal (if
   there was one).  Needs XP, and works for C but not Fortran. */

    if (AttachConsole(ATTACH_PARENT_PROCESS))
    {
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
    }

    Rf_mainloop();
    /* NOTREACHED */
    return 0;
}