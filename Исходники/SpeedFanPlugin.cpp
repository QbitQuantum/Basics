PLUGIN_EXPORT void Reload(void* data, void* rm, double* maxValue)
{
	MeasureData* measure = (MeasureData*)data;

	LPCWSTR type =  RmReadString(rm, L"SpeedFanType", L"TEMPERATURE");
	if (_wcsicmp(L"TEMPERATURE", type) == 0)
	{
		measure->type = TYPE_TEMP;

		LPCWSTR scale = RmReadString(rm, L"SpeedFanScale", L"C");
		if (_wcsicmp(L"C", scale) == 0)
		{
			measure->scale = SCALE_CENTIGRADE;
		}
		else if (_wcsicmp(L"F", scale) == 0)
		{
			measure->scale = SCALE_FARENHEIT;
		}
		else if (_wcsicmp(L"K", scale) == 0)
		{
			measure->scale = SCALE_KELVIN;
		}
		else
		{
			WCHAR buffer[256];
			_snwprintf_s(buffer, _TRUNCATE, L"SpeedFanPlugin.dll: SpeedFanScale=%s is not valid in [%s]", scale, RmGetMeasureName(rm));
			RmLog(LOG_ERROR, buffer);
		}
	}
	else if (_wcsicmp(L"FAN", type) == 0)
	{
		measure->type = TYPE_FAN;
	}
	else if (_wcsicmp(L"VOLTAGE", type) == 0)
	{
		measure->type = TYPE_VOLT;
	}
	else
	{
		WCHAR buffer[256];
		_snwprintf_s(buffer, _TRUNCATE, L"SpeedFanPlugin.dll: SpeedFanType=%s is not valid in [%s]", type, RmGetMeasureName(rm));
		RmLog(LOG_ERROR, buffer);
	}

	measure->number = RmReadInt(rm, L"SpeedFanNumber", 0);
}