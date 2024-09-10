BOOLEAN
IsKeyOptionVariable (
  CHAR16        *Name,
  EFI_GUID      *Guid,
  UINT16        *OptionNumber
  )
{
  UINTN         Index;
  
  if (!CompareGuid (Guid, &gEfiGlobalVariableGuid) ||
      (StrSize (Name) != sizeof (L"Key####")) ||
      (StrnCmp (Name, L"Key", 3) != 0)
     ) {
    return FALSE;
  }

  *OptionNumber = 0;
  for (Index = 3; Index < 7; Index++) {
    if ((Name[Index] >= L'0') && (Name[Index] <= L'9')) {
      *OptionNumber = *OptionNumber * 10 + Name[Index] - L'0';
    } else if ((Name[Index] >= L'A') && (Name[Index] <= L'F')) {
      *OptionNumber = *OptionNumber * 10 + Name[Index] - L'A';
    } else {
      return FALSE;
    }
  }

  return TRUE;
}