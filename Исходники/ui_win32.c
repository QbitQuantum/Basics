int APIENTRY
WinMain(HINSTANCE hInstance1,
	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    static char name0[256];
    static char *argv[256];
    int argc = 1;
    int i;

    GetModuleFileName(hInstance1, name0, 256);
    /* Allocate everything virtually - be on the safe side */
    argv[0] = strdup(name0);
    lpCmdLine = strdup(lpCmdLine);

    for (i = 0; lpCmdLine[i]; i++) {
	if (lpCmdLine[i] == ' ' || lpCmdLine[i] == '\t')
	    lpCmdLine[i] = 0;
	else if (!i || !lpCmdLine[i - 1])
	    argv[argc] = lpCmdLine + i, argc++;
    }

    /* Attach to parent console if available so output will be visible */
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
	/* make sure stdout is not already redirected before redefining */
	if (_fileno(stdout) == -1 || _get_osfhandle(fileno(stdout)) == -1)
	    freopen("CON", "w", stdout);
    }

    hInstance = hInstance1;
    return XaoS_main(argc, argv);
}