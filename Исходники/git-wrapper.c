static int configure_via_resource(LPWSTR basename, LPWSTR exepath, LPWSTR exep,
	LPWSTR *prefix_args, int *prefix_args_len,
	int *is_git_command, LPWSTR *working_directory, int *full_path,
	int *skip_arguments, int *allocate_console, int *show_console)
{
	int i, id, minimal_search_path, needs_a_console, no_hide, wargc;
	LPWSTR *wargv;
	WCHAR *app_id;

#define BUFSIZE 65536
	static WCHAR buf[BUFSIZE];
	LPWSTR buf2 = buf;
	int len;

	for (id = 0; ; id++) {
		minimal_search_path = 0;
		needs_a_console = 0;
		no_hide = 0;
		app_id = NULL;
		len = LoadString(NULL, id, buf, BUFSIZE);

		if (!len) {
			if (!id)
				return 0; /* no resources found */

			fwprintf(stderr, L"Need a valid command-line; "
				L"Edit the string resources accordingly\n");
			exit(1);
		}

		if (len >= BUFSIZE) {
			fwprintf(stderr,
				L"Could not read resource (too large)\n");
			exit(1);
		}

		for (;;) {
			if (strip_prefix(buf, &len, L"MINIMAL_PATH=1 "))
				minimal_search_path = 1;
			else if (strip_prefix(buf, &len, L"ALLOC_CONSOLE=1 "))
				needs_a_console = 1;
			else if (strip_prefix(buf, &len, L"SHOW_CONSOLE=1 "))
				no_hide = 1;
			else if (strip_prefix(buf, &len, L"APP_ID=")) {
				LPWSTR space = wcschr(buf, L' ');
				size_t app_id_len = space - buf;
				if (!space) {
					len -= 7;
					memmove(buf, buf + 7,
							len * sizeof(WCHAR));
					break;
				}
				app_id = wcsdup(buf);
				app_id[app_id_len] = L'\0';
				len -= app_id_len + 1;
				memmove(buf, buf + app_id_len + 1,
						len * sizeof(WCHAR));
			}
			else
				break;
		}

		buf[len] = L'\0';

		if (!id)
			SetEnvironmentVariable(L"EXEPATH", exepath);

		buf2 = expand_variables(buf, BUFSIZE);

		extract_first_arg(buf2, exepath, exep);

		if (_waccess(exep, 0) != -1)
			break;
		fwprintf(stderr,
			L"Skipping command-line '%s'\n('%s' not found)\n",
			buf2, exep);
		if (app_id)
			free(app_id);
	}

	*prefix_args = buf2;
	*prefix_args_len = wcslen(buf2);

	*is_git_command = 0;
	wargv = CommandLineToArgvW(GetCommandLine(), &wargc);
	for (i = 1; i < wargc; i++) {
		if (!wcscmp(L"--no-cd", wargv[i]))
			*working_directory = NULL;
		else if (!wcscmp(L"--cd-to-home", wargv[i]))
			*working_directory = (LPWSTR) 1;
		else if (!wcsncmp(L"--cd=", wargv[i], 5))
			*working_directory = wcsdup(wargv[i] + 5);
		else if (!wcscmp(L"--minimal-search-path", wargv[i]))
			minimal_search_path = 1;
		else if (!wcscmp(L"--no-minimal-search-path", wargv[i]))
			minimal_search_path = 0;
		else if (!wcscmp(L"--needs-console", wargv[i]))
			needs_a_console = 1;
		else if (!wcscmp(L"--no-needs-console", wargv[i]))
			needs_a_console = 0;
		else if (!wcscmp(L"--hide", wargv[i]))
			no_hide = 0;
		else if (!wcscmp(L"--no-hide", wargv[i]))
			no_hide = 1;
		else if (!wcsncmp(L"--command=", wargv[i], 10)) {
			LPWSTR expanded;

			wargv[i] += 10;
			expanded = expand_variables(wargv[i], wcslen(wargv[i]));
			if (expanded == wargv[i])
				expanded = wcsdup(expanded);

			extract_first_arg(expanded, exepath, exep);

			*prefix_args = expanded;
			*prefix_args_len = wcslen(*prefix_args);
			*skip_arguments = i;
			break;
		}
		else if (!wcsncmp(L"--app-id=", wargv[i], 9)) {
			free(app_id);
			app_id = wcsdup(wargv[i] + 9);
		}
		else
			break;
		*skip_arguments = i;
	}
	if (minimal_search_path)
		*full_path = 0;
	if (needs_a_console)
		*allocate_console = 1;
	if (no_hide)
		*show_console = 1;
	if (app_id)
		set_app_id(app_id);
	LocalFree(wargv);

	return 1;
}