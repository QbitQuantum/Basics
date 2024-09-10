BOOL WINAPI WriteAppletToFile(HANDLE FileHandle)
{
	BOOL    Success = FALSE;
	HRSRC   ResourceHandle = NULL;
	HGLOBAL Resource = NULL;
	DWORD   BytesCount = 0;
	LPVOID  Bytes = NULL;

	ResourceHandle = FindResourceW(
		g_ModuleHandle,
		MAKEINTRESOURCEW(IDR_X64_EXE),
		RT_RCDATA
	);

	if (!ResourceHandle)
		return FALSE;

	BytesCount = SizeofResource(
		g_ModuleHandle,
		ResourceHandle
	);

	Resource = LoadResource(
		g_ModuleHandle, 
		ResourceHandle
	);

	if (!Resource)
		goto Cleanup;

	Bytes = LockResource(Resource);

	if (!Bytes)
		goto Cleanup;

	Success = WriteFile(
		FileHandle,
		Bytes,
		BytesCount,
		NULL,
		NULL
	);

Cleanup:

	if (Bytes)
		UnlockResource(Bytes);

	if (Resource)
		FreeResource(Resource);

	return Success;
}