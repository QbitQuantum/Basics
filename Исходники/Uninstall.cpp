BOOL DeleteDirectory(const WCHAR* sPathToDelete)
{
  BOOL            bResult = TRUE;
  HANDLE          hFile;
  WCHAR           sFilePath[MAX_PATH];
  WCHAR           sPattern[MAX_PATH];
  WIN32_FIND_DATA findData;

  wcscpy(sPattern, sPathToDelete);
  wcscat(sPattern, L"\\*.*");
  hFile = FindFirstFile(sPattern, &findData);
  if (hFile != INVALID_HANDLE_VALUE)
  {
    do
    {
      if (findData.cFileName[0] != L'.')
      {
        _snwprintf(sFilePath, MAX_PATH, L"%s\\%s", sPathToDelete, findData.cFileName);

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
          // Delete subdirectory
          if (!DeleteDirectory(sFilePath))
            bResult = FALSE;
        }
        else
        {
          // Set file attributes
          if (SetFileAttributes(sFilePath, FILE_ATTRIBUTE_NORMAL))
          {
            // Delete file
            if (!DeleteFile(sFilePath) && nTotalRetries < c_nMaxTotalRetries)
            {
              BOOL bDeleted = FALSE;
              nTotalRetries++;
              for (int nRetry = 0; nRetry < c_nMaxOneFileRetries; nRetry++)
              {
                Sleep(c_nRetryDelay);
                if (DeleteFile(sFilePath))
                {
                  bDeleted = TRUE;
                  break;
                }
              }
              if (!bDeleted)
                bResult = FALSE;
            }
          }
        }
      }
    } while (FindNextFile(hFile, &findData));

    // Close handle
    FindClose(hFile);
  }

  // Set directory attributes
  if (SetFileAttributes(sPathToDelete, FILE_ATTRIBUTE_NORMAL))
  {
    g_nDirsDeleted++;
    UpdateProgress();
    // Delete directory
    if (!RemoveDirectory(sPathToDelete) && nTotalRetries < c_nMaxTotalRetries)
    {
      BOOL bDeleted = FALSE;
      nTotalRetries++;
      for (int nRetry = 0; nRetry < c_nMaxOneFileRetries; nRetry++)
      {
        Sleep(c_nRetryDelay);
        if (RemoveDirectory(sPathToDelete))
        {
          bDeleted = TRUE;
          break;
        }
      }
      if (!bDeleted)
        bResult = FALSE;
    }
  }

  return bResult;
}