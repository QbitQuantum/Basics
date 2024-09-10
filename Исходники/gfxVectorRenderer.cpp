static bool readDefaultFontFaceBytes(void** mem, size_t* size)
{
#if LOOM_PLATFORM == LOOM_PLATFORM_WIN32
	// Get Windows dir
	char windir[MAX_PATH];
	GetWindowsDirectoryA((LPSTR)&windir, MAX_PATH);

	// Load font file
	return readFontFile((utString(windir) + "\\Fonts\\arial.ttf").c_str(), mem, size) != 0;

	// Kept for future implementation of grabbing fonts by name
	/*
	SDL_SysWMinfo info;
	SDL_VERSION(&info.version);
	if (SDL_GetWindowWMInfo(gSDLWindow, &info)) {
	HWND windowHandle = info.info.win.window;
	HDC deviceContext = GetDC(windowHandle);
	DWORD size = GetFontData(deviceContext, 0, 0, NULL, 0);
	lmAssert(size != GDI_ERROR, "Font data retrieval failed: %d", GetLastError());
	}
	else {
	lmLogError(gGFXVectorRendererLogGroup, "Error retrieving window information: %s", SDL_GetError());
	}
	*/
#elif LOOM_PLATFORM == LOOM_PLATFORM_ANDROID
	return readFontFile("/system/fonts/DroidSans.ttf", mem, size) != 0;
#elif LOOM_PLATFORM == LOOM_PLATFORM_OSX
	return readFontFile("/Library/Fonts/Arial.ttf", mem, size) != 0;
#elif LOOM_PLATFORM == LOOM_PLATFORM_IOS
    return (bool)platform_fontSystemFontFromName("ArialMT", mem, (unsigned int*)size);
#else
	mem = NULL;
	size = 0;
#endif
}