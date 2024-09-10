int XReadFile(
	int handle,
	void *buffer,
	unsigned int numberOfBytesToRead,
	unsigned int *numberOfBytesRead)
{
	IO_STATUS_BLOCK ioStatusBlock;
	NTSTATUS        status;

#ifdef DEBUG
	debugPrint("XReadFile handle=%08x numberOfBytesToRead=%08x\n", handle, numberOfBytesToRead);
#endif
	
	if (numberOfBytesRead)
		*numberOfBytesRead = 0;
	
	status = NtReadFile(
		(void*)handle,
		NULL,
		NULL,
		NULL,
		(void*)&ioStatusBlock,
		(void*)buffer,
		numberOfBytesToRead,
		NULL);
	
	if (status == STATUS_SUCCESS)
		status = NtWaitForSingleObject((void*)handle, FALSE, (void*)NULL);
	
	if (!NT_SUCCESS(status))
		return RtlNtStatusToDosError(status);
	else
	{
		if (numberOfBytesRead)
			*numberOfBytesRead = (unsigned int)ioStatusBlock.Information;
		return STATUS_SUCCESS;
	}
}