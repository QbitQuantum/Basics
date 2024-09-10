MODULE MODULE_EXPORT int
install_hook(const char *ga_root, const char *config, const char *app_exe)
{
	char s_drive[_MAX_DRIVE], s_dir[_MAX_DIR], s_fname[_MAX_FNAME];
	
	if(ga_root == NULL || config == NULL) {
		ga_error("[install_hook] no ga-root nor configuration were specified.\n");
		return -1;
	}
	
	_splitpath(app_exe, s_drive, s_dir, s_fname, NULL);
#if 0
	if(strncpy(g_appexe, s_fname, sizeof(g_appexe)) < 0)
		return -1;
	if(strncpy(g_root, ga_root, sizeof(g_root)) < 0)
		return -1;
	if(strncpy(g_confpath, config, sizeof(g_confpath)) < 0)
		return -1;
#endif
	_putenv_s("GA_APPEXE", s_fname);
	_putenv_s("GA_ROOT", ga_root);
	_putenv_s("GA_CONFIG", config);
	
	if((gHook = SetWindowsHookEx(WH_CBT, hook_proc, hInst, 0)) == NULL) {
		ga_error("SetWindowsHookEx filaed (0x%08x)\n", GetLastError());
		return -1;
	}

	ga_error("[install_hook] success.\n");
	
	return 0;
}