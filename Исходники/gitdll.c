int git_init()
{
	char path[MAX_PATH+1];
	size_t homesize;

	_fmode = _O_BINARY;
	_setmode(_fileno(stdin), _O_BINARY);
	_setmode(_fileno(stdout), _O_BINARY);
	_setmode(_fileno(stderr), _O_BINARY);

	// set HOME if not set already
	getenv_s(&homesize, NULL, 0, "HOME");
	if (!homesize)
	{
		_wputenv_s(L"HOME", wget_windows_home_directory());
	}
	GetModuleFileName(NULL, path, MAX_PATH);
	convert_slash(path);

	git_extract_argv0_path(path);
	reset_git_env();
	g_prefix = setup_git_directory();
	git_config(git_default_config, NULL);

	if (!homesize)
	{
		_putenv_s("HOME","");/* clear home evironment to avoid affact third part software*/
	}

	return 0;
}