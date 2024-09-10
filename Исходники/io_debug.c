static int fork_and_ptraceme(RIO *io, int bits, const char *cmd) {
	PROCESS_INFORMATION pi;
	STARTUPINFO si = { 0 } ;
	DEBUG_EVENT de;
	int pid, tid;
	HANDLE th = INVALID_HANDLE_VALUE;
	if (!*cmd) {
		return -1;
	}
	setup_tokens ();
	char *_cmd = io->args ? r_str_appendf (strdup (cmd), " %s", io->args) :
		strdup (cmd);
	char **argv = r_str_argv (_cmd, NULL);
	// We need to build a command line with quoted argument and escaped quotes
	int cmd_len = 0;
	int i = 0;

	si.cb = sizeof (si);
	while (argv[i]) {
		char *current = argv[i];
		int quote_count = 0;
		while ((current = strchr (current, '"'))) {
			quote_count ++;
		}
		cmd_len += strlen (argv[i]);
		cmd_len += quote_count; // The quotes will add one backslash each
		cmd_len += 2; // Add two enclosing quotes;
		i++;
	}
	cmd_len += i-1; // Add argc-1 spaces

	char *cmdline = malloc ((cmd_len + 1) * sizeof (char));
	int cmd_i = 0; // Next character to write in cmdline
	i = 0;
	while (argv[i]) {
		if (i != 0) {
			cmdline[cmd_i++] = ' ';
		}
		cmdline[cmd_i++] = '"';

		int arg_i = 0; // Index of current character in orginal argument
		while (argv[i][arg_i]) {
			char c = argv[i][arg_i];
			if (c == '"') {
				cmdline[cmd_i++] = '\\';
			}
			cmdline[cmd_i++] = c;
			arg_i++;
		}

		cmdline[cmd_i++] = '"';
		i++;
	}
	cmdline[cmd_i] = '\0';

	LPTSTR appname_ = r_sys_conv_utf8_to_utf16 (argv[0]);
	LPTSTR cmdline_ = r_sys_conv_utf8_to_utf16 (cmdline);
	if (!CreateProcess (appname_, cmdline_, NULL, NULL, FALSE,
						 CREATE_NEW_CONSOLE | DEBUG_ONLY_THIS_PROCESS,
						 NULL, NULL, &si, &pi)) {
		r_sys_perror ("fork_and_ptraceme/CreateProcess");
		free (appname_);
		free (cmdline_);
		return -1;
	}
	free (appname_);
	free (cmdline_);
	free (cmdline);
	r_str_argv_free (argv);
	/* get process id and thread id */
	pid = pi.dwProcessId;
	tid = pi.dwThreadId;

	/* catch create process event */
	if (!WaitForDebugEvent (&de, 10000)) goto err_fork;

	/* check if is a create process debug event */
	if (de.dwDebugEventCode != CREATE_PROCESS_DEBUG_EVENT) {
		eprintf ("exception code 0x%04x\n", (ut32)de.dwDebugEventCode);
		goto err_fork;
	}

	if (th != INVALID_HANDLE_VALUE) {
		CloseHandle (th);
	}
	eprintf ("Spawned new process with pid %d, tid = %d\n", pid, tid);
	winbase = (ut64)de.u.CreateProcessInfo.lpBaseOfImage;
	wintid = tid;
	return pid;

err_fork:
	eprintf ("ERRFORK\n");
	TerminateProcess (pi.hProcess, 1);
	if (th != INVALID_HANDLE_VALUE) CloseHandle (th);
	return -1;
}