	platform_spec::platform_spec()
	{
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
		if(!IsWindowsVistaOrGreater())
			metrics.cbSize -= sizeof(metrics.iPaddedBorderWidth);
#endif
#endif
		::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof metrics, &metrics, 0);
		def_font_ptr_ = make_native_font(to_utf8(metrics.lfMessageFont.lfFaceName).c_str(), font_size_to_height(9), 400, false, false, false);
	}