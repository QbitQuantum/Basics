PLUGIN_EXPORT void Reload(void* data, void* rm, double* maxValue)
{
	MeasureData* measure = (MeasureData*)data;

	LPCWSTR type = RmReadString(rm, L"ResCountType", L"GDI");
	if (_wcsicmp(L"GDI", type) == 0)
	{
		measure->type = GDI_COUNT;
	}
	else if (_wcsicmp(L"USER", type) == 0)
	{
		measure->type = USER_COUNT;
	}
	else if (_wcsicmp(L"HANDLE", type) == 0)
	{
		measure->type = HANDLE_COUNT;
	}
	else if (_wcsicmp(L"WINDOW", type) == 0)
	{
		measure->type = WINDOW_COUNT;
	}
	else
	{
		WCHAR buffer[256];
		_snwprintf_s(buffer, _TRUNCATE, L"ResMon.dll: GDICountType=%s is not valid in [%s]", type, RmGetMeasureName(rm));
		RmLog(LOG_ERROR, buffer);
	}

	measure->process = RmReadString(rm, L"ProcessName", L"");
}