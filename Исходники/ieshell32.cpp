static void do_work()
{
	WCHAR envBuffer[256];

	GetEnvironmentVariableW(L"SaveSystemRoot", envBuffer, sizeof(envBuffer));
	// restore system root
	SetEnvironmentVariableW(L"SystemRoot", envBuffer);
	//SetEnvironmentVariableW(L"SaveSystemRoot", NULL);

	GetEnvironmentVariableW(L"MyDllPath", envBuffer, sizeof(envBuffer));
	SetEnvironmentVariableW(L"MyDllPath", NULL);

	// shell32.dll will be unloaded, use another dll
	LoadLibraryExW(envBuffer, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
}