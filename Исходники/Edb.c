/**

  The default Exception Callback for the VM interpreter.
  In this function, we report status code, and print debug information
  about EBC_CONTEXT, then dead loop.

  @param ExceptionType    Exception type.
  @param SystemContext    EBC system context.

**/
VOID
EFIAPI
EdbExceptionHandler (
  IN     EFI_EXCEPTION_TYPE   ExceptionType,
  IN OUT EFI_SYSTEM_CONTEXT   SystemContext
  )
{
  CHAR16                  InputBuffer[EFI_DEBUG_INPUS_BUFFER_SIZE];
  CHAR16                  *CommandArg;
  EFI_DEBUGGER_COMMAND    DebuggerCommand;
  EFI_DEBUG_STATUS        DebugStatus;
  STATIC BOOLEAN          mInitialized;

  mInitialized = FALSE;

  DEBUG ((DEBUG_ERROR, "Hello EBC Debugger!\n"));

  if (!mInitialized) {
    //
    // Print version
    //
    EDBPrint (
      L"EBC Interpreter Version - %d.%d\n",
      (UINTN)VM_MAJOR_VERSION,
      (UINTN)VM_MINOR_VERSION
      );
    EDBPrint (
      L"EBC Debugger Version - %d.%d\n",
      (UINTN)EBC_DEBUGGER_MAJOR_VERSION,
      (UINTN)EBC_DEBUGGER_MINOR_VERSION
      );
  }
  //
  // Init Private Data
  //
  InitDebuggerPrivateData (&mDebuggerPrivate, ExceptionType, SystemContext, mInitialized);

  //
  // EDBPrint basic info
  //
  PrintExceptionReason (&mDebuggerPrivate, ExceptionType, SystemContext, mInitialized);

  EdbShowDisasm (&mDebuggerPrivate, SystemContext);
  // EFI_BREAKPOINT ();

  if (!mInitialized) {
    //
    // Interactive with user
    //
    EDBPrint (L"\nPlease enter command now, \'h\' for help.\n");
    EDBPrint (L"(Using <Command> -b <...> to enable page break.)\n");
  }
  mInitialized = TRUE;

  //
  // Dispatch each command
  //
  while (TRUE) {
    //
    // Get user input
    //
    Input (L"\n\r" EFI_DEBUG_PROMPT_STRING, InputBuffer, EFI_DEBUG_INPUS_BUFFER_SIZE);
    EDBPrint (L"\n");

    //
    // Get command
    //
    DebuggerCommand = MatchDebuggerCommand (InputBuffer, &CommandArg);
    if (DebuggerCommand == NULL) {
      EDBPrint (L"ERROR: Command not found!\n");
      continue;
    }

    //
    // Check PageBreak;
    //
    if (CommandArg != NULL) {
      if (StriCmp (CommandArg, L"-b") == 0) {
        CommandArg = StrGetNextTokenLine (L" ");
        mDebuggerPrivate.EnablePageBreak = TRUE;
      }
    }

    //
    // Dispatch command
    //
    DebugStatus = DebuggerCommand (CommandArg, &mDebuggerPrivate, ExceptionType, SystemContext);
    mDebuggerPrivate.EnablePageBreak = FALSE;

    //
    // Check command return status
    //
    if (DebugStatus == EFI_DEBUG_RETURN) {
      mInitialized = FALSE;
      break;
    } else if (DebugStatus == EFI_DEBUG_BREAK) {
      break;
    } else if (DebugStatus == EFI_DEBUG_CONTINUE) {
      continue;
    } else {
      ASSERT (FALSE);
    }
  }

  //
  // Deinit Private Data
  //
  DeinitDebuggerPrivateData (&mDebuggerPrivate, ExceptionType, SystemContext, mInitialized);

  DEBUG ((DEBUG_ERROR, "Goodbye EBC Debugger!\n"));

  return;
}