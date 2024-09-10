  void perform(const std::string &command, const std::list<std::string> &arguments) {
    
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
    
    if(!CreateProcess(NULL, "", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)){ //child process
      char *argv[arguments.size() + 2];
      argv[0] = (char *)command.c_str();
      argv[arguments.size() + 1] = 0;

      std::list<std::string>::const_iterator it = arguments.begin();
      for (size_t i = 0; i < arguments.size(); i++) {
        argv[i + 1] = (char *)it->c_str();
        it++;
      }

      int rv = _execvp(command.c_str(), argv);
      if (rv == -1) 
        throw make_runtime_error("Unable to create new process: %s.", strerror(errno));
    }
    else { // parent process
      throw make_runtime_error("CreateProcess failed (%d).\n", GetLastError() );
      return;
    }
    
    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );

    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
  }