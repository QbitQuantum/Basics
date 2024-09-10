const char *VideoDriver_Dedicated::Start(const char * const *parm)
{
	int bpp = BlitterFactory::GetCurrentBlitter()->GetScreenDepth();
	_dedicated_video_mem = (bpp == 0) ? NULL : MallocT<byte>(_cur_resolution.width * _cur_resolution.height * (bpp / 8));

	_screen.width  = _screen.pitch = _cur_resolution.width;
	_screen.height = _cur_resolution.height;
	_screen.dst_ptr = _dedicated_video_mem;
	ScreenSizeChanged();
	BlitterFactory::GetCurrentBlitter()->PostResize();

#if defined(WINCE)
	/* WinCE doesn't support console stuff */
#elif defined(WIN32)
	/* For win32 we need to allocate a console (debug mode does the same) */
	CreateConsole();
	CreateWindowsConsoleThread();
	SetConsoleTitle(_T("OpenTTD Dedicated Server"));
#endif

#ifdef _MSC_VER
	/* Disable the MSVC assertion message box. */
	_set_error_mode(_OUT_TO_STDERR);
#endif

#ifdef __OS2__
	/* For OS/2 we also need to switch to console mode instead of PM mode */
	OS2_SwitchToConsoleMode();
#endif

	DEBUG(driver, 1, "Loading dedicated server");
	return NULL;
}