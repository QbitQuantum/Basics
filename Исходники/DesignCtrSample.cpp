//
// for MFC initialization
//
extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		_hdllInstance = hInstance;
		if(!AfxInitExtensionModule(DesignCtrSampleDll, hInstance))
			return 0;
		new CDynLinkLibrary(DesignCtrSampleDll);

		_Module.Init(ObjectMap, hInstance);
		//
		registerAppInfo(hInstance);
		DllRegisterServer();
		break;
	
	case DLL_PROCESS_DETACH:
		AfxTermExtensionModule(DesignCtrSampleDll);
		_Module.Term();
		break;
	}

	return 1;
}