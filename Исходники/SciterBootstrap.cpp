void BoilerplateInit()
{
	OleInitialize(0);

	// Common controls (manifest must be present)
	{
		// Include the v6 common controls in the manifest
		#pragma comment(lib,"comctl32.lib")
		#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

		INITCOMMONCONTROLSEX InitCtrls;
		InitCtrls.dwSize = sizeof(INITCOMMONCONTROLSEX);
		InitCtrls.dwICC = ICC_WIN95_CLASSES | ICC_STANDARD_CLASSES;
		BOOL res = InitCommonControlsEx(&InitCtrls); _ASSERT(res);
	}
}