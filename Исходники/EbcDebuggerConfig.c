/**
  Alter the EBC Debugger configuration.

  @param[in]  ImageHandle        The image handle.
  @param[in]  SystemTable        The system table.

  @retval EFI_SUCCESS            Operation completed successfully.
  @retval EFI_INVALID_PARAMETER  Usage error.
  @retval EFI_NOT_FOUND          A running debugger cannot be located.
**/
EFI_STATUS
EFIAPI
InitializeEbcDebuggerConfig (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  UINTN                               Argc;
  CHAR16                              **Argv;
  EFI_SHELL_PARAMETERS_PROTOCOL       *ShellParameters;
  EFI_DEBUGGER_CONFIGURATION_PROTOCOL *DebuggerConfiguration;
  EFI_STATUS                          Status;

  Status = gBS->HandleProtocol (
                  gImageHandle,
                  &gEfiShellParametersProtocolGuid,
                  (VOID**)&ShellParameters
                  );
  if (EFI_ERROR(Status)) {
    Print (L"Please use UEFI Shell to run this application.\n");
    return EFI_INVALID_PARAMETER;
  }

  Argc = ShellParameters->Argc;
  Argv = ShellParameters->Argv;

  if (Argc < 2) {
    PrintUsage ();
    return EFI_INVALID_PARAMETER;
  }

  if (Argc == 2) {
    if ((StrCmp (Argv[1], L"/?") == 0) ||
        (StrCmp (Argv[1], L"-?") == 0) ||
        (StrCmp (Argv[1], L"-h") == 0) ||
        (StrCmp (Argv[1], L"-H") == 0) ) {
      PrintUsage ();
      return EFI_SUCCESS;
    }
  }

  Status = gBS->LocateProtocol (
                 &gEfiDebuggerConfigurationProtocolGuid,
                 NULL,
                 (VOID**)&DebuggerConfiguration
                 );
  if (EFI_ERROR(Status)) {
    Print (L"Error: DebuggerConfiguration protocol not found.\n");
    return EFI_NOT_FOUND;
  }

  if (StriCmp (Argv[1], L"SHOWINFO") == 0) {
    EdbShowInfo (DebuggerConfiguration);
    return EFI_SUCCESS;
  }

  if (((Argc == 2) || (Argc == 3)) &&
      ((StriCmp (Argv[1], L"BOC")  == 0) ||
       (StriCmp (Argv[1], L"BOCX") == 0) ||
       (StriCmp (Argv[1], L"BOR")  == 0) ||
       (StriCmp (Argv[1], L"BOE")  == 0) ||
       (StriCmp (Argv[1], L"BOT")  == 0) ||
       (StriCmp (Argv[1], L"BOK")  == 0))) {
    if (Argc == 3) {
      EdbConfigBreak (DebuggerConfiguration, Argv[1], Argv[2]);
    } else {
      EdbConfigBreak (DebuggerConfiguration, Argv[1], NULL);
    }
    return EFI_SUCCESS;
  }

  Print (L"Error: Invalid Command.\n");
  return EFI_INVALID_PARAMETER;
}