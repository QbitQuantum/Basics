static void attach_parent_console()
{
	BOOL outRedirected, errRedirected;

	outRedirected = IsHandleRedirected(STD_OUTPUT_HANDLE);
	errRedirected = IsHandleRedirected(STD_ERROR_HANDLE);

	if (outRedirected && errRedirected) {
		/* Both standard output and error handles are redirected.
		 * There is no point in attaching to parent process console.
		 */
		return;
	}

	if (AttachConsole(ATTACH_PARENT_PROCESS) == 0) {
		/* Console attach failed. */
		return;
	}

	/* Console attach succeeded */
	if (outRedirected == FALSE) {
		freopen("CONOUT$", "w", stdout);
	}

	if (errRedirected == FALSE) {
		freopen("CONOUT$", "w", stderr);
	}
}