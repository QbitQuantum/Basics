HRESULT AgentConfigurationEx::CResetThread::Execute (DWORD_PTR dwParam, HANDLE hObject)
{
  static char name[] = "CResetThread::Execute";

  AgentConfigurationEx *agent = (AgentConfigurationEx *) dwParam;

  CancelWaitableTimer(hObject);

  // DebugBreak();

  try
  {
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof( pi ) );

    STARTUPINFO si;
    ZeroMemory(&si, sizeof( si ) );
    si.cb          = sizeof( si );
    si.dwFlags     = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;        // set the window display to HIDE

    // SCM reset command of this service
    std::string cmd = StdStringFormat("cmd /c net stop \"%s\" & net start \"%s\"", Globals.ServerName.c_str( ), Globals.ServerName.c_str( ) ); // Command line

    if ( !::CreateProcess(NULL,                                                                                                                // No module name (use command line)
           const_cast<char *>( cmd.c_str( ) ),
           NULL,                                                                                                                               // Process handle not inheritable
           NULL,                                                                                                                               // Thread handle not inheritable
           FALSE,                                                                                                                              // Set handle inheritance to FALSE
           0,                                                                                                                                  // No creation flags
           NULL,                                                                                                                               // Use parent's environment block
           NULL,                                                                                                                               // Use parent's starting directory
           &si,                                                                                                                                // Pointer to STARTUPINFO structure
           &pi) )                                                                                                                              // Pointer to PROCESS_INFORMATION structure
    {
      AtlTrace("CreateProcess FAIL ");
    }

    ::Sleep(5000);     // make sure process has spawned before killing thread
  }
  catch ( ... )
  {
    agent->AbortMsg("Exception  - ResetAtMidnightThread(void *oObject");
  }
  return S_OK;
}