//
// TDS 4.1.4
//
EFI_STATUS
BBTestStrUprFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_UNICODE_COLLATION_PROTOCOL       *UnicodeCollation;

  UINTN                                Index;

  EFI_TEST_ASSERTION                   AssertionType;

  //
  // Test Data
  //
  CHAR16                               *TestData[] ={
                                             L"\x21\x22\x31\x32\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5Ax61\x62\x7D\x7E",
                                             L"\x30\x50[abcdzyxw!)(@#*]\x40\x20\x30\x50\ab\x40\x20",
                                             L"\x30\x50[A-D]\x40\x20\x30\x50f\x40\x20",
                                             L""
                                        };

  CHAR16                               TestDataSav[MAX_SIZE_OF_STRING + 1];


  //
  // Verify whether it is one of IHV interfaces
  //
  if (! IsIhvInterface (ClientInterface, SupportHandle)) {
    return EFI_UNSUPPORTED;
  }

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  UnicodeCollation = (EFI_UNICODE_COLLATION_PROTOCOL *)ClientInterface;
  for (Index = 0; Index < sizeof (TestData) / sizeof (CHAR16*); Index++) {
    //
    // Backup current test data
    //
    CopyUnicodeString (TestDataSav, TestData[Index]);

    //
    // For each test data, test the StrUpr functionality.
    //
    UnicodeCollation->StrUpr (UnicodeCollation, TestData[Index]);

    if (CheckStrUpr (TestDataSav, TestData[Index])) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUnicodeCollationFunctionTestAssertionGuid005,
                   L"EFI_UNICODE_COLLATION_PROTOCOL.StrUpr - Verification of StrUpr interface",
                   L"%a:%d: Original=%s-- ToUpper=%s",
                   __FILE__,
                   __LINE__,
                   TestDataSav,
                   TestData[Index]
                   );

    CopyUnicodeString (TestDataSav, TestData[Index]);
    UnicodeCollation->StrLwr (UnicodeCollation, TestData[Index]);
    UnicodeCollation->StrUpr (UnicodeCollation, TestData[Index]);

    if (CheckStrEql (TestDataSav, TestData[Index])) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUnicodeCollationFunctionTestAssertionGuid006,
                   L"EFI_UNICODE_COLLATION_PROTOCOL.StrUpr - Verification of StrUpr interface",
                   L"%a:%d: Original=%s -- ToUpper=%s",
                   __FILE__,
                   __LINE__,
                   TestDataSav,
                   TestData[Index]
                   );
  };

  return EFI_SUCCESS;
}