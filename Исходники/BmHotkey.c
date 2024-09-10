/**

  Check whether the input variable is an key option variable.

  @param   Name               Input variable name.
  @param   Guid               Input variable guid.
  @param   OptionNumber       The option number of this key option variable.

  @retval  TRUE               Input variable is a key option variable.
  @retval  FALSE              Input variable is not a key option variable.
**/
BOOLEAN
BmIsKeyOptionVariable (
  CHAR16        *Name,
  EFI_GUID      *Guid,
  UINT16        *OptionNumber
  )
{
  UINTN         Index;
  UINTN         Uint;

  if (!CompareGuid (Guid, &gEfiGlobalVariableGuid) ||
      (StrSize (Name) != sizeof (L"Key####")) ||
      (StrnCmp (Name, L"Key", 3) != 0)
     ) {
    return FALSE;
  }

  *OptionNumber = 0;
  for (Index = 3; Index < 7; Index++) {
    Uint = BmCharToUint (Name[Index]);
    if (Uint == -1) {
      return FALSE;
    } else {
      *OptionNumber = (UINT16) Uint + *OptionNumber * 0x10;
    }
  }

  return TRUE;
}