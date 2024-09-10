BOOL
BackupWriteAlternateData(HANDLE hFile, BACKUPCONTEXT *pbuc, BACKUPIOFRAME *pbif)
{
    if (pbuc->fStreamStart) {
	NTSTATUS Status;
	UNICODE_STRING strName;
	OBJECT_ATTRIBUTES oa;
	IO_STATUS_BLOCK iosb;

	strName.Length = (USHORT) pbuc->head.dwStreamNameSize;
	strName.MaximumLength = strName.Length;
	strName.Buffer = pbuc->head.cStreamName;

	InitializeObjectAttributes(
		&oa,
		&strName,
		OBJ_CASE_INSENSITIVE,
		hFile,
		NULL);

	Status = NtCreateFile(
		    &pbuc->hAlternate,
		    FILE_GENERIC_WRITE,
		    &oa,
		    &iosb,
		    NULL,
		    FILE_ATTRIBUTE_NORMAL,
		    FILE_SHARE_READ | FILE_SHARE_WRITE,
		    FILE_OVERWRITE_IF,
		    FILE_SYNCHRONOUS_IO_NONALERT | FILE_OPEN_FOR_BACKUP_INTENT,
		    NULL,
		    0L);

	if (!NT_SUCCESS(Status)) {
	    BaseSetLastNTError(Status);
	    pbuc->fAccessError = TRUE;
	    return(FALSE);
	}
	pbuc->fStreamStart = FALSE;
    }

    if (pbuc->hAlternate == INVALID_HANDLE_VALUE) {
	pbuc->fAccessError = TRUE;
	return(FALSE);
    }
    return(BackupWriteStream(pbuc->hAlternate, pbuc, pbif));
}