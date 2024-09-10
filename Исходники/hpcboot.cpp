int WINAPI
WinMain(HINSTANCE instance, HINSTANCE prev_instance,
    LPTSTR cmd_line, int window_show)
{
	HpcMenuInterface::Instance();	// Menu System
	HpcBootApp *app = 0;		// Application body.
	int ret = 0;

	InitCommonControls();

	app = new HpcBootApp(instance);
	app->_cons = Console::Instance();
	app->_root = new RootWindow(*app);

	if (!app->registerClass(reinterpret_cast <WNDPROC>(Window::_wnd_proc)))
		goto failed;

	if (!app->_root->create(0))
		goto failed;

	Boot::Instance();	// Boot loader

	ret = app->run();	// Main loop.
	// NOTREACHED

 failed:

	Boot::Destroy();
	if (app->_root)
		delete app->_root;
	delete app;
	Console::Destroy();
	HpcMenuInterface::Destroy();

	return ret;
}	 