/*
** Converts given time to string.
** This function is a wrapper function for wcsftime.
**
*/
void MeasureTime::TimeToString(WCHAR* buf, size_t bufLen, const WCHAR* format, const struct tm* time)
{
	if (bufLen > 0)
	{
		_invalid_parameter_handler oldHandler = _set_invalid_parameter_handler(RmNullCRTInvalidParameterHandler);
		_CrtSetReportMode(_CRT_ASSERT, 0);

		errno = 0;
		wcsftime(buf, bufLen, format, time);
		if (errno == EINVAL)
		{
			LogErrorF(this, L"Time: \"Format=%s\" invalid", format);
			buf[0] = 0;
		}

		_set_invalid_parameter_handler(oldHandler);
	}
}