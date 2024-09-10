INTN
EFIAPI
main (
  IN  INTN  Argc,
  IN  CHAR8 **Argv,
  IN  CHAR8 **Envp
  )
/*++

Routine Description:
  Main entry point to SEC for WinNt. This is a Windows program

Arguments:
  Argc - Number of command line arguments
  Argv - Array of command line argument strings
  Envp - Array of environmemt variable strings

Returns:
  0 - Normal exit
  1 - Abnormal exit

--*/
{
  EFI_STATUS            Status;
  HANDLE                Token;
  TOKEN_PRIVILEGES      TokenPrivileges;
  EFI_PHYSICAL_ADDRESS  InitialStackMemory;
  UINT64                InitialStackMemorySize;
  UINTN                 Index;
  UINTN                 Index1;
  UINTN                 Index2;
  CHAR16                *FileName;
  CHAR16                *FileNamePtr;
  BOOLEAN               Done;
  VOID                  *PeiCoreFile;
  CHAR16                *MemorySizeStr;
  CHAR16                *FirmwareVolumesStr;
  UINTN                 *StackPointer;

  //
  // Enable the privilege so that RTC driver can successfully run SetTime()
  //
  OpenProcessToken (GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &Token);
  if (LookupPrivilegeValue(NULL, SE_TIME_ZONE_NAME, &TokenPrivileges.Privileges[0].Luid)) {
    TokenPrivileges.PrivilegeCount = 1;
    TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges(Token, FALSE, &TokenPrivileges, 0, (PTOKEN_PRIVILEGES) NULL, 0);
  }

  MemorySizeStr      = (CHAR16 *) PcdGetPtr (PcdWinNtMemorySizeForSecMain);
  FirmwareVolumesStr = (CHAR16 *) PcdGetPtr (PcdWinNtFirmwareVolume);

  SecPrint ("\nEDK II SEC Main NT Emulation Environment from www.TianoCore.org\n");

  //
  // Make some Windows calls to Set the process to the highest priority in the
  //  idle class. We need this to have good performance.
  //
  SetPriorityClass (GetCurrentProcess (), IDLE_PRIORITY_CLASS);
  SetThreadPriority (GetCurrentThread (), THREAD_PRIORITY_HIGHEST);

  //
  // Allocate space for gSystemMemory Array
  //
  gSystemMemoryCount  = CountSeperatorsInString (MemorySizeStr, '!') + 1;
  gSystemMemory       = calloc (gSystemMemoryCount, sizeof (NT_SYSTEM_MEMORY));
  if (gSystemMemory == NULL) {
    SecPrint ("ERROR : Can not allocate memory for %S.  Exiting.\n", MemorySizeStr);
    exit (1);
  }
  //
  // Allocate space for gSystemMemory Array
  //
  gFdInfoCount  = CountSeperatorsInString (FirmwareVolumesStr, '!') + 1;
  gFdInfo       = calloc (gFdInfoCount, sizeof (NT_FD_INFO));
  if (gFdInfo == NULL) {
    SecPrint ("ERROR : Can not allocate memory for %S.  Exiting.\n", FirmwareVolumesStr);
    exit (1);
  }
  //
  // Setup Boot Mode. If BootModeStr == "" then BootMode = 0 (BOOT_WITH_FULL_CONFIGURATION)
  //
  SecPrint ("  BootMode 0x%02x\n", PcdGet32 (PcdWinNtBootMode));

  //
  //  Allocate 128K memory to emulate temp memory for PEI.
  //  on a real platform this would be SRAM, or using the cache as RAM.
  //  Set InitialStackMemory to zero so WinNtOpenFile will allocate a new mapping
  //
  InitialStackMemorySize  = STACK_SIZE;
  InitialStackMemory = (EFI_PHYSICAL_ADDRESS) (UINTN) VirtualAlloc (NULL, (SIZE_T) (InitialStackMemorySize), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
  if (InitialStackMemory == 0) {
    SecPrint ("ERROR : Can not allocate enough space for SecStack\n");
    exit (1);
  }

  for (StackPointer = (UINTN*) (UINTN) InitialStackMemory;
       StackPointer < (UINTN*) ((UINTN)InitialStackMemory + (SIZE_T) InitialStackMemorySize);
       StackPointer ++) {
    *StackPointer = 0x5AA55AA5;
  }
  
  SecPrint ("  SEC passing in %d bytes of temp RAM to PEI\n", InitialStackMemorySize);

  //
  // Open All the firmware volumes and remember the info in the gFdInfo global
  //
  FileNamePtr = (CHAR16 *)malloc (StrLen ((CHAR16 *)FirmwareVolumesStr) * sizeof(CHAR16));
  if (FileNamePtr == NULL) {
    SecPrint ("ERROR : Can not allocate memory for firmware volume string\n");
    exit (1);
  }

  StrCpy (FileNamePtr, (CHAR16*)FirmwareVolumesStr);

  for (Done = FALSE, Index = 0, PeiCoreFile = NULL; !Done; Index++) {
    FileName = FileNamePtr;
    for (Index1 = 0; (FileNamePtr[Index1] != '!') && (FileNamePtr[Index1] != 0); Index1++)
      ;
    if (FileNamePtr[Index1] == 0) {
      Done = TRUE;
    } else {
      FileNamePtr[Index1]  = '\0';
      FileNamePtr = FileNamePtr + Index1 + 1;
    }

    //
    // Open the FD and remmeber where it got mapped into our processes address space
    //
    Status = WinNtOpenFile (
              FileName,
              0,
              OPEN_EXISTING,
              &gFdInfo[Index].Address,
              &gFdInfo[Index].Size
              );
    if (EFI_ERROR (Status)) {
      SecPrint ("ERROR : Can not open Firmware Device File %S (0x%X).  Exiting.\n", FileName, Status);
      exit (1);
    }

    SecPrint ("  FD loaded from");
    //
    // printf can't print filenames directly as the \ gets interperted as an
    //  escape character.
    //
    for (Index2 = 0; FileName[Index2] != '\0'; Index2++) {
      SecPrint ("%c", FileName[Index2]);
    }

    if (PeiCoreFile == NULL) {
      //
      // Assume the beginning of the FD is an FV and look for the PEI Core.
      // Load the first one we find.
      //
      Status = SecFfsFindPeiCore ((EFI_FIRMWARE_VOLUME_HEADER *) (UINTN) gFdInfo[Index].Address, &PeiCoreFile);
      if (!EFI_ERROR (Status)) {
        SecPrint (" contains SEC Core");
      }
    }

    SecPrint ("\n");
  }
  //
  // Calculate memory regions and store the information in the gSystemMemory
  //  global for later use. The autosizing code will use this data to
  //  map this memory into the SEC process memory space.
  //
  for (Index = 0, Done = FALSE; !Done; Index++) {
    //
    // Save the size of the memory and make a Unicode filename SystemMemory00, ...
    //
    gSystemMemory[Index].Size = _wtoi (MemorySizeStr) * 0x100000;

    //
    // Find the next region
    //
    for (Index1 = 0; MemorySizeStr[Index1] != '!' && MemorySizeStr[Index1] != 0; Index1++)
      ;
    if (MemorySizeStr[Index1] == 0) {
      Done = TRUE;
    }

    MemorySizeStr = MemorySizeStr + Index1 + 1;
  }

  SecPrint ("\n");

  //
  // Hand off to PEI Core
  //
  SecLoadFromCore ((UINTN) InitialStackMemory, (UINTN) InitialStackMemorySize, (UINTN) gFdInfo[0].Address, PeiCoreFile);

  //
  // If we get here, then the PEI Core returned. This is an error as PEI should
  //  always hand off to DXE.
  //
  SecPrint ("ERROR : PEI Core returned\n");
  exit (1);
}