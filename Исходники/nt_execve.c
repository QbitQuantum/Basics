static int try_shell_ex(char *argv0, const char *const *argv, unsigned long shellexflags, char **cmdstr, unsigned int *cmdsize)
{
	char *cmdend;
	size_t cmdlen;
	SHELLEXECUTEINFO shinfo;
	BOOL nocmd = 0;

	path_to_backslash(argv0);

	/* @@@@ is this code really needed ? when ? */
	if ((!*argv) && (argv0[0] == '\\') && (argv0[1] == '\\')) {
		shellexflags |= SEE_MASK_CONNECTNETDRV;
		nocmd = 1;
		goto noargs;
	}

	cmdend = *cmdstr;
	cmdlen = 0;
	concat_args_and_quote(argv, cmdstr, &cmdlen, &cmdend, cmdsize);
	*cmdend = '\0';

noargs:
	dbgprintf(PR_EXEC, "ShellExecute(%s, ..) with cmdstr [%s]\n", argv0, *cmdstr);
	memset(&shinfo, 0, sizeof(shinfo));
	shinfo.cbSize = sizeof(shinfo);
	shinfo.fMask = SEE_MASK_FLAG_NO_UI | SEE_MASK_FLAG_DDEWAIT | shellexflags;
	shinfo.hwnd = NULL;
	shinfo.lpVerb = NULL;
	shinfo.lpFile = argv0;
	shinfo.lpParameters = nocmd ? NULL : *cmdstr;
	shinfo.lpDirectory = 0;
	shinfo.nShow = SW_SHOWDEFAULT;

	if (ShellExecuteEx(&shinfo)) {
		DWORD retval = 255;
		dbgprintf(PR_EXEC, "ShellExecute() created process handle 0x%p\n", shinfo.hProcess);
		/* may happen if "executing" a file associated to a running program, i.e.
		   "execute" a .html file with an already opened browser window */
		if (shinfo.hProcess != (HANDLE)0) {
			if (shellexflags & SEE_MASK_NOCLOSEPROCESS) {
				if ((intptr_t)(shinfo.hInstApp) > 32) {
					if (WaitForSingleObject(shinfo.hProcess, INFINITE) == WAIT_OBJECT_0) {
						/* try to get the return value */
						GetExitCodeProcess(shinfo.hProcess, &retval);
					} else {
						dbgprintf(PR_ERROR, "!!! ShellExecute() [%s] WaitForSingleObject() error %ld\n", argv0, GetLastError());
					}
				} else {
					dbgprintf(PR_ERROR, "!!! ShellExecute() [%s] error %p\n", argv0, shinfo.hInstApp);
				}
			}
			/* try to close, it may fail but .. what else could we do */
			CloseHandle(shinfo.hProcess);
		}
		dbgprintf(PR_ALL, "--- %s(): ShellExecute() OK, exiting with code %ld\n", __FUNCTION__, retval);
		exec_exit((int)retval);
	} else {
		dbgprintf(PR_EXEC, "ShellExecute() failed\n");
	}
       	return (0);
}