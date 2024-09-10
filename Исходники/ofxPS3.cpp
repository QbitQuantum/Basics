void ofxPS3::StartSettingsDialog()
{
   HWND        hwnd;
   MSG         msg;
   WNDCLASS    wndclass;
   char        szAppName[64] = "PS3 Eye settings: ";
   strcat(szAppName,GUIDToString(guid).c_str());
   wndclass.style         = 0;
   wndclass.lpfnWndProc   = ofxPS3::WndProc;
   wndclass.cbClsExtra    = 0;
   wndclass.cbWndExtra    = 0;
   HMODULE hInstance;
   GetModuleHandleEx(0,NULL,&hInstance);
   wndclass.hInstance     = hInstance;
   wndclass.hIcon         = LoadIconA(hInstance, szAppName);
   wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
   wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
   //wndclass.lpszMenuName  = szAppName;
   //wndclass.lpszClassName = szAppName;
   RegisterClass(&wndclass);

   InitCommonControls(); 

   hwnd = CreateWindowA(szAppName,
      szAppName,
      DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
	  0, 0, 465, cameraPixelMode ? 410 : 110,
      NULL, NULL, hInstance, 0);
   SetWindowLongPtr(hwnd,GWLP_USERDATA,(LONG_PTR)(this));
   while (GetMessage(&msg, NULL, 0, 0)) 
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
}