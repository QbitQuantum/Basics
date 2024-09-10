VOID
DisplayReportGenerator(
  IN EFI_MENU_PAGE                *Page
  )
{

  EFI_STATUS               Status;
  EFI_FILE_DIALOG_CONTEXT *DialogContext;
  CHAR16                  *FileName;
  EFI_DIALOG_CONTEXT       MsgDialogContext;
  CHAR16                  *MsgDialogTitle;
  CHAR16                  *LogFilePath;

  DialogContext = NULL;
  //
  //allocate a new efi file dialog context.
  //
  Status = BS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_FILE_DIALOG_CONTEXT),
                 (VOID **)&DialogContext
                 );
  if (EFI_ERROR (Status)) {
    return;
  }

  BS->SetMem (DialogContext, sizeof(EFI_FILE_DIALOG_CONTEXT), 0);
  DialogContext->DialogType = EFI_FILE_DIALOG_TYPE_SAVE_FILE;
  DialogContext->FileType = EFI_FILTER_FILE_TYPE_CSV;

  //
  //get filename through FileDialog
  //
  Status = DoFileDialog (DialogContext);

  if (EFI_ERROR (Status)) {
    MsgDialogTitle = StrDuplicate (L"Generate Report Error!");
    MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;
    MenuPageRefresh (Page);
    DoDialog (MsgDialogTitle, &MsgDialogContext);
  } else if (DialogContext->DevicePath != NULL && DialogContext->FileName != NULL
      && DialogContext->FileName[0] != L'\0') {
    //
    //make up file name
    //
    if (StrLen (DialogContext->FileName) > 4 &&
      StriCmp (DialogContext->FileName + StrLen (DialogContext->FileName) - 4, L".csv") == 0) {
      FileName = StrDuplicate (DialogContext->FileName);
    } else if ( StrLen (DialogContext->FileName) > 1 &&
      StriCmp (DialogContext->FileName + StrLen (DialogContext->FileName) - 1, L".") == 0) {
      FileName = PoolPrint (L"%scsv", DialogContext->FileName);
    } else {
      FileName = PoolPrint (L"%s.csv", DialogContext->FileName);
    }
    if (FileName == NULL) {
      BS->FreePool (DialogContext->DevicePath);
      BS->FreePool (DialogContext->FileName);
      BS->FreePool (DialogContext);
      return;
    }

    MsgDialogTitle = StrDuplicate (L"Wait a few minutes...");
    MsgDialogContext.Type = EFI_DIALOG_TYPE_REMINDER;
    MenuPageRefresh (Page);
    DoDialog (MsgDialogTitle, &MsgDialogContext);

    LogFilePath = PoolPrint (
                    L"%s\\%s",
                    gFT->FilePath,
                    EFI_SCT_PATH_LOG
                    );
    if (LogFilePath == NULL) {
      return;
    }

    //
    // Generate the report file
    //
    Status = GenerateReport (
               gFT->DevicePath,
               LogFilePath,
               DialogContext->DevicePath,
               FileName
               );

    if (EFI_ERROR (Status)) {
      MsgDialogTitle = StrDuplicate (L"Generate Report Error!");
    } else {
      MsgDialogTitle = StrDuplicate (L"Generate Report Succeed!");
    }

    MsgDialogContext.Type = EFI_DIALOG_TYPE_MESSAGE;

    DoDialog (MsgDialogTitle, &MsgDialogContext);

    BS->FreePool (FileName);
    BS->FreePool (DialogContext->DevicePath);
    BS->FreePool (DialogContext->FileName);
  } else {
    if (DialogContext->FileName != NULL) {
      BS->FreePool (DialogContext->FileName);
    }
    if (DialogContext->DevicePath != NULL) {
      BS->FreePool (DialogContext->DevicePath);
    }
  }

  BS->FreePool (DialogContext);
  MenuPageRefresh (Page);
  return;
}