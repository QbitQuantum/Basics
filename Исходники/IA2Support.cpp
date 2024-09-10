BOOL uninstallIA2Support() {
	int i;
	LPFNDLLCANUNLOADNOW IA2Dll_DllCanUnloadNow;
	if(isIA2Installed) {
	for(i=0;i<ARRAYSIZE(ia2Iids);++i) {
			CoRegisterPSClsid(ia2Iids[i],_ia2PSClsidBackups[i]);
		}
		CoRevokeClassObject(IA2RegCooky);
		IA2Dll_DllCanUnloadNow=(LPFNDLLCANUNLOADNOW)GetProcAddress(static_cast<HMODULE>(IA2DllHandle),"DllCanUnloadNow");
		assert(IA2Dll_DllCanUnloadNow); //IAccessible2 proxy dll must have this function
		if(IA2Dll_DllCanUnloadNow()==S_OK) {
			CoFreeLibrary(IA2DllHandle);
		}
		IA2DllHandle=0;
		isIA2Installed=FALSE;
	}
	return TRUE;
}