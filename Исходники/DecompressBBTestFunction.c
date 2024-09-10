//
//TDS 4.1.2
//
EFI_STATUS
Decompress_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                              Status;
  EFI_DECOMPRESS_PROTOCOL                 *Decompress;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  UINT32                                  UncompressedFileSize;
  UINT32                                  CompressedFileSize;
  UINT32                                  DestinationSize;
  UINT32                                  ScratchSize;
  UINTN                                   Index;
  UINTN                                   SubIndex;
  VOID                                    *CompressedFileBuffer;
  VOID                                    *UncompressedFileBuffer;
  UINT8                                   *DecompressBuffer;
  VOID                                    *ScratchBuffer;
  UINTN                                   BufferSize;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_INI_FILE_HANDLE                     FileHandle;
  EFI_FILE_HANDLE                         CompressedFHandle;
  EFI_FILE_HANDLE                         UncompressedFHandle;
  UINTN                                   MaxOrder;
  CHAR16                                  *CompressedFileName;
  CHAR16                                  *UncompressedFileName;

  //
  //get tested interface.
  //
  Decompress = (EFI_DECOMPRESS_PROTOCOL *)ClientInterface;

  //
  // Get the test Supported Library Interface
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib
             );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //open the ini file.
  //
  Status = OpenTestIniFile (ProfileLib, &FileHandle);

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DECOMPRESS_PROTOCOL.Decompress() -not found the profile.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  //
  //we initialize this variable because it was taken as UINT32 type, in fact it
  //is UINT64 value in ipf platform.
  //

  MaxOrder = 0;

  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_DECOMPRESS_BASIC_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DECOMPRESS_PROTOCOL.Decompress() -no item found for this test case.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index++) {

    CompressedFileBuffer   = NULL;
    UncompressedFileBuffer = NULL;
    DecompressBuffer       = NULL;
    ScratchBuffer          = NULL;

    //
    //get compressed FileName and file size.
    //
    Status = GetCompressedFileName (
               FileHandle,
               SECTION_NAME_DECOMPRESS_BASIC_TEST,
               Index,
               &CompressedFileName
               );

    if (EFI_ERROR(Status)) {
      Print (L"Get CompressedFileName Error\r\n");
      continue;
    }

    Status = GetUncompressedFileName (
               FileHandle,
               SECTION_NAME_DECOMPRESS_BASIC_TEST,
               Index,
               &UncompressedFileName
               );

    if (EFI_ERROR(Status)) {
      gtBS->FreePool (CompressedFileName);
      Print (L"Get UncompressedFileName Error\r\n");
      continue;
    }

    //
    //Open the Compressed file and get file size.
    //
    Status = OpenFileAndGetSize (
               CompressedFileName,
               &CompressedFHandle,
               &CompressedFileSize
               );

    if (EFI_ERROR(Status)) {
      Print (L"Can not open the File :%s\r\n", CompressedFileName);
      gtBS->FreePool (CompressedFileName);
      gtBS->FreePool (UncompressedFileName);
      continue;
    }
    gtBS->FreePool (CompressedFileName);

    //
    //Open the Uncompressed file and get file size.
    //
    Status = OpenFileAndGetSize (
               UncompressedFileName,
               &UncompressedFHandle,
               &UncompressedFileSize
               );

    if (EFI_ERROR(Status)) {
      Print (L"Can not open the File :%s\r\n", UncompressedFileName);
      CompressedFHandle->Close (CompressedFHandle);
      gtBS->FreePool (UncompressedFileName);
      continue;
    }
    gtBS->FreePool (UncompressedFileName);

    //
    //then read the Compressed File into memory.
    //
    CompressedFileBuffer = AllocatePool (CompressedFileSize);

    if (CompressedFileBuffer == NULL) {
      CompressedFHandle->Close (CompressedFHandle);
      UncompressedFHandle->Close (UncompressedFHandle);
      Print (L"Can not allocate %xh buffer.\r\n", CompressedFileSize);
      continue;
    }

    BufferSize = CompressedFileSize;

    Status = CompressedFHandle->Read (
                                  CompressedFHandle,
                                  &BufferSize,
                                  CompressedFileBuffer
                                  );

    CompressedFHandle->Close (CompressedFHandle);

    if (EFI_ERROR(Status)) {
      UncompressedFHandle->Close (UncompressedFHandle);
      Print (L"File Read Error Status %r\r\n", Status);
      gtBS->FreePool (CompressedFileBuffer);
      continue;
    }

    if (UncompressedFileSize == 0) {

      UncompressedFHandle->Close (UncompressedFHandle);

      Status = Decompress->GetInfo (
                             Decompress,
                             CompressedFileBuffer,
                             CompressedFileSize,
                             &DestinationSize,
                             &ScratchSize
                             );

      if (Status == EFI_SUCCESS) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_DECOMPRESS_PROTOCOL.GetInfo() - return Status Should be EFI_SUCCESS",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     __LINE__,
                     Status
                     );

      if (DestinationSize == 0) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_DECOMPRESS_PROTOCOL.GetInfo() - the Destination Size should be equal with the Uncompressed File Size",
                     L"%a:%d:destination Size - %d, Uncompressed File Size - %d",
                     __FILE__,
                     __LINE__,
                     (UINT32)DestinationSize,
                     (UINT32)UncompressedFileSize
                     );


      //
      // Fill the buffer with 0x00, and check whether the buffer is changed later
      //
      DecompressBuffer = AllocateZeroPool (128);

      if (DecompressBuffer == NULL) {
        gtBS->FreePool (CompressedFileBuffer);
        Print (L"Can not allocate %xh buffer.\r\n", 128);
        continue;
      }

      ScratchBuffer = AllocatePool (ScratchSize);

      if (ScratchBuffer == NULL) {
        gtBS->FreePool (CompressedFileBuffer);
        gtBS->FreePool (DecompressBuffer);
        Print (L"Can not allocate %xh buffer.\r\n", ScratchSize);
        continue;
      }

      Status = Decompress->Decompress (
                             Decompress,
                             CompressedFileBuffer,
                             CompressedFileSize,
                             DecompressBuffer,
                             DestinationSize,
                             ScratchBuffer,
                             ScratchSize
                             );

      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDecompressBBTestFunctionAssertionGuid007,
                     L"EFI_DECOMPRESS_PROTOCOL.Decompess() - decompress zero file, return Status should be EFI_SUCCESS",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     __LINE__,
                     Status
                     );

      AssertionType = EFI_TEST_ASSERTION_PASSED;

      //
      // Check whether the buffer is changed
      //
      for (SubIndex = 0; SubIndex < 128; SubIndex++) {
        if (DecompressBuffer[SubIndex] != (UINT8)0x00) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }
      SubIndex = (SubIndex < 127) ? SubIndex : 127;
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDecompressBBTestFunctionAssertionGuid008,
                     L"EFI_DECOMPRESS_PROTOCOL.Decompess() - Decompressed zero length file, the buffer should not be modified",
                     L"%a:%d:buffer - 0x%02x, expected - 0x00",
                     __FILE__,
                     __LINE__,
                     DecompressBuffer[SubIndex]
                     );

      //
      // Fill the buffer with 0xff, and check whether the buffer is changed later
      //
      for (SubIndex = 0; SubIndex < 128; SubIndex++) {
        DecompressBuffer[SubIndex] = (UINT8)0xff;
      }

      Status = Decompress->Decompress (
                             Decompress,
                             CompressedFileBuffer,
                             CompressedFileSize,
                             DecompressBuffer,
                             DestinationSize,
                             ScratchBuffer,
                             ScratchSize
                             );

      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDecompressBBTestFunctionAssertionGuid007,
                     L"EFI_DECOMPRESS_PROTOCOL.Decompess() - decompress zero file, return Status should be EFI_SUCCESS",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     __LINE__,
                     Status
                     );

      AssertionType = EFI_TEST_ASSERTION_PASSED;

      //
      // Check whether the buffer is changed
      //
      for (SubIndex = 0; SubIndex < 128; SubIndex++) {
        if (DecompressBuffer[SubIndex] != (UINT8)0xff) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }
      SubIndex = (SubIndex < 127) ? SubIndex : 127;
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDecompressBBTestFunctionAssertionGuid008,
                     L"EFI_DECOMPRESS_PROTOCOL.Decompess() - Decompressed zero length file, the buffer should not be modified",
                     L"%a:%d:buffer - 0x%02x, expected - 0xff",
                     __FILE__,
                     __LINE__,
                     DecompressBuffer[SubIndex]
                     );

      //
      //free the resources.
      //
      gtBS->FreePool (CompressedFileBuffer);
      gtBS->FreePool (DecompressBuffer);
      gtBS->FreePool (ScratchBuffer);
      continue;
    }

    //
    //the Uncompressed file is not null so read it into memory.
    //
    UncompressedFileBuffer = AllocatePool (UncompressedFileSize);

    if (UncompressedFileBuffer == NULL) {
      UncompressedFHandle->Close (UncompressedFHandle);
      gtBS->FreePool (CompressedFileBuffer);
      Print (L"Can not alloate %xh buffer.\r\n", UncompressedFileSize);
      continue;
    }

    BufferSize = UncompressedFileSize;

    Status = UncompressedFHandle->Read (
                                    UncompressedFHandle,
                                    &BufferSize,
                                    UncompressedFileBuffer
                                    );

    UncompressedFHandle->Close (UncompressedFHandle);

    if (EFI_ERROR(Status)) {
      gtBS->FreePool (CompressedFileBuffer);
      gtBS->FreePool (UncompressedFileBuffer);
      Print (L"File Read Error Status %r\r\n", Status);
      continue;
    }

    //
    //now verify the check points.
    //

    Status = Decompress->GetInfo (
                           Decompress,
                           CompressedFileBuffer,
                           CompressedFileSize,
                           &DestinationSize,
                           &ScratchSize
                           );

    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_DECOMPRESS_PROTOCOL.GetInfo() - return Status should be EFI_SUCCESS",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );

    if (DestinationSize == UncompressedFileSize) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_DECOMPRESS_PROTOCOL.GetInfo() - the Destination Size should be equal with the Uncompressed File Size",
                   L"%a:%d:destination Size - %d, Uncompressed File Size - %d",
                   __FILE__,
                   __LINE__,
                   (UINT32)DestinationSize,
                   (UINT32)UncompressedFileSize
                   );

    //
    //allocate Decompess buffer and Decompress the compessed data.
    //
    DecompressBuffer = AllocatePool (DestinationSize);
    if (DecompressBuffer == NULL) {
      gtBS->FreePool (CompressedFileBuffer);
      gtBS->FreePool (UncompressedFileBuffer);
      Print (L"Can not allocate %xh buffer.\r\n", DestinationSize);
      continue;
    }

    ScratchBuffer = AllocatePool (ScratchSize);
    if (ScratchBuffer == NULL) {
      gtBS->FreePool (CompressedFileBuffer);
      gtBS->FreePool (UncompressedFileBuffer);
      gtBS->FreePool (DecompressBuffer);
      Print (L"Can not allocate %xh buffer.\r\n", ScratchSize);
      continue;
    }

    Status = Decompress->Decompress (
                           Decompress,
                           CompressedFileBuffer,
                           CompressedFileSize,
                           DecompressBuffer,
                           DestinationSize,
                           ScratchBuffer,
                           ScratchSize
                           );

    if (!EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDecompressBBTestFunctionAssertionGuid009,
                   L"EFI_DECOMPRESS_PROTOCOL.Decompess() - decompress unzero file, return Status should be EFI_SUCCESS",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    if (CompareMem (DecompressBuffer,
                    UncompressedFileBuffer, UncompressedFileSize) == 0) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDecompressBBTestFunctionAssertionGuid010,
                   L"EFI_DECOMPRESS_PROTOCOL.Decompess() - Decompressed data should be equal with Uncompressed data",
                   L"%a:%d",
                   __FILE__,
                   __LINE__
                   );

    //
    //free the resources
    //
    gtBS->FreePool (CompressedFileBuffer);
    gtBS->FreePool (UncompressedFileBuffer);
    gtBS->FreePool (DecompressBuffer);
    gtBS->FreePool (ScratchBuffer);
  }

  CloseTestIniFile (ProfileLib, FileHandle);

  //
  //done successfully
  //
  return EFI_SUCCESS;
}