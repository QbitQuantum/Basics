//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//beginPlugin
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int beginPlugin(HINSTANCE hMainInstance)
{
	if (plugin_hwnd_blackbox)
	{
		MessageBox(plugin_hwnd_blackbox, "Dont load me twice!", szAppName, MB_OK|MB_SETFOREGROUND);
		return 1;
	}

	//Deal with instances
	plugin_instance_plugin = hMainInstance;
	plugin_hwnd_blackbox = GetBBWnd();

	const char *bbv = GetBBVersion();
	if (0 == _memicmp(bbv, "bblean", 6)) BBVersion = BBVERSION_LEAN;
	else
	if (0 == _memicmp(bbv, "bb", 2)) BBVersion = BBVERSION_XOB;
	else BBVersion = BBVERSION_09X;

	//Deal with os info
	plugin_getosinfo();

#ifdef BBINTERFACE_ALPHA_SOFTWARE
	int result = BBMessageBox(plugin_hwnd_blackbox,
		"WARNING!\n\n"
		"This is ALPHA software! Use at your own risk!\n\n"
		"The authors are not responsible in the event that:\n - your configuration is lost,\n - your computer blows up,\n - you are hit by a truck, or\n - anything else at all.\n\n"
		"Do you wish to continue loading this ALPHA software?",
		"BBInterface ALPHA Warning",
		MB_ICONWARNING|MB_DEFBUTTON2|MB_YESNO);
	if (result != IDYES) return 0;
#endif

	//Startup
	plugin_load = true;
	plugin_startup();

	return 0;
}