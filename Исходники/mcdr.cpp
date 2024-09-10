/* ======================================================================= */
void Initialise(HINSTANCE *Instance)
{
  ProcessMutex = CreateMutex(0, 1, WindowName);
  if(ProcessMutex == NULL)
    Exception(__LINE__, GetLastError(), "Failed to create mutex object");
  if(GetLastError() == ERROR_ALREADY_EXISTS)
    Exception(__LINE__, GetLastError(), "Another instance of %s is already running. Please wait for it to terminate, click the icon in the taskbar and click terminate or kill the process through the Windows Task Manager", WindowName);

  char **ArgumentsPointer;
  // Walk arguments array
  for(ArgumentsPointer = __argv + 1; *ArgumentsPointer; ++ArgumentsPointer)
  {
    // First character not forward slash
    if(**ArgumentsPointer != 47)
      // Not valid switch character, so bail
      Exception(0, 0, "The switch character '%c' is unrecognised. Please use the '/' character to denote the beginning of an option", **ArgumentsPointer);
    // Compare character after slash
    switch(*(++*ArgumentsPointer))
    {
      // Encoding quality
      case 'q': Quality = Clamp(atoi(++*ArgumentsPointer), 0, 9); break;
      // Enable logging
      case 'l': Log(LOG_OPEN, NULL); break;
      // Enable one-track-only mp3
      case 'o': OneTrackOnly = 1; break;
      // Set CBR quality and bitrate
      case 'b': MP3Quality = Clamp(atoi(++*ArgumentsPointer), ABR_8, ABR_320); break;
      // Set VBR quality
      case 'v': MP3Quality = Clamp(atoi(++*ArgumentsPointer), 0, 9); MP3Quality = VBR_10+(MP3Quality*10); break;
      // Version information
      case '!': Exception(0, 0, "%s; Version %u.%02u (%u-bit) compiled %s.\nCopyright © MS-Design, 2011. http://github.com/msdsgn/mcdr.\n\nUses LAME audio encoder -- http://lame.sourceforge.net/", WindowName, VersionMajor, VersionMinor, VersionBits, VersionDate);
      // Bail on un-supported or invalid parameters
      default : Exception(0, 0, "The parameter '%c' is unrecognised", **ArgumentsPointer);
    }
  }

  Log(LOG_WRITE, "%s %u.%02u (%u-bit); %s", WindowName, VersionMajor, VersionMinor, VersionBits, VersionDate);

  Log(LOG_WRITE, "* MP3 Quality = %d", MP3Quality);
  Log(LOG_WRITE, "* Encoding Quality = %d", Quality);
  Log(LOG_WRITE, "* One Track Only = %d", OneTrackOnly);

  INITCOMMONCONTROLSEX iccData;

  iccData.dwSize = sizeof(iccData);
  iccData.dwICC = ICC_PROGRESS_CLASS;

  if(InitCommonControlsEx(&iccData) == FALSE)
    Exception(__LINE__, GetLastError(), "Error code %u initialising common controls", iccData.dwICC);

  memset(&WindowClass, 0, sizeof(WindowClass));
  WindowClass.cbSize = sizeof(WindowClass);
  WindowClass.style = CS_HREDRAW | CS_VREDRAW;
  WindowClass.lpfnWndProc = (WNDPROC)WinProc;
  WindowClass.hInstance = *Instance;
  WindowClass.hIcon = (HICON)LoadImage(WindowClass.hInstance, MAKEINTRESOURCE(1), IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
  WindowClass.hIconSm = (HICON)LoadImage(WindowClass.hInstance, MAKEINTRESOURCE(1), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
  WindowClass.hCursor = LoadCursor(0, IDC_ARROW);
  WindowClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
  WindowClass.lpszClassName = WindowName;
  if(!RegisterClassEx(&WindowClass))
    Exception(__LINE__, GetLastError(), "Failed to register window class");

  WindowFont = CreateFont(13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "MS Shell Dlg");
  if(WindowFont == NULL)
    Exception(__LINE__, GetLastError(), "Failed to create shell dialog font");

  RECT D;
  GetWindowRect(GetDesktopWindow(), &D);

  Handles.WH = CreateWindowEx(WS_EX_APPWINDOW, WindowClass.lpszClassName, WindowClass.lpszClassName, WS_POPUP | WS_DLGFRAME | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, 320, 260, NULL, NULL, WindowClass.hInstance, NULL);
  if(Handles.WH == NULL)
    Exception(__LINE__, GetLastError(), "Failed to load window");

  Handles.WT = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE, 52, 10, 248, 48, Handles.WH, NULL, WindowClass.hInstance, NULL);
  if(Handles.WT == NULL)
    Exception(__LINE__, GetLastError(), "Failed to create window text object");
  SendMessage(Handles.WT, WM_SETFONT, (WPARAM)WindowFont, 0);

  Handles.PO = CreateWindowEx(0, "msctls_progress32", NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH, 10, 60, 294, 24, Handles.WH, NULL, WindowClass.hInstance, NULL);
  if(Handles.PO == NULL)
    Exception(__LINE__, GetLastError(), "Failed to create progress bar one object");

  Handles.PA = CreateWindowEx(0, "msctls_progress32", NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH, 10, 98, 294, 24, Handles.WH, NULL, WindowClass.hInstance, NULL);
  if(Handles.PA == NULL)
    Exception(__LINE__, GetLastError(), "Failed to create progress bar all object");

  Handles.WC = CreateWindowEx(0, "Button", "&Cancel", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 10, 136, 64, 24, Handles.WH, (HMENU)1, WindowClass.hInstance, NULL);
  if(Handles.WC == NULL)
    Exception(__LINE__, GetLastError(), "Failed to create cancel button object");
  SendMessage(Handles.WC, WM_SETFONT, (WPARAM)WindowFont, 0);

  Handles.WI = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_ICON, 10, 10, 32, 32, Handles.WH, NULL, WindowClass.hInstance, NULL);
  if(Handles.WI == NULL)
    Exception(__LINE__, GetLastError(), "Failed to create icon object");

  Handles.WA = CreateWindowEx(0, "STATIC", "", WS_CHILD | WS_VISIBLE | WS_DISABLED | SS_RIGHT, 80, 134, 224, 32, Handles.WH, NULL, WindowClass.hInstance, NULL);
  if(Handles.WA == NULL)
    Exception(__LINE__, GetLastError(), "Failed to create about text object");
  SendMessage(Handles.WA, WM_SETFONT, (WPARAM)WindowFont, 0);

  Handles.WB = CreateWindowEx(WS_EX_STATICEDGE, "STATIC", "", WS_CHILD | WS_VISIBLE | SS_BITMAP, 9, 174, 294, 48, Handles.WH, NULL, WindowClass.hInstance, NULL);
  if(Handles.WB == NULL)
    Exception(__LINE__, GetLastError(), "Failed to create bitmap object");

  SendMessage(Handles.WI, STM_SETICON, (WPARAM)WindowClass.hIcon, NULL);
  WindowBitmap = (HBITMAP)LoadImage(WindowClass.hInstance, MAKEINTRESOURCE(1), IMAGE_BITMAP, 294, 48, LR_DEFAULTCOLOR);
  if(WindowBitmap == NULL)
    Exception(__LINE__, GetLastError(), "Failed to load window bitmap");
  SendMessage(Handles.WB, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)WindowBitmap);

  SetLabel(Handles.WA, "M-CDR %u.%02u (%u-bit) %s\nCopyright © MS-Design, 2011", VersionMajor, VersionMinor, VersionBits, VersionDate);

  ThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadMain, &Handles, 0, NULL);
  if(ThreadHandle == NULL)
    Exception(__LINE__, GetLastError(), "Error creating thread");

  CentreWindow(Handles.WH);
  ShowWindow(Handles.WH, SW_SHOW);
  SetForegroundWindow(Handles.WH);
  SetFocus(Handles.WC);
}