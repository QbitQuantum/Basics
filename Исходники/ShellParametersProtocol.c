/**
  Function to populate Argc and Argv.

  This function parses the CommandLine and divides it into standard C style Argc/Argv
  parameters for inclusion in EFI_SHELL_PARAMETERS_PROTOCOL.  this supports space
  delimited and quote surrounded parameter definition.

  @param[in] CommandLine         String of command line to parse
  @param[in, out] Argv           pointer to array of strings; one for each parameter
  @param[in, out] Argc           pointer to number of strings in Argv array

  @return EFI_SUCCESS           the operation was sucessful
  @return EFI_OUT_OF_RESOURCES  a memory allocation failed.
**/
EFI_STATUS
EFIAPI
ParseCommandLineToArgs(
  IN CONST CHAR16 *CommandLine,
  IN OUT CHAR16 ***Argv,
  IN OUT UINTN *Argc
  )
{
  UINTN       Count;
  CHAR16      *TempParameter;
  CHAR16      *Walker;
  CHAR16      *NewParam;
  UINTN       Size;

  ASSERT(Argc != NULL);
  ASSERT(Argv != NULL);

  if (CommandLine == NULL || StrLen(CommandLine)==0) {
    (*Argc) = 0;
    (*Argv) = NULL;
    return (EFI_SUCCESS);
  }

  Size = StrSize(CommandLine);
  TempParameter = AllocateZeroPool(Size);
  if (TempParameter == NULL) {
    return (EFI_OUT_OF_RESOURCES);
  }

  for ( Count = 0
      , Walker = (CHAR16*)CommandLine
      ; Walker != NULL && *Walker != CHAR_NULL
      ; GetNextParameter(&Walker, &TempParameter)
      , Count++
     );

/*  Count = 0;
  Walker = (CHAR16*)CommandLine;
  while(Walker != NULL) {
    GetNextParameter(&Walker, &TempParameter);
    Count++;
  }
*/
  //
  // lets allocate the pointer array
  //
  (*Argv) = AllocateZeroPool((Count)*sizeof(CHAR16*));
  if (*Argv == NULL) {
    SHELL_FREE_NON_NULL(TempParameter);
    return (EFI_OUT_OF_RESOURCES);
  }

  *Argc = 0;
  Walker = (CHAR16*)CommandLine;
  while(Walker != NULL && *Walker != CHAR_NULL) {
    SetMem16(TempParameter, Size, CHAR_NULL);
    GetNextParameter(&Walker, &TempParameter);
    NewParam = AllocateZeroPool(StrSize(TempParameter));
    ASSERT(NewParam != NULL);
    StrCpy(NewParam, TempParameter);
    ((CHAR16**)(*Argv))[(*Argc)] = NewParam;
    (*Argc)++;
  }
  ASSERT(Count >= (*Argc));
  SHELL_FREE_NON_NULL(TempParameter);
  return (EFI_SUCCESS);
}