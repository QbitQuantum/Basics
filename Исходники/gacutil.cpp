extern "C" __declspec(dllexport) BOOL __stdcall GacUninstallAssembly(
		LPINTERNAL_CONTEXT InContext,
		WCHAR* InAssemblyName,
		WCHAR* InDescription,
		WCHAR* InUniqueID){

	FUSION_INSTALL_REFERENCE InstallInfo;

	// setup uninstallation parameters
	memset(&InstallInfo, 0, sizeof(InstallInfo));

	InstallInfo.cbSize = sizeof(InstallInfo);
	InstallInfo.dwFlags = 0;
	InstallInfo.guidScheme = FUSION_REFCOUNT_OPAQUE_STRING_GUID;
	InstallInfo.szIdentifier = InUniqueID;
	InstallInfo.szNonCannonicalData = InDescription;

	CComPtr<IAssemblyCache> Cache;

	if (!SUCCEEDED(InContext->CreateAssemblyCache(&Cache, 0)))
		return FALSE;

	// uninstall assembly with given parameters
	if(!SUCCEEDED(Cache->UninstallAssembly(0, InAssemblyName, &InstallInfo, NULL)))
		return FALSE;

	return TRUE;
}