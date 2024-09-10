/**
  function to take a list of files to copy and a destination location and do
  the verification and copying of those files to that location.  This function
  will report any errors to the user and halt.

  The key is to have this function called ONLY once.  this allows for the parameter
  verification to happen correctly.

  @param[in] FileList           A LIST_ENTRY* based list of files to move.
  @param[in] DestDir            The destination location.
  @param[in] SilentMode         TRUE to eliminate screen output.
  @param[in] RecursiveMode      TRUE to copy directories.
  @param[in] Resp               The response to the overwrite query (if always).

  @retval SHELL_SUCCESS             the files were all moved.
  @retval SHELL_INVALID_PARAMETER   a parameter was invalid
  @retval SHELL_SECURITY_VIOLATION  a security violation ocurred
  @retval SHELL_WRITE_PROTECTED     the destination was write protected
  @retval SHELL_OUT_OF_RESOURCES    a memory allocation failed
**/
SHELL_STATUS
EFIAPI
ValidateAndCopyFiles(
  IN CONST EFI_SHELL_FILE_INFO  *FileList,
  IN CONST CHAR16               *DestDir,
  IN BOOLEAN                    SilentMode,
  IN BOOLEAN                    RecursiveMode,
  IN VOID                       **Resp
  )
{
  CHAR16                    *HiiOutput;
  CHAR16                    *HiiResultOk;
  CONST EFI_SHELL_FILE_INFO *Node;
  SHELL_STATUS              ShellStatus;
  CHAR16                    *DestPath;
  VOID                      *Response;
  UINTN                     PathLen;
  CONST CHAR16              *Cwd;
  CONST CHAR16              *TempLocation;
  UINTN                     NewSize;

  if (Resp == NULL) {
    Response = NULL;
  } else {
    Response = *Resp;
  }

  DestPath    = NULL;
  ShellStatus = SHELL_SUCCESS;
  PathLen     = 0;
  Cwd         = ShellGetCurrentDir(NULL);

  ASSERT(FileList != NULL);
  ASSERT(DestDir  != NULL);

  //
  // We already verified that this was present.
  //
  ASSERT(Cwd      != NULL);

  //
  // If we are trying to copy multiple files... make sure we got a directory for the target...
  //
  if (EFI_ERROR(ShellIsDirectory(DestDir)) && FileList->Link.ForwardLink != FileList->Link.BackLink) {
    //
    // Error for destination not a directory
    //
    ShellPrintHiiEx(-1, -1, NULL, STRING_TOKEN (STR_GEN_NOT_DIR), gShellLevel2HiiHandle, DestDir);
    return (SHELL_INVALID_PARAMETER);
  }
  for (Node = (EFI_SHELL_FILE_INFO *)GetFirstNode(&FileList->Link)
    ;  !IsNull(&FileList->Link, &Node->Link)
    ;  Node = (EFI_SHELL_FILE_INFO *)GetNextNode(&FileList->Link, &Node->Link)
    ){
    //
    // skip the directory traversing stuff...
    //
    if (StrCmp(Node->FileName, L".") == 0 || StrCmp(Node->FileName, L"..") == 0) {
      continue;
    }

    NewSize =  StrSize(DestDir);
    NewSize += StrSize(Node->FullName);
    NewSize += StrSize(Cwd);
    if (NewSize > PathLen) {
      PathLen = NewSize;
    }

    //
    // Make sure got -r if required
    //
    if (!RecursiveMode && !EFI_ERROR(ShellIsDirectory(Node->FullName))) {
      ShellPrintHiiEx(-1, -1, NULL, STRING_TOKEN (STR_CP_DIR_REQ), gShellLevel2HiiHandle);
      return (SHELL_INVALID_PARAMETER);
    }

    //
    // make sure got dest as dir if needed
    //
    if (!EFI_ERROR(ShellIsDirectory(Node->FullName)) && EFI_ERROR(ShellIsDirectory(DestDir))) {
      //
      // Error for destination not a directory
      //
      ShellPrintHiiEx(-1, -1, NULL, STRING_TOKEN (STR_GEN_NOT_DIR), gShellLevel2HiiHandle, DestDir);
      return (SHELL_INVALID_PARAMETER);
    }
  }

  HiiOutput   = HiiGetString (gShellLevel2HiiHandle, STRING_TOKEN (STR_CP_OUTPUT), NULL);
  HiiResultOk = HiiGetString (gShellLevel2HiiHandle, STRING_TOKEN (STR_GEN_RES_OK), NULL);
  DestPath    = AllocateZeroPool(PathLen);

  if (DestPath == NULL || HiiOutput == NULL || HiiResultOk == NULL) {
    SHELL_FREE_NON_NULL(DestPath);
    SHELL_FREE_NON_NULL(HiiOutput);
    SHELL_FREE_NON_NULL(HiiResultOk);
    return (SHELL_OUT_OF_RESOURCES);
  }

  //
  // Go through the list of files to copy...
  //
  for (Node = (EFI_SHELL_FILE_INFO *)GetFirstNode(&FileList->Link)
    ;  !IsNull(&FileList->Link, &Node->Link)
    ;  Node = (EFI_SHELL_FILE_INFO *)GetNextNode(&FileList->Link, &Node->Link)
    ){
    if (ShellGetExecutionBreakFlag()) {
      break;
    }
    ASSERT(Node->FileName != NULL);
    ASSERT(Node->FullName != NULL);

    //
    // skip the directory traversing stuff...
    //
    if (StrCmp(Node->FileName, L".") == 0 || StrCmp(Node->FileName, L"..") == 0) {
      continue;
    }

    if (FileList->Link.ForwardLink == FileList->Link.BackLink // 1 item
      && EFI_ERROR(ShellIsDirectory(DestDir))                 // not an existing directory
      ) {
      if (StrStr(DestDir, L":") == NULL) {
        //
        // simple copy of a single file
        //
        StrCpy(DestPath, Cwd);
        if (DestPath[StrLen(DestPath)-1] != L'\\' && DestDir[0] != L'\\') {
          StrCat(DestPath, L"\\");
        } else if (DestPath[StrLen(DestPath)-1] == L'\\' && DestDir[0] == L'\\') {
          ((CHAR16*)DestPath)[StrLen(DestPath)-1] = CHAR_NULL;
        }
        StrCat(DestPath, DestDir);
      } else {
        StrCpy(DestPath, DestDir);
      }
    } else {
      //
      // we have multiple files or a directory in the DestDir
      //
      
      //
      // Check for leading slash
      //
      if (DestDir[0] == L'\\') {
          //
          // Copy to the root of CWD
          //
        StrCpy(DestPath, Cwd);
        while (PathRemoveLastItem(DestPath));
        StrCat(DestPath, DestDir+1);
        StrCat(DestPath, Node->FileName);
      } else if (StrStr(DestDir, L":") == NULL) {
        StrCpy(DestPath, Cwd);
        if (DestPath[StrLen(DestPath)-1] != L'\\' && DestDir[0] != L'\\') {
          StrCat(DestPath, L"\\");
        } else if (DestPath[StrLen(DestPath)-1] == L'\\' && DestDir[0] == L'\\') {
          ((CHAR16*)DestPath)[StrLen(DestPath)-1] = CHAR_NULL;
        }
        StrCat(DestPath, DestDir);
        if (DestDir[StrLen(DestDir)-1] != L'\\' && Node->FileName[0] != L'\\') {
          StrCat(DestPath, L"\\");
        } else if (DestDir[StrLen(DestDir)-1] == L'\\' && Node->FileName[0] == L'\\') {
          ((CHAR16*)DestPath)[StrLen(DestPath)-1] = CHAR_NULL;
        }
        StrCat(DestPath, Node->FileName);

      } else {
        StrCpy(DestPath, DestDir);
        if (DestDir[StrLen(DestDir)-1] != L'\\' && Node->FileName[0] != L'\\') {
          StrCat(DestPath, L"\\");
        } else if (DestDir[StrLen(DestDir)-1] == L'\\' && Node->FileName[0] == L'\\') {
          ((CHAR16*)DestDir)[StrLen(DestDir)-1] = CHAR_NULL;
        }
        StrCat(DestPath, Node->FileName);
      }
    }

    //
    // Make sure the path exists
    //
    if (EFI_ERROR(VerifyIntermediateDirectories(DestPath))) {
      ShellPrintHiiEx(-1, -1, NULL, STRING_TOKEN (STR_CP_DIR_WNF), gShellLevel2HiiHandle);
      ShellStatus = SHELL_DEVICE_ERROR;
      break;
    }

    if ( !EFI_ERROR(ShellIsDirectory(Node->FullName))
      && !EFI_ERROR(ShellIsDirectory(DestPath))
      && StrniCmp(Node->FullName, DestPath, StrLen(DestPath)) == NULL
      ){
      ShellPrintHiiEx(-1, -1, NULL, STRING_TOKEN (STR_CP_SD_PARENT), gShellLevel2HiiHandle);
      ShellStatus = SHELL_INVALID_PARAMETER;
      break;
    }
    if (StringNoCaseCompare(&Node->FullName, &DestPath) == 0) {
      ShellPrintHiiEx(-1, -1, NULL, STRING_TOKEN (STR_CP_SD_SAME), gShellLevel2HiiHandle);
      ShellStatus = SHELL_INVALID_PARAMETER;
      break;
    }

    if ((TempLocation = StrniCmp(Node->FullName, DestPath, StrLen(Node->FullName))) == 0
      && (DestPath[StrLen(Node->FullName)] == CHAR_NULL || DestPath[StrLen(Node->FullName)] == L'\\')
      ) {
      ShellPrintHiiEx(-1, -1, NULL, STRING_TOKEN (STR_CP_SD_SAME), gShellLevel2HiiHandle);
      ShellStatus = SHELL_INVALID_PARAMETER;
      break;
    }

    PathCleanUpDirectories(DestPath);

    ShellPrintEx(-1, -1, HiiOutput, Node->FullName, DestPath);

    //
    // copy single file...
    //
    ShellStatus = CopySingleFile(Node->FullName, DestPath, &Response, SilentMode);
    if (ShellStatus != SHELL_SUCCESS) {
      break;
    }
  }
  if (ShellStatus == SHELL_SUCCESS && Resp == NULL) {
    ShellPrintEx(-1, -1, L"%s", HiiResultOk);
  }

  SHELL_FREE_NON_NULL(DestPath);
  SHELL_FREE_NON_NULL(HiiOutput);
  SHELL_FREE_NON_NULL(HiiResultOk);
  if (Resp == NULL) {
    SHELL_FREE_NON_NULL(Response);
  }

  return (ShellStatus);

}