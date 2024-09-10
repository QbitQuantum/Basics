/**
  Function to parse the Data by the type of Data, and save in the Buffer.

  @param[in]      Data                A pointer to a buffer to be parsed.
  @param[out]     Buffer              A pointer to a buffer to hold the return data.
  @param[in,out]  BufferSize          On input, indicates the size of Buffer in bytes.
                                      On output,indicates the size of data return in Buffer.
                                      Or the size in bytes of the buffer needed to obtain.

  @retval   EFI_INVALID_PARAMETER     The Buffer or BufferSize is NULL.
  @retval   EFI_BUFFER_TOO_SMALL      The Buffer is too small to hold the data.
  @retval   EFI_OUT_OF_RESOURCES      A memory allcation failed.
  @retval   EFI_SUCCESS               The Data parsed successful and save in the Buffer.
**/
EFI_STATUS
ParseParameterData (
  IN CONST CHAR16   *Data,
  OUT VOID          *Buffer,
  IN OUT UINTN      *BufferSize
  )
{
  UINT64                    HexNumber;
  UINTN                     HexNumberLen;
  UINTN                     Size;
  CHAR8                     *AsciiBuffer;
  DATA_TYPE                 DataType;
  EFI_DEVICE_PATH_PROTOCOL  *DevPath;
  EFI_STATUS                Status;

  HexNumber                 = 0;
  HexNumberLen              = 0;
  Size                      = 0;
  AsciiBuffer               = NULL;
  DevPath                   = NULL;
  Status                    = EFI_SUCCESS;

  if (Data == NULL || BufferSize == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  DataType = TestDataType (Data);
  if (DataType == DataTypeHexNumber) {
    //
    // hex number
    //
    StrHexToUint64S (Data + 2, NULL, &HexNumber);
    HexNumberLen = StrLen (Data + 2);
    if (HexNumberLen >= 1 && HexNumberLen <= 2) {
      Size = 1;
    } else if (HexNumberLen >= 3 && HexNumberLen <= 4) {
      Size = 2;
    } else if (HexNumberLen >= 5 && HexNumberLen <= 8) {
      Size = 4;
    } else if (HexNumberLen >= 9 && HexNumberLen <= 16) {
      Size = 8;
    }
    if (Buffer != NULL && *BufferSize >= Size) {
      CopyMem(Buffer, (VOID *)&HexNumber, Size);
    } else {
      Status = EFI_BUFFER_TOO_SMALL;
    }
    *BufferSize = Size;
  } else if (DataType == DataTypeHexArray) {
    //
    // hex array
    //
    if (*Data == L'H') {
      Data = Data + 1;
    }

    Size = StrLen (Data) / 2;
    if (Buffer != NULL && *BufferSize >= Size) {
      StrHexToBytes(Data, StrLen  (Data), (UINT8 *)Buffer, Size);
    } else {
      Status = EFI_BUFFER_TOO_SMALL;
    }
    *BufferSize = Size;
  } else if (DataType == DataTypeAscii) {
    //
    // ascii text
    //
    if (*Data == L'S') {
      Data = Data + 1;
    }
    AsciiBuffer = AllocateZeroPool (StrSize (Data) / 2);
    if (AsciiBuffer == NULL) {
      Status = EFI_OUT_OF_RESOURCES;
    } else {
      AsciiSPrint (AsciiBuffer, StrSize (Data) / 2, "%s", (CHAR8 *)Data);

      Size = StrSize (Data) / 2 - 1;
      if (Buffer != NULL && *BufferSize >= Size) {
        CopyMem (Buffer, AsciiBuffer, Size);
      } else {
        Status = EFI_BUFFER_TOO_SMALL;
      }
      *BufferSize = Size;
    }
    SHELL_FREE_NON_NULL (AsciiBuffer);
  } else if (DataType == DataTypeUnicode) {
    //
    // unicode text
    //
    if (*Data == L'L') {
      Data = Data + 1;
    }
    Size = StrSize (Data) - sizeof (CHAR16);
    if (Buffer != NULL && *BufferSize >= Size) {
      CopyMem (Buffer, Data, Size);
    } else {
      Status = EFI_BUFFER_TOO_SMALL;
    }
    *BufferSize = Size;
  } else if (DataType == DataTypeDevicePath) {
    if (*Data == L'P') {
      Data = Data + 1;
    } else if (StrnCmp (Data, L"--", 2) == 0) {
      Data = Data + 2;
    }
    DevPath = ConvertTextToDevicePath (Data);
    if (DevPath == NULL) {
      ShellPrintHiiEx (-1, -1, NULL, STRING_TOKEN (STR_SETVAR_ERROR_DPFT), gShellDebug1HiiHandle, L"setvar");
      Status = EFI_INVALID_PARAMETER;
    } else {
      Size = GetDevicePathSize (DevPath);
      if (Buffer != NULL && *BufferSize >= Size) {
        CopyMem (Buffer, DevPath, Size);
      } else {
        Status = EFI_BUFFER_TOO_SMALL;
      }
      *BufferSize = Size;
    }
    SHELL_FREE_NON_NULL (DevPath);
  } else {
    Status = EFI_INVALID_PARAMETER;
  }

  return Status;
}