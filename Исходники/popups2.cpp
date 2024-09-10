int ReloadFont(WPARAM wParam, LPARAM lParam) 
{
#ifdef _UNICODE
	if(ServiceExists(MS_FONT_GETW)) {
		LOGFONTW log_font;
		if(hFontFirstLine) DeleteObject(hFontFirstLine);
		colFirstLine = CallService(MS_FONT_GETW, (WPARAM)&font_id_firstlinew, (LPARAM)&log_font);
		hFontFirstLine = CreateFontIndirectW(&log_font);
		if(hFontSecondLine) DeleteObject(hFontSecondLine);
		colSecondLine = CallService(MS_FONT_GETW, (WPARAM)&font_id_secondlinew, (LPARAM)&log_font);
		hFontSecondLine = CreateFontIndirectW(&log_font);
		if(hFontTime) DeleteObject(hFontTime);
		colTime = CallService(MS_FONT_GETW, (WPARAM)&font_id_timew, (LPARAM)&log_font);
		hFontTime = CreateFontIndirectW(&log_font);

		colBg = CallService(MS_COLOUR_GETW, (WPARAM)&colour_id_bgw, 0);
		colBorder = CallService(MS_COLOUR_GETW, (WPARAM)&colour_id_borderw, 0);
		colSidebar = CallService(MS_COLOUR_GETW, (WPARAM)&colour_id_sidebarw, 0);
		colTitleUnderline = CallService(MS_COLOUR_GETW, (WPARAM)&colour_id_titleunderlinew, 0);
	} else
#endif
	{
		LOGFONTA log_font;
		if(hFontFirstLine) DeleteObject(hFontFirstLine);
		colFirstLine = CallService(MS_FONT_GET, (WPARAM)&font_id_firstline, (LPARAM)&log_font);
		hFontFirstLine = CreateFontIndirectA(&log_font);
		if(hFontSecondLine) DeleteObject(hFontSecondLine);
		colSecondLine = CallService(MS_FONT_GET, (WPARAM)&font_id_secondline, (LPARAM)&log_font);
		hFontSecondLine = CreateFontIndirectA(&log_font);
		if(hFontTime) DeleteObject(hFontTime);
		colTime = CallService(MS_FONT_GET, (WPARAM)&font_id_time, (LPARAM)&log_font);
		hFontTime = CreateFontIndirectA(&log_font);

		colBg = CallService(MS_COLOUR_GET, (WPARAM)&colour_id_bg, 0);
		colBorder = CallService(MS_COLOUR_GET, (WPARAM)&colour_id_border, 0);
		colSidebar = CallService(MS_COLOUR_GET, (WPARAM)&colour_id_sidebar, 0);
		colTitleUnderline = CallService(MS_COLOUR_GET, (WPARAM)&colour_id_titleunderline, 0);
	}

	return 0;
}