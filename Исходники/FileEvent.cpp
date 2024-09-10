UINT CFileEvent::FileEventProc (LPVOID lpParam)
  {
    CFileEvent *pFileEvent = (CFileEvent*) lpParam;
    int nFilePathCount = pFileEvent->m_lstFilePath.GetCount ();
    HANDLE *phChanges = new HANDLE[nFilePathCount + 1];
    for (int i;;)
      {
        *phChanges = pFileEvent->m_evWatching;
        POSITION pos = pos = pFileEvent->m_lstFilePath.GetHeadPosition ();
        CFilePath *pFilePath;
        int j = 0;
        for (i = 0; i < nFilePathCount; i++)
          {
            if (!pos)
              {
                nFilePathCount = i;
                break;
              }
            pFilePath = pFileEvent->m_lstFilePath.GetNext (pos);
            ASSERT (pFilePath);
            HANDLE hFC = FindFirstChangeNotification (pFilePath->GetPath(), FALSE,
              FILE_NOTIFY_CHANGE_LAST_WRITE|FILE_NOTIFY_CHANGE_SIZE|FILE_NOTIFY_CHANGE_FILE_NAME);
            if (hFC != INVALID_HANDLE_VALUE) // if i can gen a notification --
              phChanges[++j] = hFC;
          }
        DWORD dwResult = WaitForMultipleObjects (j + 1, phChanges, FALSE, INFINITE);
        for (i = 1; i < j; i++)
          VERIFY (FindCloseChangeNotification (phChanges[i + 1]));
        if (dwResult == WAIT_OBJECT_0)
          break;
        int nPath = dwResult - WAIT_OBJECT_0 - 1;
        pos = pFileEvent->m_lstFilePath.FindIndex (nPath);
        //ASSERT (pos);
		if(pos == 0)
		{
			break;
		}
        pFilePath = pFileEvent->m_lstFilePath.GetAt (pos);
        //ASSERT (pFilePath);
		if(pFilePath == NULL)
		{
			break;
		}
        CString sPathName;
        CFileInfo *pFileInfo;
        for (pos = pFileEvent->m_mapFileInfo.GetStartPosition (); pos;)
          {
            pFileEvent->m_mapFileInfo.GetNextAssoc (pos, sPathName, pFileInfo);
            ASSERT (pFileInfo);
            if (!_tcscmp (pFilePath->GetPath (), pFileInfo->GetPath ()))
              {
                HANDLE hFile = CreateFile (sPathName, GENERIC_READ, FILE_SHARE_READ /*|FILE_SHARE_WRITE|FILE_SHARE_DELETE*/,
                  NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				// add at 2006-05-06 by blueant
				if (hFile == INVALID_HANDLE_VALUE)
				{
					// 文件保存过程中很大情况下返回的是无效句柄,需要延迟一段时间等保存完毕再打开
					Sleep(50);
					hFile = CreateFile (sPathName, GENERIC_READ, FILE_SHARE_READ /*|FILE_SHARE_WRITE|FILE_SHARE_DELETE*/,
						NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				}
                if (hFile != INVALID_HANDLE_VALUE)
                  {
                    FILETIME ftModified;
                    VERIFY (GetFileTime (hFile, NULL, NULL, &ftModified));
                    DWORD dwSize;
					// ->HE
					dwSize= GetFileSize (hFile, NULL);
					ASSERT(dwSize != (DWORD)-1);
					// <-HE
                   CloseHandle (hFile);
                    WPARAM wEvent = FE_NONE;
                    if (CompareFileTime (&pFileInfo->GetModified (), &ftModified) < 0)
                      {
                        pFileInfo->SetModified (ftModified);
                        wEvent |= FE_CHANGED_TIME;
                      }
                    if (pFileInfo->GetSize () != dwSize)
                      {
                        pFileInfo->SetSize (dwSize);
                        wEvent |= FE_CHANGED_SIZE;
                      }
                    if (wEvent)
                      pFileEvent->OnFileEvent (wEvent, sPathName);
                  }
                else
                  {
                    pFileEvent->OnFileEvent (FE_DELETED, sPathName);
                    pFileEvent->RemoveFile (sPathName);
                  }
              }
          }
      }
    delete [] phChanges;
    return 0;
  }