int APIENTRY wWinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPWSTR    lpCmdLine,
                      int       nCmdShow)
{
  ghInstance = hInstance;
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
  UNREFERENCED_PARAMETER(nCmdShow);

  OleInitialize(0); // for system drag-n-drop

  // comment this out if you need system theming
  ::SciterSetOption(NULL,SCITER_SET_UX_THEMING,TRUE);

  auto message_pump = []() -> int {
    MSG msg;
    // Main message loop:
	  while (GetMessage(&msg, NULL, 0, 0))
	  {
  	  TranslateMessage(&msg);
		  DispatchMessage(&msg);
	  }
    return (int) msg.wParam;
  };

  int r = uimain(message_pump);

  OleUninitialize();

  return r;
	  
}