PLUGIN_EXPORT double Update(void* data)
{
	Measure* measure = (Measure*)data;

	double currentState = 0.0;
	APPBARDATA abd = { sizeof abd };
	UINT uState = (UINT)SHAppBarMessage(ABM_GETSTATE, &abd);
	HWND hwnd = FindWindow(L"Shell_traywnd", L"");

	switch (measure->type)
	{
	case BOTH:
		hwnd = FindWindow(L"Shell_traywnd", L"");
		break;
	case FIRST:
		hwnd = FindWindow(L"Shell_traywnd", L"");
		break;
	case SECOND:
		hwnd = FindWindow(L"Shell_SecondaryTrayWnd", L"");
		break;
	}
	
	currentState = (uState & ABS_AUTOHIDE) ? 2 : 1;
	return (!IsWindowVisible(hwnd)) ? -currentState : currentState;

}