__stdcall
OpenDeviceByName( UNICODE_STRING *FileName )
{
  LONG status;
  VOID* handle;
  OBJECT_ATTRIBUTES objectAttributes;
  IO_STATUS_BLOCK   isb;

 objectAttributes.Length = sizeof(OBJECT_ATTRIBUTES);
 objectAttributes.RootDirectory = NULL;
 objectAttributes.Attributes = OBJ_CASE_INSENSITIVE;
 objectAttributes.ObjectName = FileName;
 objectAttributes.SecurityDescriptor = NULL;
 objectAttributes.SecurityQualityOfService = NULL;

  /*status = NtOpenFile(
            &handle,
            SYNCHRONIZE | GENERIC_READ | GENERIC_WRITE,
            &objAttrib,
            &io_status,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT
            );*/

 status = NtCreateFile(
            &handle,
            SYNCHRONIZE | GENERIC_READ | GENERIC_WRITE,
            &objectAttributes,
            &isb,
            0,
            NULL,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            FILE_OPEN,
            FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT,
            NULL,
            0
            );

    if (!NT_SUCCESS(status))
    {
        return INVALID_HANDLE_VALUE;
    }

  return handle;
}