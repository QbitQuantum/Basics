int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
//	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	AtlAxWinInit();

	int nRet = 0;
	
	BOOL bFirstInst = CSingleInstApp::InitInstance(APP_INST_UID);
	if (!bFirstInst) {

		if (::lstrcmpi(_T("/exit"), lpstrCmdLine) == 0) {

			CSingleInstApp::PostInstanceMesage(AIMSG_EXIT, 0);
			nRet = 251;

		} else if (::lstrcmpi(_T("/restart"), lpstrCmdLine) == 0) {

			CSingleInstApp::PostInstanceMesage(AIMSG_EXIT, 0);
			CSingleInstApp::WaitInstance(APP_INST_UID);
			nRet = Run(lpstrCmdLine, nCmdShow);
			CSingleInstApp::InitInstance(APP_INST_UID);

		} else {

			CSingleInstApp::PostInstanceMesage(AIMSG_POPUP, 0);
			nRet = 250;
		}

		//		ATOM atCmdLine = ::GlobalAddAtom(lpstrCmdLine);
		//		if (NULL != atCmdLine) {
		//		}


	} else {

		nRet = Run(lpstrCmdLine, nCmdShow);

	}

	_Module.Term();
	::CoUninitialize();

	return nRet;
}