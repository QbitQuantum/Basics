    bool TryToCreateProcessForCurrentApp(const std::string & restartParam, const std::string & additionalParams)
    {
#if GUSLIB_PLATFORM_TYPE == GUSLIB_PLATFORM_TYPE_WINDOWS
      TCHAR szAppPath[MAX_PATH] = { 0 };
      GetModuleFileName(NULL, szAppPath, MAX_PATH);

      STARTUPINFO        si = { 0 };
      PROCESS_INFORMATION    pi = { 0 };
      si.cb = sizeof(STARTUPINFO);
      // Create New Instance command line
      // Copy the application path, including the application's name itself.
      // If the path includes white space, use of qutation marks is required.
      bool bSpace = false;
      int nLen = static_cast<int>(wcslen(szAppPath));
      for (int i = 0; i < nLen && !bSpace; ++i)
      {
        if (szAppPath[i] == L' ')
        {
          bSpace = true;
        }
      }

      if (bSpace)
      {
        for (int i = nLen + 1; i > 1 && i < MAX_PATH; --i)
        {
          szAppPath[i] = szAppPath[i - 1];
        }
        szAppPath[nLen + 1] = '\"';
        szAppPath[0] = '\"';
      }

      // Now add the application's parameters, separated by space.

      wcscat_s(szAppPath, MAX_PATH, L" ");
      wcscat_s(szAppPath, MAX_PATH, stringutil::StringToWString(restartParam).c_str());

      wchar_t wszTempString[MAX_PATH];
      size_t numCharsWritten;
      mbstowcs_s(&numCharsWritten, wszTempString, MAX_PATH, additionalParams.c_str(), additionalParams.length());

      wcscat_s(szAppPath, MAX_PATH, wszTempString);

      // Create another copy of processS
      bool bResult = CreateProcess(NULL, szAppPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
      return (bResult == true);
#else
      return false;
#endif
    }