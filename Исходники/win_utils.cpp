bool Win32_ChangeDisplayMode (const Win32_DisplayMode *displayMode)
{
	if (!displayMode)
	{
		return ::ChangeDisplaySettingsA (NULL, NULL) == DISP_CHANGE_SUCCESSFUL;
	}

	if (displayMode->width && displayMode->height)
	{
		if (displayMode->width != g_desktopDisplayMode.width || displayMode->height != g_desktopDisplayMode.height || displayMode->bpp != g_desktopDisplayMode.bpp)
		{
			DEVMODE mode;
			DEVMODE sel;
			int i = 0;
			memset(&sel, 0, sizeof(sel));

			while ( ::EnumDisplaySettings(0, i++, &mode))
			{
				if ( mode.dmPelsWidth == displayMode->width && mode.dmPelsHeight == displayMode->height)
				{
					if (mode.dmBitsPerPel < displayMode->bpp)
					{
						continue;
					}

					if (mode.dmDisplayFrequency >= sel.dmDisplayFrequency)
					{
						sel = mode;
					}

					if (mode.dmBitsPerPel > sel.dmBitsPerPel)
					{
						sel = mode;
					}
				}
			}

			if (sel.dmPelsWidth == 0)
			{
				return false;
			}

			sel.dmSize = sizeof(sel);
			sel.dmDriverExtra = 0;
			sel.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

			if ( DISP_CHANGE_SUCCESSFUL != ChangeDisplaySettings(&sel, CDS_FULLSCREEN | CDS_SET_PRIMARY))
			{
				sel.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

				if ( DISP_CHANGE_SUCCESSFUL != ChangeDisplaySettingsA(&mode, CDS_FULLSCREEN | CDS_SET_PRIMARY))
				{
					return false;
				}
			}
		}

		return true;
	}

	return false;
}