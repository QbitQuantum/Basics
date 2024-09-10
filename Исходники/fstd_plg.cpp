BOOL WINAPI DllMain(HINSTANCE hinst, DWORD reason, LPVOID ptr)
{
	if(reason == DLL_PROCESS_ATTACH)
	{
		FP_HModule = (HMODULE)hinst;
		AtExit(idAtExit);
	}

	BOOL res = FP_PluginStartup(reason);

	if(reason == DLL_PROCESS_DETACH)
	{
		CallAtExit();
	}

	return res;
}