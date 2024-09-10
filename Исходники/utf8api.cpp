	unsigned status_bar_get_text_width (HWND wnd, HTHEME thm, const char * p_text, bool b_customfont)
	{
		HFONT fnt = NULL;
		bool b_release_fnt = false;
		unsigned rv = NULL;

		DLLVERSIONINFO2 dvi;

		//uxtheme_api_ptr p_uxtheme;

		bool b_themed = thm != NULL;//p_uxtheme->IsThemeActive() && p_uxtheme->IsAppThemed();

		HRESULT hr = uih::GetComCtl32Version(dvi);

		if (!(SUCCEEDED(hr) && dvi.info1.dwMajorVersion == 6))
			//uxtheme_handle::g_create(p_uxtheme);
			b_themed=false;


		if (b_customfont || !b_themed)
		{
			fnt = (HFONT)SendMessage(wnd, WM_GETFONT, NULL, NULL);
			b_release_fnt =false;
		}
		else
		{
			LOGFONT lf;

			//bool b_got_theme_font = false;

			if (b_themed && SUCCEEDED(GetThemeFont(thm, NULL, NULL, NULL, TMT_FONT, &lf)))
			{
				fnt = CreateFontIndirect(&lf);
				b_release_fnt = true;
			}
			else
			{
				fnt = (HFONT)SendMessage(wnd, WM_GETFONT, NULL, NULL);
				b_release_fnt =false;
			}
#if 0
			if (!b_got_theme_font)
			{

				NONCLIENTMETRICS ncm;
				memset(&ncm, 0, sizeof(NONCLIENTMETRICS));
				ncm.cbSize = sizeof(NONCLIENTMETRICS);
				SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &ncm, 0);
				lf = ncm.lfStatusFont;
			}
			fnt = CreateFontIndirect(&lf);
			b_release_fnt = true;
#endif
		}

		HDC dc = GetDC(wnd);
		HFONT fnt_old = SelectFont(dc, fnt);
		rv = (unsigned)ui_helpers::get_text_width(dc, p_text, strlen(p_text));
		SelectFont(dc, fnt_old);
		ReleaseDC(wnd, dc);

		if (b_release_fnt)
			DeleteFont(fnt);
		return rv;
	}