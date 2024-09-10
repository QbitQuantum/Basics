int _tmain(int argc, _TCHAR* argv[]) {
  CommandLineArguments args(argc, argv);
  vector<TCHAR> temp_file_name_buffer(MAX_PATH);
  vector<TCHAR> temp_path_buffer(MAX_PATH);

  //  Gets the temp path env string (no guarantee it's a valid path).
  unsigned long temp_path_length = ::GetTempPath(MAX_PATH,
                                                 &temp_path_buffer[0]);

  unsigned int error_code = ::GetTempFileName(&temp_path_buffer[0],
                                              TEMP_FILE_PREFIX,
                                              0,
                                              &temp_file_name_buffer[0]);

  std::wstring temp_file_name(&temp_file_name_buffer[0]);
  if (!ExtractResource(IDR_DRIVER_LIBRARY, temp_file_name)) {
    std::wcout << L"Failed to extract the library to temp directory: "
               << temp_file_name;
    return ERR_DLL_EXTRACT_FAIL;
  }

  HMODULE module_handle = ::LoadLibrary(temp_file_name.c_str());
  if (module_handle == NULL) {
    std::wcout << L"Failed to load the library from temp directory: "
               << temp_file_name;
    return ERR_DLL_LOAD_FAIL;
  }

  STARTSERVEREXPROC start_server_ex_proc = reinterpret_cast<STARTSERVEREXPROC>(
      ::GetProcAddress(module_handle, START_SERVER_EX_API_NAME));
  STOPSERVERPROC stop_server_proc = reinterpret_cast<STOPSERVERPROC>(
      ::GetProcAddress(module_handle, STOP_SERVER_API_NAME));
  if (start_server_ex_proc == NULL || stop_server_proc == NULL) {
    std::wcout << L"Could not find entry point in extracted library: "
               << temp_file_name;
    return ERR_FUNCTION_NOT_FOUND;
  }

  int port = atoi(args.GetValue(PORT_COMMAND_LINE_ARG, "5555").c_str());
  std::string host_address = args.GetValue(HOST_COMMAND_LINE_ARG, "");
  std::string log_level = args.GetValue(LOGLEVEL_COMMAND_LINE_ARG, "");
  std::string log_file = args.GetValue(LOGFILE_COMMAND_LINE_ARG, "");
  void* server_value = start_server_ex_proc(port,
                                            host_address,
                                            log_level,
                                            log_file);
  if (server_value == NULL) {
    std::cout << L"Failed to start the server with: "
              << L"port = '" << port << "', "
              << L"host = '" << host_address << "', "
              << L"log level = '" << log_level << "', "
              << L"log file = '" << log_file << "'";
    ;
    return ERR_SERVER_START;
  }
  std::cout << "Started InternetExplorerDriver server"
            << " (" << GetProcessArchitectureDescription() << ")"
            << std::endl;
  std::cout << GetExecutableVersion()
            << std::endl;
  std::cout << "Listening on port " << port << std::endl;
  if (host_address.size() > 0) {
    std::cout << "Bound to network adapter with IP address " 
              << host_address
              << std::endl;
  }
  if (log_level.size() > 0) {
    std::cout << "Log level is set to "
              << log_level
              << std::endl;
  }
  if (log_file.size() > 0) {
    std::cout << "Log file is set to "
              << log_file
              << std::endl;
  }

  // Create the shutdown event and wait for it to be signaled.
  DWORD process_id = ::GetCurrentProcessId();
  vector<wchar_t> process_id_buffer(10);
  _ltow_s(process_id, &process_id_buffer[0], process_id_buffer.size(), 10);
  std::wstring process_id_string(&process_id_buffer[0]);
  std::wstring event_name = IESERVER_SHUTDOWN_EVENT_NAME + process_id_string;
  HANDLE event_handle = ::CreateEvent(NULL,
                                      TRUE, 
                                      FALSE,
                                      event_name.c_str());
  ::WaitForSingleObject(event_handle, INFINITE);
  ::CloseHandle(event_handle);
  stop_server_proc();

  ::FreeLibrary(module_handle);
  ::DeleteFile(temp_file_name.c_str());
  return 0;
}