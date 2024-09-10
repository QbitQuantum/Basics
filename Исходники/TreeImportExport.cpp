DWORD_PTR TreeImportExport::ConvertStringToDwordPtr(const char * strValue)
{
	DWORD_PTR result = 0;

	if (strValue)
	{
#ifdef _WIN64
		result = _strtoi64(strValue, NULL, 16);
#else
		result = strtoul(strValue, NULL, 16);
#endif
	}

	return result;
}