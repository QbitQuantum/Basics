string osl_FloatToStr(float n)
{
	char buffer[OSL_CONVERT_BUFFER_SIZE];

	try
	{
		if(_gcvt_s(buffer, OSL_CONVERT_BUFFER_SIZE, (float)n, OSL_CONVERT_DIGITS) != 0)
			throw("_gcvt_s() FAILED");
	}
	catch(char* str)
	{
		WriteToLog(DEFAULT_OSL_LOG_NAME, "osl_FloatToStr() EXCEPTION: " + string(str));
		return "";
	}

	return string(buffer);
}