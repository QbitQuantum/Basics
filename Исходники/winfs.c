/* Move a file handle to recycle bin
 * The pathname must be a valid NT file name generated using filename_to_nt_pathname()
 */
static NTSTATUS move_to_recycle_bin(HANDLE handle, WCHAR *pathname)
{
	IO_STATUS_BLOCK status_block;
	NTSTATUS status;

	/* TODO: Handle the case when recycle bin does not exist (according to cygwin) */
	/* TODO: Handle when the file is inside recycle bin */
	WCHAR recyclepath[512];
	UNICODE_STRING recycle;
	RtlInitEmptyUnicodeString(&recycle, recyclepath, sizeof(recyclepath));
	/* Root directory, should look like "\??\C:\", 7 characters */
	UNICODE_STRING root;
	RtlInitCountedUnicodeString(&root, pathname, sizeof(WCHAR) * 7);
	RtlAppendUnicodeStringToString(&recycle, &root);
	RtlAppendUnicodeToString(&recycle, L"$Recycle.Bin\\");

	WCHAR renamepath[512];
	UNICODE_STRING rename;
	RtlInitEmptyUnicodeString(&rename, renamepath, sizeof(renamepath));
	RtlAppendUnicodeStringToString(&rename, &recycle);
	/* Append user sid */
	{
		WCHAR buf[256];
		UNICODE_STRING sid;
		RtlInitEmptyUnicodeString(&sid, buf, sizeof(buf));
		RtlConvertSidToUnicodeString(&sid, get_user_sid(), FALSE);
		RtlAppendUnicodeStringToString(&rename, &sid);
		RtlAppendUnicodeToString(&rename, L"\\");
	}
	/* Generate an unique file name by append file id and a hash of the pathname,
	 * To allow unlinking multiple hard links of the same file
	 */
	RtlAppendUnicodeToString(&rename, L".flinux");
	/* Append file id */
	{
		FILE_INTERNAL_INFORMATION info;
		status = NtQueryInformationFile(handle, &status_block, &info, sizeof(info), FileInternalInformation);
		if (!NT_SUCCESS(status))
		{
			log_error("NtQueryInformationFile(FileInternalInformation) failed, status: %x", status);
			return status;
		}
		RtlAppendInt64ToString(info.IndexNumber.QuadPart, 16, &rename);
		RtlAppendUnicodeToString(&rename, L"_");
	}
	/* Append file path hash */
	{
		UNICODE_STRING path;
		RtlInitUnicodeString(&path, pathname);
		ULONG hash;
		RtlHashUnicodeString(&path, FALSE, HASH_STRING_ALGORITHM_DEFAULT, &hash);
		RtlAppendIntegerToString(hash, 16, &rename);
	}
	/* Rename file */
	char buf[512];
	FILE_RENAME_INFORMATION *info = (FILE_RENAME_INFORMATION *)buf;
	info->ReplaceIfExists = FALSE;
	info->RootDirectory = NULL;
	info->FileNameLength = rename.Length;
	memcpy(info->FileName, rename.Buffer, rename.Length);
	status = NtSetInformationFile(handle, &status_block, info, sizeof(*info) + info->FileNameLength, FileRenameInformation);
	if (!NT_SUCCESS(status))
	{
		log_error("NtSetInformationFile(FileRenameInformation) failed, status: %x", status);
		return status;
	}
	return STATUS_SUCCESS;
}