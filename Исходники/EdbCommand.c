/**

  Find the command according to name.

  @param  CommandName   - Command Name
  @param  CommandArg    - Command Argument

  @return Not NULL        - The DebuggerCommand is found successfully
  @return NULL            - not found

**/
EFI_DEBUGGER_COMMAND
MatchDebuggerCommand (
  IN CHAR16    *CommandName,
  IN CHAR16    **CommandArg
  )
{
  UINTN  Index;
  CHAR16 *Temp;

  //
  // Get Command Name
  //
  Temp = StrGetNewTokenLine (CommandName, L" ");
  CommandName = Temp;
  //
  // Get Command Argument
  //
  Temp = StrGetNextTokenLine (L" ");
  *CommandArg = Temp;

  if (CommandName == NULL) {
    return NULL;
  }

  //
  // Go through each command, check the CommandName
  //
  for (Index = 0; mDebuggerCommandSet[Index].CommandName != NULL; Index++) {
    if (StriCmp (CommandName, mDebuggerCommandSet[Index].CommandName) == 0) {
      //
      // Found
      //
      return mDebuggerCommandSet[Index].CommandFunc;
    }
  }

  //
  // Not found
  //
  return NULL;
}