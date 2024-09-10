	double platform_abstraction::font_default_pt()
	{
#ifdef NANA_WINDOWS
		//Create default font object.
		NONCLIENTMETRICS metrics = {};
		metrics.cbSize = sizeof metrics;
#if(WINVER >= 0x0600)
#if defined(NANA_MINGW)
		OSVERSIONINFO osvi = {};
		osvi.dwOSVersionInfoSize = sizeof(osvi);
		::GetVersionEx(&osvi);
		if (osvi.dwMajorVersion < 6)
			metrics.cbSize -= sizeof(metrics.iPaddedBorderWidth);
#else
		if (!IsWindowsVistaOrGreater())
			metrics.cbSize -= sizeof(metrics.iPaddedBorderWidth);
#endif
#endif
		::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof metrics, &metrics, 0);

		auto desktop = ::GetDC(nullptr);
		auto pt = std::abs(metrics.lfMessageFont.lfHeight) * 72.0 / ::GetDeviceCaps(desktop, LOGPIXELSY);
		::ReleaseDC(nullptr, desktop);
		return pt;
#else
		return 10;
#endif
	}