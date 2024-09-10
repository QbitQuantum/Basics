LRESULT DeskBandWindow::OnPaint(const HDC hdcIn)
{
	if (mHwnd == NULL) return 0;
	HDC hdc = hdcIn;
	PAINTSTRUCT ps;

	if (!hdc)
	{
		hdc = BeginPaint(mHwnd, &ps);
	}

	if (hdc)
	{
		RECT rc;
		GetClientRect(mHwnd, &rc);

		if (m_fCompositionEnabled)
		{		
			HTHEME hTheme;
			if (ThemeReady)
			{
				ZeroMemory(CurrentTheme, sizeof(CurrentTheme));
				wcscat(CurrentTheme, Theme);
				wcscat(CurrentTheme, Toolbar);
				hTheme = OpenThemeData(mHwnd, CurrentTheme);
			}
			else
			{
				hTheme = OpenThemeData(mHwnd, L"TOOLBAR");
			}
			
			
			if (hTheme)
			{
				HDC hdcPaint = NULL;
				HPAINTBUFFER hBufferedPaint = BeginBufferedPaint(hdc, &rc, BPBF_TOPDOWNDIB, NULL, &hdcPaint);
		
				DrawThemeParentBackground(mHwnd, hdcPaint, &rc);

				switch (Mouse)
				{
				case Entered:
					DrawThemeBackground(hTheme, hdcPaint, TP_BUTTON, TS_HOT, &rc, NULL);
					break;
				case ClickDown:
					DrawThemeBackground(hTheme, hdcPaint, TP_BUTTON, TS_PRESSED, &rc, NULL);
					break;
				case Left:
				case ClickUp:
					break;
				}

				HICON m_iconSafe = LoadIcon(g_hDllInst, MAKEINTRESOURCE(IDI_ICON1));
				DrawIconEx(hdcPaint, rc.left+(rc.right-rc.left-30)/2, rc.top+(rc.bottom-rc.top-24)/2, m_iconSafe, 30, 24, 0, NULL, DI_DEFAULTSIZE | DI_NORMAL);
		
				EndBufferedPaint(hBufferedPaint, TRUE);
		
				CloseThemeData(hTheme);
			}
		}
	}

	if (!hdcIn)
	{
		EndPaint(mHwnd, &ps);
	}

	return 0;
};