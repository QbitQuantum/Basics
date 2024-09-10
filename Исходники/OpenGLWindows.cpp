/**
 * Resize the GL context.
 */
void PlatformResizeGLContext( FPlatformOpenGLDevice* Device, FPlatformOpenGLContext* Context, uint32 SizeX, uint32 SizeY, bool bFullscreen, bool bWasFullscreen, GLenum BackBufferTarget, GLuint BackBufferResource)
{
	FScopeLock ScopeLock(Device->ContextUsageGuard);
{
	uint32 WindowStyle = WS_CAPTION | WS_SYSMENU;
	uint32 WindowStyleEx = 0;
	HWND InsertAfter = HWND_NOTOPMOST;

	if (bFullscreen)
	{
		// Get the monitor info from the window handle.
		HMONITOR hMonitor = MonitorFromWindow(Context->WindowHandle, MONITOR_DEFAULTTOPRIMARY);
		MONITORINFOEX MonitorInfo;
		memset(&MonitorInfo, 0, sizeof(MONITORINFOEX));
		MonitorInfo.cbSize = sizeof(MONITORINFOEX);
		GetMonitorInfo(hMonitor, &MonitorInfo);

		DEVMODE Mode;
		Mode.dmSize = sizeof(DEVMODE);
		Mode.dmBitsPerPel = 32;
		Mode.dmPelsWidth = SizeX;
		Mode.dmPelsHeight = SizeY;
		Mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Turn on fullscreen mode for the current monitor
		ChangeDisplaySettingsEx(MonitorInfo.szDevice, &Mode, NULL, CDS_FULLSCREEN, NULL);

		WindowStyle = WS_POPUP;
		WindowStyleEx = WS_EX_APPWINDOW | WS_EX_TOPMOST;
		InsertAfter = HWND_TOPMOST;
	}
	else if (bWasFullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	//SetWindowLong(Context->WindowHandle, GWL_STYLE, WindowStyle);
	//SetWindowLong(Context->WindowHandle, GWL_EXSTYLE, WindowStyleEx);

		{
			FScopeContext ScopeContext(Context);

			if (Context->ViewportFramebuffer == 0)
			{
				glGenFramebuffers(1, &Context->ViewportFramebuffer);
			}
			glBindFramebuffer(GL_FRAMEBUFFER, Context->ViewportFramebuffer);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, BackBufferTarget, BackBufferResource, 0);
#if UE_BUILD_DEBUG
			glReadBuffer(GL_COLOR_ATTACHMENT0);
			glDrawBuffer(GL_COLOR_ATTACHMENT0);
#endif
			FOpenGL::CheckFrameBuffer();

			glViewport(0, 0, SizeX, SizeY);
			static GLfloat ZeroColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			glClearBufferfv(GL_COLOR, 0, ZeroColor );
		}
	}
}