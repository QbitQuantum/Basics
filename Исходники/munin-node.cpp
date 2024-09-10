int main(int argc, char* argv[])
{
#ifdef _DEBUG
  // Setup the debug options
  _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF 
    | _CRTDBG_LEAK_CHECK_DF //Check for memory leaks on app exit
    );//| _CRTDBG_CHECK_ALWAYS_DF);
  _CrtSetAllocHook(YourAllocHook);	
#endif

  // Read in Version Infomation
  CFileVersionInfo ver;
  ver.Open(GetModuleHandle(NULL));
  TCHAR displayName[256];
  _sntprintf(displayName, 255, _T("Munin Node for Windows %i.%i.%i"), ver.GetFileVersionMajor(), ver.GetFileVersionMinor(), ver.GetFileVersionQFE());

  // Load Configuration
  // Get the executable file path
  char szConfigFilePath[MAX_PATH];
  ::GetModuleFileNameA(NULL, szConfigFilePath, MAX_PATH);
  PathRemoveFileSpecA(szConfigFilePath);
  PathAppendA(szConfigFilePath, "\\munin-node.ini");
  g_Config.SetPath(szConfigFilePath);
  g_Config.ReadFile();

  // Prepare Service modules
  _Module.Init(_T("munin-node"), _T("Munin Node for Windows"));
  _Module.m_bService = TRUE;  

  // Parse arguments
  if (argc > 1)
  {
    char seps[] = "-/";
    char *pToken;

    pToken = strtok(argv[1], seps);
    while (pToken)
    {
      if (!stricmp(pToken, "install"))
      {
        return !_Module.Install();
      }
      else if (!stricmp(pToken, "uninstall"))
      {
        return !_Module.Uninstall();
      }
      else if (!stricmp(pToken, "quiet"))
      {
        FreeConsole();
      }
      else if (!stricmp(pToken, "unattended"))
      {
        _Module.SetQuiet(true);
      }
      else if (!stricmp(pToken, "run"))
      {
        _Module.m_bService = FALSE;
      }
      else if (!stricmp(pToken, "help") || !stricmp(pToken, "h") || !stricmp(pToken, "?"))
      {
        printf("%s\n", _Module.GetServiceDisplayName());
        printf("Usage:\n");
        printf("  -install    Install the 'Munin Node' service.\n");
        printf("  -uninstall  Removes the 'Munin Node' service.\n");
        printf("  -quiet      Close the console window, running in the background.\n");
        printf("  -run        Run as a normal program, rather than a service.\n");

        return 1;
      }
      pToken = strtok(NULL, seps);			
    }
  }	

  _Module.Start();

  return 0;
}