BOOL config_GetAnsiString(HMODULE hModule,DWORD dwStringID,PANSI_STRING pasString)
{
	PWCHAR pwString;
	UNICODE_STRING usString;
		
	// get pointer to string in stringtable
	if (pwString=config_GetResourceStringData(hModule,dwStringID))
	{
		// convert it to ansi
		usString.Buffer=pwString+1;
		usString.Length=usString.MaximumLength=(*pwString)*2;

		if (NT_SUCCESS(RtlUnicodeStringToAnsiString(pasString,&usString,TRUE)))
			return TRUE;
	}

	return FALSE;
}