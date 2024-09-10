BOOLEAN AddFileSaveList(PFILEINFOSET lpFileInfoSet)
{
  PFILEINFO       lpFileInfo, lpFileInfoIn;
  ULONG           dwSize, dwSizeOfItem, dwSizeOfItemNew;
  PWSTR           pwszNtFileName;
  ULONG           dwSizeOfNtFileName;
  ANSI_STRING     FileNameAnsi;
  UNICODE_STRING  FileNameUni;

  if (!_MmIsAddressValid(lpFileInfoSet))
    return FALSE;
  if (lpFileInfoSet->dwSize < SIZEOF_FILEINFOSET)
    return FALSE;

  MUTEX_WAIT(LockMutexToFileSaveList);

  DbgPrintSO(("He4HookInv: AddFileSaveList: Start!!!\n"));
  if (!_MmIsAddressValid(pSaveList))
  {
    pSaveList = new KDLinkedList(NULL);
    if (pSaveList == NULL)
    {
      DbgPrintSO(("He4HookInv: AddFileSaveList: File list create ERROR!!!\n"));
      MUTEX_RELEASE(LockMutexToFileSaveList);
      return FALSE;
    }
  }

  if (!_MmIsAddressValid(pDirTree))
  {
    pDirTree = new KShieldDirectoryTree();
    if (pDirTree == NULL)
    {
      DbgPrintSO(("He4HookInv: AddFileSaveList: KShieldDirectoryTree create ERROR!!!\n"));
      MUTEX_RELEASE(LockMutexToFileSaveList);
      return FALSE;
    }
  }

  DbgPrintSO(("He4HookInv: AddFileSaveList: List created OK!!!\n"));

  dwSize = lpFileInfoSet->dwSize - (SIZEOF_FILEINFOSET - SIZEOF_FILEINFO);
  lpFileInfoIn = &lpFileInfoSet->FileInfo[0];
  while(dwSize > SIZEOF_FILEINFO)
  {
    if (!CheckFileInfo(lpFileInfoIn))
      break;
    dwSizeOfItem = ((SIZEOF_FILEINFO-sizeof(CHAR)) + lpFileInfoIn->dwSizeAllNamesArea);
    if (lpFileInfoIn->dwSizeAnsiName > sizeof(CHAR))
    {
      pwszNtFileName = (PWSTR)_AllocatePoolFromKHeap(hKHeapSOFileList, sizeof(WCHAR)*lpFileInfoIn->dwSizeAnsiName+2048);
      if (pwszNtFileName)
      {
        RtlInitAnsiString(&FileNameAnsi, lpFileInfoIn->szNames+lpFileInfoIn->dwOffsetToAnsiName);
        RtlAnsiStringToUnicodeString(&FileNameUni, &FileNameAnsi, TRUE);
        dwSizeOfNtFileName = DosPathNameToNtPathName(FileNameUni.Buffer, pwszNtFileName, sizeof(WCHAR)*lpFileInfoIn->dwSizeAnsiName+2048, 255, NULL);
        RtlFreeUnicodeString(&FileNameUni);

        if (dwSizeOfNtFileName)
        {
          dwSizeOfNtFileName += sizeof(WCHAR);
          dwSizeOfItemNew = (SIZEOF_FILEINFO-sizeof(CHAR)) + lpFileInfoIn->dwSizeAnsiName + dwSizeOfNtFileName;
          
          #define ADD_NT_PATH   L"\\??\\"
          //L"\\DosDevices\\"
          //L"\\??\\"
          
          if (lpFileInfoIn->dwAccessType & FILE_ACC_TYPE_EXCHANGE)
          {
            if (lpFileInfoIn->dwSizeAnsiChangedName > sizeof(CHAR))
            {
              dwSizeOfItemNew += sizeof(WCHAR)*lpFileInfoIn->dwSizeAnsiChangedName + sizeof(ADD_NT_PATH)-sizeof(WCHAR);
            }
            else
            {
              if (lpFileInfoIn->dwSizeUniChangedName > sizeof(WCHAR))
                dwSizeOfItemNew += lpFileInfoIn->dwSizeUniChangedName;
            }
          }
          
          lpFileInfo = (PFILEINFO)_AllocatePoolFromKHeap(hKHeapSOFileList, dwSizeOfItemNew+sizeof(WCHAR));
          if (lpFileInfo)
          {
            memset(lpFileInfo, 0, dwSizeOfItemNew+sizeof(WCHAR));
            lpFileInfo->dwAccessType = lpFileInfoIn->dwAccessType;
            lpFileInfo->dwSizeAllNamesArea = dwSizeOfItemNew - (SIZEOF_FILEINFO-sizeof(CHAR));
          
            lpFileInfo->dwOffsetToAnsiName = 0;
            lpFileInfo->dwSizeAnsiName = lpFileInfoIn->dwSizeAnsiName;
          
            RtlCopyMemory(lpFileInfo->szNames+lpFileInfo->dwOffsetToAnsiName,
                          lpFileInfoIn->szNames+lpFileInfoIn->dwOffsetToAnsiName,
                          lpFileInfo->dwSizeAnsiName);
          
            lpFileInfo->dwOffsetToUniName = lpFileInfo->dwOffsetToAnsiName + lpFileInfo->dwSizeAnsiName;
            lpFileInfo->dwSizeUniName = dwSizeOfNtFileName;
          
            RtlCopyMemory(lpFileInfo->szNames+lpFileInfo->dwOffsetToUniName, pwszNtFileName, dwSizeOfNtFileName);
          
            if (lpFileInfoIn->dwAccessType & FILE_ACC_TYPE_EXCHANGE)
            {
              if (lpFileInfoIn->dwSizeAnsiChangedName > sizeof(CHAR))
              {
                lpFileInfo->dwOffsetToUniChangedName = lpFileInfo->dwOffsetToUniName + lpFileInfo->dwSizeUniName;
                lpFileInfo->dwSizeUniChangedName = sizeof(WCHAR)*lpFileInfoIn->dwSizeAnsiChangedName+sizeof(ADD_NT_PATH)-sizeof(WCHAR);
          
                RtlInitAnsiString(&FileNameAnsi, lpFileInfoIn->szNames+lpFileInfoIn->dwOffsetToAnsiChangedName);
                RtlAnsiStringToUnicodeString(&FileNameUni, &FileNameAnsi, TRUE);
          
                RtlCopyMemory(lpFileInfo->szNames+lpFileInfo->dwOffsetToUniChangedName, ADD_NT_PATH, sizeof(ADD_NT_PATH));
                RtlCopyMemory((lpFileInfo->szNames+lpFileInfo->dwOffsetToUniChangedName+sizeof(ADD_NT_PATH)-sizeof(WCHAR)), FileNameUni.Buffer,
                              (sizeof(WCHAR)*lpFileInfoIn->dwSizeAnsiChangedName) < (FileNameUni.Length+sizeof(WCHAR)) ? (sizeof(WCHAR)*lpFileInfoIn->dwSizeAnsiChangedName) : (FileNameUni.Length+sizeof(WCHAR)));
                RtlFreeUnicodeString(&FileNameUni);
              }
              else
              {
                if (lpFileInfoIn->dwSizeUniChangedName > sizeof(WCHAR))
                {
                  lpFileInfo->dwOffsetToUniChangedName = lpFileInfo->dwOffsetToUniName + lpFileInfo->dwSizeUniName;
                  lpFileInfo->dwSizeUniChangedName = lpFileInfoIn->dwSizeUniChangedName;
                
                  RtlCopyMemory(
                                lpFileInfo->szNames+lpFileInfo->dwOffsetToUniChangedName,
                                lpFileInfoIn->szNames+lpFileInfoIn->dwOffsetToUniChangedName,
                                lpFileInfo->dwSizeUniChangedName
                               );
                }
                else
                {
                  lpFileInfo->dwAccessType &= ~FILE_ACC_TYPE_EXCHANGE;
                }
              }
            }

            PVOID pContext;
            if (pDirTree->Find((PWSTR)(lpFileInfo->szNames+lpFileInfo->dwOffsetToUniName), &pContext) == NULL)
            {
              DbgPrintSO(("He4HookInv: AddFileSaveList: %s, type = %x\n", lpFileInfo->szNames+lpFileInfo->dwOffsetToAnsiName, lpFileInfo->dwAccessType));
              if (pDirTree->Add((PWSTR)(lpFileInfo->szNames+lpFileInfo->dwOffsetToUniName), (PVOID)lpFileInfo) == TRUE)
              {
                if (pSaveList->AddTailObject(lpFileInfo) == FALSE)
                {
                  pDirTree->Remove((PWSTR)(lpFileInfo->szNames+lpFileInfo->dwOffsetToUniName), NULL);
                  FreePoolToKHeap(hKHeapSOFileList, lpFileInfo); 
                }
              }
              else
              {
                FreePoolToKHeap(hKHeapSOFileList, lpFileInfo); 
              }
            }
            else
            {
              FreePoolToKHeap(hKHeapSOFileList, lpFileInfo); 
            }
          }
        }
        FreePoolToKHeap(hKHeapSOFileList, pwszNtFileName);
      }
    }
    dwSize -= dwSizeOfItem;
    lpFileInfoIn = (PFILEINFO)((PCHAR)lpFileInfoIn + dwSizeOfItem);
  }

  MUTEX_RELEASE(LockMutexToFileSaveList);

  return TRUE;
}