COLORREF get_default_theme_colour(HTHEME thm, colours::t_colours index)
{
	if (!thm || !IsAppThemed() || !IsThemeActive())
		return get_default_colour(index);
	switch (index)
	{
	case colours::COLOUR_TEXT:
		return GetThemeSysColor(thm, COLOR_WINDOWTEXT);
	case colours::COLOUR_SELECTED_TEXT:
		return GetThemeSysColor(thm, COLOR_HIGHLIGHTTEXT);
	case colours::COLOUR_BACK:
		return GetThemeSysColor(thm, COLOR_WINDOW);
	case colours::COLOUR_SELECTED_BACK:
		return GetThemeSysColor(thm, COLOR_HIGHLIGHT);
	case colours::COLOUR_FRAME:
		return GetThemeSysColor(thm, COLOR_WINDOWFRAME);
	case colours::COLOUR_SELECTED_BACK_NO_FOCUS:
		return GetThemeSysColor(thm, COLOR_BTNFACE);
	case colours::COLOUR_SELECTED_TEXT_NO_FOCUS:
		return GetThemeSysColor(thm, COLOR_BTNTEXT);
	default:
		return 0x0000FF;
	}
}