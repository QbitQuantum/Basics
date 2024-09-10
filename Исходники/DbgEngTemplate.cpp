extern "C" HRESULT CALLBACK DebugExtensionInitialize(PULONG Version, PULONG Flags)
{
	IDebugClient *DebugClient;
	PDEBUG_CONTROL DebugControl;
	HRESULT Hr;

	*Version = DEBUG_EXTENSION_VERSION(1, 0);
	*Flags = 0;
	Hr = S_OK;

	if ((Hr = DebugCreate(__uuidof(IDebugClient), (void **)&DebugClient)) != S_OK)
	{
		return Hr;
	}
	if ((Hr = DebugClient->QueryInterface(__uuidof(IDebugControl),	(void **)&DebugControl)) == S_OK)
	{
		ExtensionApis.nSize = sizeof(ExtensionApis);
		Hr = DebugControl->GetWindbgExtensionApis64(&ExtensionApis);
		DebugControl->Release();
	}
	DebugClient->Release();
	return Hr;
}