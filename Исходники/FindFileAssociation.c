/*--------------------------------------------------------------------------*/ 
char *FindFileAssociation (char *ptrFindStr,char *Extra) 
{
	char *ptrResult = NULL ;

	if ( ptrFindStr )
	{
		wchar_t *wcptrFindStr = to_wide_string(ptrFindStr);
		wchar_t *wcExtra = to_wide_string(Extra);
		wchar_t szDefault[PATH_MAX + FILENAME_MAX];
		DWORD ccDefault = PATH_MAX + FILENAME_MAX;

		if (wcptrFindStr)
		{
			HRESULT rc = AssocQueryStringW (0, ASSOCSTR_EXECUTABLE,wcptrFindStr, wcExtra, szDefault, &ccDefault);
			if (ccDefault)
			{
				if (rc == S_OK) ptrResult = wide_string_to_UTF8(szDefault);
			}
		}
	}
	return ptrResult;
}