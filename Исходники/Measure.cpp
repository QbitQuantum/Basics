void CMeasure::GetScaledValue(AUTOSCALE autoScale, int decimals, double theValue, WCHAR* buffer, size_t sizeInWords)
{
	WCHAR format[32];
	double value = 0;

	if (decimals == 0)
	{
		wcsncpy_s(format, L"%.0f", _TRUNCATE);
	}
	else
	{
		_snwprintf_s(format, _TRUNCATE, L"%%.%if", decimals);
	}

	const double* tblScale =
		g_TblScale[(autoScale == AUTOSCALE_1000 || autoScale == AUTOSCALE_1000K) ? AUTOSCALE_INDEX_1000 : AUTOSCALE_INDEX_1024];

	if (theValue >= tblScale[0])
	{
		value = theValue / tblScale[0];
		wcsncat_s(format, L" T", _TRUNCATE);
	}
	else if (theValue >= tblScale[1])
	{
		value = theValue / tblScale[1];
		wcsncat_s(format, L" G", _TRUNCATE);
	}
	else if (theValue >= tblScale[2])
	{
		value = theValue / tblScale[2];
		wcsncat_s(format, L" M", _TRUNCATE);
	}
	else if (autoScale == AUTOSCALE_1024K || autoScale == AUTOSCALE_1000K || theValue >= tblScale[3])
	{
		value = theValue / tblScale[3];
		wcsncat_s(format, L" k", _TRUNCATE);
	}
	else
	{
		value = theValue;
		wcsncat_s(format, L" ", _TRUNCATE);
	}
	_snwprintf_s(buffer, sizeInWords, _TRUNCATE, format, value);
}