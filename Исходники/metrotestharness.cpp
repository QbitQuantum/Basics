static bool Launch()
{
  Log(L"Launching browser...");

  DWORD processID;

  // The interface that allows us to activate the browser
  CComPtr<IApplicationActivationManager> activateMgr;
  if (FAILED(CoCreateInstance(CLSID_ApplicationActivationManager, NULL,
                              CLSCTX_LOCAL_SERVER,
                              IID_IApplicationActivationManager,
                              (void**)&activateMgr))) {
    Fail(L"CoCreateInstance CLSID_ApplicationActivationManager failed.");
    return false;
  }
  
  HRESULT hr;
  WCHAR appModelID[256];
  // Activation is based on the browser's registered app model id
  if (!GetDefaultBrowserAppModelID(appModelID, (sizeof(appModelID)/sizeof(WCHAR)))) {
    Fail(L"GetDefaultBrowserAppModelID failed.");
    return false;
  }
  Log(L"App model id='%s'", appModelID);

  // Hand off focus rights if the terminal has focus to the out-of-process
  // activation server (explorer.exe). Without this the metro interface
  // won't launch.
  if (GetForegroundWindow() == GetConsoleWindow()) {
    hr = CoAllowSetForegroundWindow(activateMgr, NULL);
    if (FAILED(hr)) {
      Fail(L"CoAllowSetForegroundWindow result %X", hr);
      return false;
    }
  }

  Log(L"Harness process id: %d", GetCurrentProcessId());

  // Because we can't pass command line args, we store params in a
  // tests.ini file in dist/bin which the browser picks up on launch.
  CStringA testFilePath;
  if (sFirefoxPath.GetLength()) {
    // Use the firefoxpath passed to us by the test harness
    int index = sFirefoxPath.ReverseFind('\\');
    if (index == -1) {
      Fail(L"Bad firefoxpath path");
      return false;
    }
    testFilePath = sFirefoxPath.Mid(0, index);
    testFilePath += "\\";
    testFilePath += kMetroTestFile;
  } else {
    // Use the module path
    char path[MAX_PATH];
    if (!GetModuleFileNameA(NULL, path, MAX_PATH)) {
      Fail(L"GetModuleFileNameA errorno=%d", GetLastError());
      return false;
    }
    char* slash = strrchr(path, '\\');
    if (!slash)
      return false;
    *slash = '\0'; // no trailing slash
    testFilePath = path;
    testFilePath += "\\";
    testFilePath += kMetroTestFile;
  }

  Log(L"Writing out tests.ini to: '%s'", CStringW(testFilePath));
  HANDLE hTestFile = CreateFileA(testFilePath, GENERIC_WRITE,
                                 0, NULL, CREATE_ALWAYS,
                                 FILE_ATTRIBUTE_NORMAL,
                                 NULL);
  if (hTestFile == INVALID_HANDLE_VALUE) {
    Fail(L"CreateFileA errorno=%d", GetLastError());
    return false;
  }

  DeleteTestFileHelper dtf(testFilePath);

  CStringA asciiParams = sAppParams;
  if (!WriteFile(hTestFile, asciiParams, asciiParams.GetLength(), NULL, 0)) {
    CloseHandle(hTestFile);
    Fail(L"WriteFile errorno=%d", GetLastError());
    return false;
  }
  FlushFileBuffers(hTestFile);
  CloseHandle(hTestFile);

  // Create a named stdout pipe for the browser
  if (!SetupTestOutputPipe()) {
    Fail(L"SetupTestOutputPipe failed (errno=%d)", GetLastError());
    return false;
  }

  // Launch firefox
  hr = activateMgr->ActivateApplication(appModelID, L"", AO_NOERRORUI, &processID);
  if (FAILED(hr)) {
    Fail(L"ActivateApplication result %X", hr);
    return false;
  }

  Log(L"Activation succeeded. processid=%d", processID);

  HANDLE child = OpenProcess(SYNCHRONIZE, FALSE, processID);
  if (!child) {
    Fail(L"Couldn't find child process. (%d)", GetLastError());
    return false;
  }

  Log(L"Waiting on child process...");

  MSG msg;
  DWORD waitResult = WAIT_TIMEOUT;
  HANDLE handles[2] = { child, gTestOutputPipe };
  while ((waitResult = MsgWaitForMultipleObjects(2, handles, FALSE, INFINITE, QS_ALLINPUT)) != WAIT_OBJECT_0) {
    if (waitResult == WAIT_FAILED) {
      Log(L"Wait failed (errno=%d)", GetLastError());
      break;
    } else if (waitResult == WAIT_OBJECT_0 + 1) {
      ReadPipe();
    } else if (waitResult == WAIT_OBJECT_0 + 2 &&
               PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  ReadPipe();
  CloseHandle(gTestOutputPipe);
  CloseHandle(child);

  Log(L"Exiting.");
  return true;
}