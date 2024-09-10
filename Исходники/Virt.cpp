ULONG
MyCopyFile(
	__in PWCHAR NewFileName,
	__in PWCHAR OldFileName
)
{
	ULONG verdict  = efVerdict_Default;
	ULONG i = 0;
	i = (ULONG)wcslen(NewFileName);
	
	while ( i > 0 )
	{
		if (NewFileName[i] == L'\\')
			break;
		
		i--;
	}
	
	if (i > 2 )
	{
		PWCHAR wcDirectoryPath;
		
		wcDirectoryPath = new WCHAR[i+1];
		memset(wcDirectoryPath, 0, (i+1)*sizeof(WCHAR) );
		memcpy( wcDirectoryPath, NewFileName, i*sizeof(WCHAR) );

		SHCreateDirectoryExW(
			NULL,
			wcDirectoryPath,
			NULL
			);
		
		delete [] wcDirectoryPath;
	}
	
	BOOL res = CopyFileW(
		OldFileName,
		NewFileName,
		FALSE
		);

	verdict = (res)?efVerdict_Allow : efVerdict_Deny ;


	return verdict;
}