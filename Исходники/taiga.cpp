BOOL Taiga::InitInstance() {
  // Check another instance
  if (CheckInstance(L"Taiga-33d5a63c-de90-432f-9a8b-f6f733dab258", L"TaigaMainW"))
    return FALSE;
  g_hInstance = GetInstanceHandle();

  // Initialize
  InitCommonControls(ICC_STANDARD_CLASSES);
  OleInitialize(NULL);

  // Initialize logger
#ifdef _DEBUG
  Logger.SetOutputPath(AddTrailingSlash(GetCurrentDirectory()) + L"Taiga_debug.log");
  Logger.SetSeverityLevel(LevelDebug);
#else
  Logger.SetOutputPath(AddTrailingSlash(GetPathOnly(GetModulePath())) + L"Taiga.log");
  Logger.SetSeverityLevel(LevelWarning);
#endif

  // Load data
  LoadData();

  // Create API windows
  Skype.Create();
  TaigaApi.Create();

  if (Settings.Program.StartUp.check_new_version) {
    // Create update dialog
    ExecuteAction(L"CheckUpdates");
  } else {
    // Create main dialog
    ExecuteAction(L"MainDialog");
  }

  return TRUE;
}