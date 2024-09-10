static void
parse_recieved_arguments(char *args[])
{
	char lwin_path[PATH_MAX] = "";
	char rwin_path[PATH_MAX] = "";
	int lwin_handle = 0, rwin_handle = 0;
	int argc = 0;

	while(args[argc] != NULL)
	{
		argc++;
	}

	parse_args(argc, args, args[0], lwin_path, rwin_path, &lwin_handle,
			&rwin_handle);
	exec_startup_commands(argc, args);

	if(get_mode() != NORMAL_MODE && get_mode() != VIEW_MODE)
	{
		return;
	}

#ifdef _WIN32
	SwitchToThisWindow(GetConsoleWindow(), TRUE);
	BringWindowToTop(GetConsoleWindow());
	SetForegroundWindow(GetConsoleWindow());
#endif

	if(view_needs_cd(&lwin, lwin_path))
	{
		remote_cd(&lwin, lwin_path, lwin_handle);
	}

	if(view_needs_cd(&rwin, rwin_path))
	{
		remote_cd(&rwin, rwin_path, rwin_handle);
	}

	if(lwin_path[0] != '\0' && rwin_path[0] == '\0' && curr_view != &lwin)
	{
		change_window();
	}

	clean_status_bar();
	curr_stats.save_msg = 0;
}