//Activate the Previous Instance of our Application.
HWND CInstanceChecker::ActivatePreviousInstance(LPCTSTR lpCmdLine, ULONG_PTR dwCopyDataItemData, DWORD dwTimeout)
{
  //What will be the return value from this function (assume the worst)
  HWND hWindow = NULL;

  //Try to open the previous instances MMF
  HANDLE hPrevInstance = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, GetMMFFilename());
  if (hPrevInstance)
  {
    //Open up the MMF
    int nMMFSize = sizeof(CWindowInstance);
    CWindowInstance* pInstanceData = static_cast<CWindowInstance*>(MapViewOfFile(hPrevInstance, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, nMMFSize));
    if (pInstanceData) //Opening the MMF should work
    {
      //Lock the data prior to reading from it
      CSingleLock dataLock(&m_instanceDataMutex, TRUE);

      //activate the old window
      ASSERT(pInstanceData->hMainWnd); //Something gone wrong with the MMF
      hWindow = pInstanceData->hMainWnd;
	  if (::IsWindow(hWindow))
      {
        CWnd wndPrev;
        wndPrev.Attach(hWindow);
        CWnd* pWndChild = wndPrev.GetLastActivePopup();

        //Restore the focus to the previous instance and bring it to the foreground
        if (wndPrev.IsIconic())
          wndPrev.ShowWindow(SW_RESTORE);

        if (pWndChild)
          pWndChild->SetForegroundWindow();

        if (lpCmdLine)
        {  
          //Send the current apps command line to the previous instance using WM_COPYDATA
          COPYDATASTRUCT cds;
          cds.dwData = dwCopyDataItemData;
          DWORD dwCmdLength = static_cast<DWORD>(_tcslen(lpCmdLine) + 1);
          cds.cbData = dwCmdLength * sizeof(TCHAR); 
          TCHAR* pszLocalCmdLine = new TCHAR[dwCmdLength]; //We use a local buffer so that we can specify a constant parameter
                                                           //to this function
        #if (_MSC_VER >= 1400)
          _tcscpy_s(pszLocalCmdLine, dwCmdLength, lpCmdLine);
        #else                                                 
          _tcscpy(pszLocalCmdLine, lpCmdLine);
        #endif
          cds.lpData = pszLocalCmdLine;
          CWnd* pMainWindow = AfxGetMainWnd();
          HWND hSender = NULL;
          if (pMainWindow)
            hSender = pMainWindow->GetSafeHwnd();

          //Send the message to the previous instance. Use SendMessageTimeout instead of SendMessage to ensure we 
          //do not hang if the previous instance itself is hung
          DWORD_PTR dwResult = 0;
          if (SendMessageTimeout(hWindow, WM_COPYDATA, reinterpret_cast<WPARAM>(hSender), reinterpret_cast<LPARAM>(&cds),
                                 SMTO_ABORTIFHUNG, dwTimeout, &dwResult) == 0)
          {
            //Previous instance is not responding to messages
            hWindow = NULL;
          }

          //Tidy up the heap memory we have used
          delete [] pszLocalCmdLine;
        }

        //Detach the CWnd we were using
        wndPrev.Detach();
      }

      //Unmap the MMF we were using
      UnmapViewOfFile(pInstanceData);
    }

    //Close the file handle now that we 
    CloseHandle(hPrevInstance);

    //When we have activate the previous instance, we can release the lock
    ReleaseLock();
  }

  return hWindow;
}