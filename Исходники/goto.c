EFI_STATUS
EFIAPI
SEnvCmdGoto (
  IN  EFI_HANDLE               ImageHandle,
  IN  EFI_SYSTEM_TABLE         *SystemTable
  )
/*++

Routine Description:

  Transfers execution of batch file to location following a label (:labelname).

Arguments:
  ImageHandle      The image handle
  SystemTable      The system table

Returns:
  EFI_SUCCESS      The command finished sucessfully
  EFI_UNSUPPORTED  Unsupported
  EFI_INVALID_PARAMETER Invalid parameter
  EFI_OUT_OF_RESOURCES  Out of resources
  
--*/
{
  EFI_STATUS  Status;

  EFI_SHELL_APP_INIT (ImageHandle, SystemTable);

  //
  //  Output help
  //
  if (SI->Argc == 2) {
    if (StriCmp (SI->Argv[1], L"-?") == 0) {
      if (IS_OLD_SHELL) {
        PrintToken (STRING_TOKEN (STR_NO_HELP), HiiEnvHandle);
      } else {
        PrintToken (STRING_TOKEN (STR_SHELLENV_GOTO_VERBOSE_HELP), HiiEnvHandle);
      }

      return EFI_SUCCESS;
    }
  } else if (SI->Argc == 3) {
    if ((StriCmp (SI->Argv[1], L"-?") == 0 && StriCmp (SI->Argv[2], L"-b") == 0) ||
        (StriCmp (SI->Argv[2], L"-?") == 0 && StriCmp (SI->Argv[1], L"-b") == 0)
        ) {
      EnablePageBreak (DEFAULT_INIT_ROW, DEFAULT_AUTO_LF);
      if (IS_OLD_SHELL) {
        PrintToken (STRING_TOKEN (STR_NO_HELP), HiiEnvHandle);
      } else {
        PrintToken (STRING_TOKEN (STR_SHELLENV_GOTO_VERBOSE_HELP), HiiEnvHandle);
      }

      return EFI_SUCCESS;
    }
  }

  if (!SEnvBatchIsActive ()) {
    PrintToken (STRING_TOKEN (STR_SHELLENV_GOTO_ONLY_SUPPORTED_SCRIPT), HiiEnvHandle);
    return EFI_UNSUPPORTED;
  }

  if (SI->Argc > 2) {
    PrintToken (STRING_TOKEN (STR_SHELLENV_GOTO_TOO_MANY_ARGS), HiiEnvHandle, SEnvGetLineNumber ());
    SEnvSetBatchAbort ();
    return EFI_INVALID_PARAMETER;
  }

  if (SI->Argc < 2) {
    PrintToken (STRING_TOKEN (STR_SHELLENV_GOTO_TOO_FEW_ARGS), HiiEnvHandle, SEnvGetLineNumber ());
    SEnvSetBatchAbort ();
    return EFI_INVALID_PARAMETER;
  }

  TargetLabel = StrDuplicate (SI->Argv[1]);
  if (TargetLabel == NULL) {
    PrintToken (STRING_TOKEN (STR_SHELLENV_GOTO_OUT_OF_RESOURCES), HiiEnvHandle);
    SEnvSetBatchAbort ();
    return EFI_OUT_OF_RESOURCES;
  }

  SEnvBatchSetGotoActive ();
  Status = SEnvBatchResetJumpStmt ();
  if (EFI_ERROR (Status)) {
    PrintToken (STRING_TOKEN (STR_SHELLENV_GOTO_CANNOT_EXECUTE_SCRIPT), HiiEnvHandle, Status);
    SEnvSetBatchAbort ();
    return Status;
  }

  return Status;
}