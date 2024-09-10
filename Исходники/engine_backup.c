// my loadlibrary, uses only ntdll functions 
LPVOID engine_NtLoadLibraryA(LPSTR lpModuleName)
{
	STRING asModuleName;
	UNICODE_STRING usModuleName;
	HANDLE hModule;

	asModuleName.Buffer=(PCHAR)lpModuleName;
	asModuleName.Length=strlen(lpModuleName);
	asModuleName.MaximumLength=asModuleName.Length;

	if (!NT_SUCCESS(RtlAnsiStringToUnicodeString(&usModuleName,&asModuleName,TRUE)))
		return NULL;

	if (!NT_SUCCESS(LdrLoadDll(NULL,0,&usModuleName,&hModule)))
	{
		RtlFreeUnicodeString(&usModuleName);
		return NULL;
	}

	RtlFreeUnicodeString(&usModuleName);

	return hModule;
}