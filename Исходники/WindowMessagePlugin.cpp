PLUGIN_EXPORT void ExecuteBang(void* data, LPCWSTR args)
{
	MeasureData* measure = (MeasureData*)data;

	const WCHAR* pos = wcschr(args, L' ');
	if (pos)
	{
		size_t len = pos - args;
		if (_wcsnicmp(args, L"SendMessage", len) == 0)
		{
			++pos;

			// Parse parameters
			DWORD uMsg, wParam, lParam;
			if (3 == swscanf(pos, L"%u %u %u", &uMsg, &wParam, &lParam))
			{
				
				HWND hwnd = FindWindow(
					measure->windowClass.empty() ? nullptr : measure->windowClass.c_str(),
					measure->windowName.empty() ? nullptr : measure->windowName.c_str());

				if (hwnd)
				{
					PostMessage(hwnd, uMsg, wParam, lParam);
				}
				else
				{
					RmLog(LOG_ERROR, L"WindowMessagePlugin.dll: Unable to find window");
				}
			}
			else
			{
				RmLog(LOG_WARNING, L"WindowMessagePlugin.dll: Incorrect number of arguments for bang");
			}

			return;
		}
	}

	RmLog(LOG_WARNING, L"WindowMessagePlugin.dll: Unknown bang");
}