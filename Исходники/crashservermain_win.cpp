int main()
#endif
{
    {
        int hCrt;
        FILE *hf;

        AllocConsole();
        //::AttachConsole(ATTACH_PARENT_PROCESS);
        hCrt = _open_osfhandle(
                (long) GetStdHandle(STD_OUTPUT_HANDLE),
                _O_TEXT
            );
        hf = _fdopen( hCrt, "w" );
        *stdout = *hf;
        /*i = */setvbuf( stdout, NULL, _IONBF, 0 );
    }

  const wchar_t *pipeName = BREAKPAD_PIPE_NAME;
  const ::LPSECURITY_ATTRIBUTES securityAttributes = NULL;
  void* connect_context = 0;
  void* dump_context = 0;
  void* exit_context = 0;
  const bool generate_dumps = true;
  const std::wstring dump_path = L"c:\\temp";

  std::cout << "---------------------------------------------------------------------------------------" << std::endl;
  std::cout << "Creating CrashGenerationServer" << std::endl;

  void* upload_context = 0;
  google_breakpad::CrashGenerationServer server(pipeName,
                                                securityAttributes,
                                                onClientConnectedCallback,
                                                connect_context,
                                                onClientDumpRequestCallback,
                                                dump_context,
                                                onClientExitedCallback,
                                                exit_context,
                                                onClientUploadRequestCallback,
                                                upload_context,
                                                generate_dumps,
                                                &dump_path);

  std::cout << "Starting CrashGenerationServer..." << std::endl;

  if (!server.Start()) {
      std::cerr << "failed to start" << std::endl;
    return -1;
  }

  std::cout << "\tsuccess!" << std::endl;

#ifdef WINDOWS_APP
  ::MSG msg;
  for (;;)
  {
    std::cout << "alive... " << std::endl;

    ::BOOL messageAvailable = ::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
    if (messageAvailable == 0) {
      Sleep(1000);
      continue;
    }

    ::BOOL success = GetMessage(&msg, NULL, 0, 0);
    if (0 != success) {
        std::cerr << "Unable to get next Windows message. Exiting" << std::endl;
      break;
    }

    if (-1 == success) {
        std::cerr << "Windowing message pump error" << std::endl;
      return -1;
    }
    else {
      std::cout << "WM message " << msg.message << std::endl;

      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  const int exitCode = (int)msg.wParam;
  std::cout << "Exiting..." << exitCode << std::endl;
  return exitCode;
#else
  for (;;)
  {
    std::cout << "alive... " << std::endl;
    ::Sleep(1000);
  }
#endif
}