NTSTATUS WINAPI SafeNtOpenFile(
  PHANDLE             FileHandle,
  ACCESS_MASK         DesiredAccess,
  POBJECT_ATTRIBUTES  ObjectAttributes,
  PIO_STATUS_BLOCK    IoStatusBlock,
  ULONG               ShareAccess,
  ULONG               OpenOptions 
)
{
	NTSTATUS rc;

	if (CheckOldFunction(&OldNtOpenFile))
		rc=OldNtOpenFile(FileHandle,DesiredAccess,ObjectAttributes,IoStatusBlock,ShareAccess,OpenOptions);
	else
		rc=NtOpenFile(FileHandle,DesiredAccess,ObjectAttributes,IoStatusBlock,ShareAccess,OpenOptions);

	return rc;
}