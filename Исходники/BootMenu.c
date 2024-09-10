/**
  Worker function that asks for a boot option to be selected and returns a
  pointer to the structure describing the selected boot option.

  @param[in]  BootOptionsList  List of the boot options

  @retval     EFI_SUCCESS      Selection succeeded
  @retval     !EFI_SUCCESS     Input error or input cancelled

**/
STATIC
EFI_STATUS
SelectBootOption (
  IN  LIST_ENTRY*               BootOptionsList,
  IN  CONST CHAR16*             InputStatement,
  OUT BDS_LOAD_OPTION_ENTRY**   BdsLoadOptionEntry
  )
{
  EFI_STATUS                    Status;
  UINTN                         BootOptionCount;
  UINT16                       *BootOrder;
  LIST_ENTRY*                   Entry;
  UINTN                         BootOptionSelected;
  UINTN                         Index;

  // Get the number of boot options
  Status = GetGlobalEnvironmentVariable (
            L"BootOrder", NULL, &BootOptionCount, (VOID**)&BootOrder
            );
  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }
  FreePool (BootOrder);
  BootOptionCount /= sizeof (UINT16);

  // Check if a valid boot option(s) is found
  if (BootOptionCount == 0) {
    if (StrCmp (InputStatement, DELETE_BOOT_ENTRY) == 0) {
      Print (L"Nothing to remove!\n");
    } else if (StrCmp (InputStatement, UPDATE_BOOT_ENTRY) == 0) {
      Print (L"Nothing to update!\n");
    } else if (StrCmp (InputStatement, MOVE_BOOT_ENTRY) == 0) {
      Print (L"Nothing to move!\n");
    } else {
      Print (L"No supported Boot Entry.\n");
    }
    return EFI_NOT_FOUND;
  }

  // Get the index of the boot device to delete
  BootOptionSelected = 0;
  while (BootOptionSelected == 0) {
    Print (InputStatement);
    Status = GetHIInputInteger (&BootOptionSelected);
    if (EFI_ERROR (Status)) {
      Print (L"\n");
      goto ErrorExit;
    } else if ((BootOptionSelected == 0) || (BootOptionSelected > BootOptionCount)) {
      Print (L"Invalid input (max %d)\n", BootOptionCount);
      BootOptionSelected = 0;
    }
  }

  // Get the structure of the Boot device to delete
  Index = 1;
  for (Entry = GetFirstNode (BootOptionsList);
       !IsNull (BootOptionsList, Entry);
       Entry = GetNextNode (BootOptionsList,Entry)
       )
  {
    if (Index == BootOptionSelected) {
      *BdsLoadOptionEntry = LOAD_OPTION_ENTRY_FROM_LINK (Entry);
      break;
    }
    Index++;
  }

ErrorExit:
  return Status;
}