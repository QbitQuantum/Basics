bool FontUnload(const char *p_filename)
{
	bool t_success;
	t_success = true;

	if (t_success)
		t_success = RemoveFontResourceA(p_filename) != 0;

	if (t_success)
		PostMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);

	return t_success;
}