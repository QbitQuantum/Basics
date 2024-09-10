NTSTATUS
DokanSetEndOfFileInformation(
	 PEVENT_CONTEXT		EventContext,
	 PDOKAN_FILE_INFO	FileInfo,
	 PDOKAN_OPERATIONS	DokanOperations)
{
	PFILE_END_OF_FILE_INFORMATION endInfo =
		(PFILE_END_OF_FILE_INFORMATION)((PCHAR)EventContext + EventContext->Operation.SetFile.BufferOffset);

	if (!DokanOperations->SetEndOfFile)
		return STATUS_NOT_IMPLEMENTED;

	return DokanOperations->SetEndOfFile(
		EventContext->Operation.SetFile.FileName,
		endInfo->EndOfFile.QuadPart,
		FileInfo);
}