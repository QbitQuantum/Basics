EFI_STATUS
CheckBootFromNetworkProtocols (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN EFI_INI_FILE_HANDLE                  IniFile
  )
{
  EFI_STATUS          Status;
  UINT32              MaxLength;
  CHAR16              String[10];
  BOOLEAN             ValueA;
  BOOLEAN             ValueB;
  BOOLEAN             ValueC;
  VOID                *Interface;
  EFI_TEST_ASSERTION  AssertionType;

  //
  // Check the SIMPLE_NETWORK protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiSimpleNetworkProtocolGuid,
                   NULL,
                   &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueA = TRUE;
  } else {
    ValueA = FALSE;
  }

  //
  // Check the PXE_BASE_CODE protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiPxeBaseCodeProtocolGuid,
                   NULL,
                   &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueB = TRUE;
  } else {
    ValueB = FALSE;
  }

  //
  // Check the BIS protocol
  //
  Status = gtBS->LocateProtocol (
                   &gEfiBisProtocolGuid,
                   NULL,
                   &Interface
                   );
  if (!EFI_ERROR (Status)) {
    ValueC = TRUE;
  } else {
    ValueC = FALSE;
  }

  //
  // BIS protocol indicates the ability to validate a boot image received
  // through a network device. UEFI forum may think it is not one of platform
  // specific elements. So here we skip the check to this protocol.
  //

  //
  // Need *two* or warning
  //
  AssertionType = NeedTwoOrWarning (ValueA, ValueB);

  //
  // For platform-specific elements, throw out a warning in default
  //
  if (AssertionType == EFI_TEST_ASSERTION_FAILED) {
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }

  //
  // If warning, check with INI file to decide they must exist or not
  //
  if ((AssertionType == EFI_TEST_ASSERTION_WARNING) &&
      (IniFile       != NULL_HANDLE               )) {
    MaxLength = 10;

    Status = IniFile->GetString (
                        IniFile,
                        SECTION_NAME_PLATFORM_SPECIFIC,
                        L"BootFromNetworkDevices",
                        String,
                        &MaxLength
                        );
    if (!EFI_ERROR (Status) && (StriCmp (String, L"yes") == 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
  }

  //
  // Record test result
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEfiCompliantBbTestPlatformAssertionGuid005,
                 L"EFI Compliant - Boot from network protocols must be implemented",
                 L"%a:%d:SNP - %s, PXE BC - %s, BIS (not required) - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 ValueA ? L"Yes" : L"No",
                 ValueB ? L"Yes" : L"No",
                 ValueC ? L"Yes" : L"No"
                 );

  //
  // Done
  //
  return EFI_SUCCESS;
}