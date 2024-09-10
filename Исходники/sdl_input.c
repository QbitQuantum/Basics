qboolean IN_InitRawMouse(void)
{
	// http://www.usb.org/developers/devclass_docs/Hut1_12.pdf
	if (!SDLWindowProc)
	{
		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);
		SDL_GetWMInfo(&wmInfo);
		SDLWindowProc = (WNDPROC)GetWindowLongPtr(wmInfo.window, GWLP_WNDPROC);
		SetWindowLongPtr(wmInfo.window, GWLP_WNDPROC, (LONG_PTR)RawWndProc);
	}

	{
		RAWINPUTDEVICE dev =
		{
			1,  // usUsagePage - generic desktop controls
			2,  // usUsage - mouse
			0,  // dwFlags
			0   // hwndTarget
		};
		if (!RegisterRawInputDevices(&dev, 1, sizeof(dev)))
		{
			Com_Printf("Raw input registration failed. (0x%lx)\n", GetLastError());
			return qfalse;
		}
	}
	Com_DPrintf("Registered for raw input.\n");
	mouseRaw = qtrue;
	return qtrue;
}