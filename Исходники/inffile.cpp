BOOL InfFile::UninstallFiles(const char *pFilesSection) const
{
  if (!pPath)
    return FALSE;

  int res;
  HINF hInf;

  do {
    res = IDCONTINUE;

    UINT errLine;
    hInf = SetupOpenInfFile(pPath, NULL, INF_STYLE_WIN4, &errLine);

    if (hInf == INVALID_HANDLE_VALUE)
      res = ShowLastError(MB_CANCELTRYCONTINUE, "SetupOpenInfFile(%s) on line %u", pPath, errLine);
  } while (res == IDTRYAGAIN);

  if (res != IDCONTINUE)
    return FALSE;

  do {
    res = IDCONTINUE;

    HSPFILEQ hFileQueue = SetupOpenFileQueue();

    if (hFileQueue != INVALID_HANDLE_VALUE) {
      if (SetupQueueDeleteSection(hFileQueue, hInf, NULL, pFilesSection)) {
        PVOID pContext = SetupInitDefaultQueueCallback(NULL);

        if (pContext) {
          if(!SetupCommitFileQueue(NULL, hFileQueue, FileCallback, pContext))
            res = ShowLastError(MB_CANCELTRYCONTINUE, "SetupCommitFileQueue()");

          SetupTermDefaultQueueCallback(pContext);
        } else {
          res = ShowLastError(MB_CANCELTRYCONTINUE, "SetupInitDefaultQueueCallback()");
        }
      } else {
        res = ShowLastError(MB_CANCELTRYCONTINUE, "SetupQueueDeleteSection(%s)", pFilesSection);
      }

      SetupCloseFileQueue(hFileQueue);
    } else {
      res = ShowLastError(MB_CANCELTRYCONTINUE, "SetupOpenFileQueue()");
    }
  } while (res == IDTRYAGAIN);

  SetupCloseInfFile(hInf);

  if (res != IDCONTINUE)
    return FALSE;

  return TRUE;
}