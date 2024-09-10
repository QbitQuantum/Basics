int initialiseWindows(const TRI_win_initialise_e initialiseWhat, const char* data) {


  // ............................................................................
  // The data is used to transport information from the calling function to here
  // it may be NULL (and will be in most cases)
  // ............................................................................

  switch (initialiseWhat) {

    case TRI_WIN_INITIAL_SET_DEBUG_FLAG: {
      _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF)|_CRTDBG_CHECK_ALWAYS_DF);    
      return 0;
    }

    // ...........................................................................
    // Assign a handler for invalid handles 
    // ...........................................................................

    case TRI_WIN_INITIAL_SET_INVALID_HANLE_HANDLER: { 
      newInvalidHandleHandler = InvalidParameterHandler;
      oldInvalidHandleHandler = _set_invalid_parameter_handler(newInvalidHandleHandler);
      return 0;
    }

    case TRI_WIN_INITIAL_SET_MAX_STD_IO: {
      int* newMax = (int*)(data);
      int result = _setmaxstdio(*newMax);
      if (result != *newMax) {
        return -1;
      }
      return 0;  
    }

    case TRI_WIN_INITIAL_WSASTARTUP_FUNCTION_CALL: {
      int errorCode;
      WSADATA wsaData;
      WORD wVersionRequested = MAKEWORD(2,2);
      errorCode = WSAStartup(wVersionRequested, &wsaData);
      if (errorCode != 0) {
        LOG_ERROR("Could not find a usuable Winsock DLL. WSAStartup returned an error.");
        return -1;
      }
      if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        LOG_ERROR("Could not find a usuable Winsock DLL. WSAStartup did not return version 2.2.");
        WSACleanup();
        return -1;
      }   
      return 0;
    }

    default: {
      LOG_ERROR("Invalid windows initialisation called");
      return -1;
    }
  }

  return -1;

}