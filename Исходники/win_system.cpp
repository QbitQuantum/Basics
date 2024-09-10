void win_system::onCreate()
{
  HINSTANCE hInstance = GetModuleHandle(NULL);
  
  mainWindow = new main_window_com(this);
  mainWindow->init("MAIN", hInstance, NULL);
  mainWindow->create("CrashUtils", 300, 300, 1280, 800);
  mainWindow->SetWindowPos(200, 30, 1280, 800);
  mainWindow->ShowWindow(SW_SHOW/*nCmdShow*/);
  mainWindow->UpdateWindow();
  
  AllowSetForegroundWindow(ASFW_ANY);
}