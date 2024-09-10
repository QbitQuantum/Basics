  void Init()
  {
    cDLL dll(TEXT("user32.dll"));
    if (dll.IsValid()) {
      BOOL (WINAPI *SetProcessDPIAware)() = nullptr;
      if (dll.LoadFunction("SetProcessDPIAware", &SetProcessDPIAware)) {
        std::wcout<<TEXT("WinMain Calling SetProcessDPIAware()")<<std::endl;
        SetProcessDPIAware();
      }
    }

    // Init common controls for modern looking theming
    INITCOMMONCONTROLSEX icce;
    icce.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icce.dwICC =
      ICC_USEREX_CLASSES | // Combobox
      ICC_STANDARD_CLASSES // All other controls
    ;
    ::InitCommonControlsEx(&icce);

    // Init GDI+
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&gGDIPlusToken, &gdiplusStartupInput, NULL);
  }