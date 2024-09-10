int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow) {

    CoInitialize(NULL);
	
#if 0
    // register the type lib
	ITypeLib* pTLib = NULL;
	LoadTypeLibEx(L"AnyEXETypeInfo.tlb", REGKIND_REGISTER, &pTLib);
	pTLib->Release();
#endif

	if(strstr(lpCmdLine, "/Embedding") || strstr(lpCmdLine, "-Embedding")) {
        ComponentClassFactory cf;
		DWORD regID = 0;
		CoRegisterClassObject(CLSID_Component, (IClassFactory*)&cf, CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &regID);
		MSG ms;
		while(GetMessage(&ms, 0, 0, 0)) {
			TranslateMessage(&ms);
			DispatchMessage(&ms);
		}
		CoRevokeClassObject(regID);
    }
	CoUninitialize();   
	return 0;
}