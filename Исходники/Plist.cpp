// https://blogs.msdn.microsoft.com/oldnewthing/20071008-00/?p=24863/
static bool is_alttab_window(HWND const Window)
{
	if (!IsWindowVisible(Window))
		return false;

	auto Try = GetAncestor(Window, GA_ROOTOWNER);
	HWND Walk = nullptr;
	while (Try != Walk)
	{
		Walk = Try;
		Try = GetLastActivePopup(Walk);
		if (IsWindowVisible(Try))
			break;
	}
	if (Walk != Window)
		return false;

	// Tool windows should not be displayed either, these do not appear in the task bar
	if (GetWindowLongPtr(Window, GWL_EXSTYLE) & WS_EX_TOOLWINDOW)
		return false;

	if (IsWindows8OrGreater())
	{
		int Cloaked = 0;
		if (SUCCEEDED(imports.DwmGetWindowAttribute(Window, DWMWA_CLOAKED, &Cloaked, sizeof(Cloaked))) && Cloaked)
			return false;
	}

	return true;
}