/*++
* @name SmpDeleteFile
*
* The SmpDeleteFile function deletes a specify file.
*
* @param    lpFileName
*           the name of a file which should be deleted
*
* @return   STATUS_SUCCESS in case of success, STATUS_UNSUCCESSFUL
*           othwerwise.
*
* @remarks
* This function is called by SmpMoveFilesQueryRoutine().
*
*
*--*/
NTSTATUS
SmpDeleteFile( IN LPCWSTR lpFileName )
{
	FILE_DISPOSITION_INFORMATION FileDispInfo;
	OBJECT_ATTRIBUTES ObjectAttributes;
	IO_STATUS_BLOCK IoStatusBlock;
	UNICODE_STRING FileNameU;
	HANDLE FileHandle;
	NTSTATUS Status;

	DPRINT("SmpDeleteFile ( %S )\n", lpFileName);

	if( !lpFileName )
		return (STATUS_INVALID_PARAMETER);

	RtlInitUnicodeString(&FileNameU, lpFileName);

	InitializeObjectAttributes(&ObjectAttributes,
		&FileNameU,
		OBJ_CASE_INSENSITIVE,
		NULL,
		NULL);

	Status = NtCreateFile (&FileHandle,
		DELETE,
		&ObjectAttributes,
		&IoStatusBlock,
		NULL,
		FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		FILE_OPEN,
		FILE_SYNCHRONOUS_IO_NONALERT,
		NULL,
		0);

	if( !NT_SUCCESS(Status) ) {
		DPRINT("NtCreateFile() failed (Status %lx)\n", Status);
		return (Status);
	}

	FileDispInfo.DeleteFile = TRUE;

	Status = NtSetInformationFile(
		FileHandle,
		&IoStatusBlock,
		&FileDispInfo,
		sizeof(FILE_DISPOSITION_INFORMATION),
		FileDispositionInformation );

	NtClose(FileHandle);

	return (Status);
}