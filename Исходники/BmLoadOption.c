/**
  Check whether the VariableName is a valid load option variable name
  and return the load option type and option number.

  @param VariableName The name of the load option variable.
  @param OptionType   Return the load option type.
  @param OptionNumber Return the load option number.

  @retval TRUE  The variable name is valid; The load option type and
                load option number is returned.
  @retval FALSE The variable name is NOT valid.
**/
BOOLEAN
BmIsValidLoadOptionVariableName (
  IN CHAR16                             *VariableName,
  OUT EFI_BOOT_MANAGER_LOAD_OPTION_TYPE *OptionType,
  OUT UINT16                            *OptionNumber
  )
{
  UINTN                             VariableNameLen;
  UINTN                             Index;
  UINTN                             Uint;

  VariableNameLen = StrLen (VariableName);

  if (VariableNameLen <= 4) {
    return FALSE;
  }

  for (Index = 0; Index < sizeof (mBmLoadOptionName) / sizeof (mBmLoadOptionName[0]); Index++) {
    if ((VariableNameLen - 4 == StrLen (mBmLoadOptionName[Index])) &&
        (StrnCmp (VariableName, mBmLoadOptionName[Index], VariableNameLen - 4) == 0)
        ) {
      break;
    }
  }

  if (Index == sizeof (mBmLoadOptionName) / sizeof (mBmLoadOptionName[0])) {
    return FALSE;
  }

  *OptionType = (EFI_BOOT_MANAGER_LOAD_OPTION_TYPE) Index;
  *OptionNumber = 0;
  for (Index = VariableNameLen - 4; Index < VariableNameLen; Index++) {
    Uint = BmCharToUint (VariableName[Index]);
    if (Uint == -1) {
      break;
    } else {
      *OptionNumber = (UINT16) Uint + *OptionNumber * 0x10;
    }
  }

  return (BOOLEAN) (Index == VariableNameLen);
}