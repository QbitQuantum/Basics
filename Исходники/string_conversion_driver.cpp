NTSTATUS
OnRead(PDEVICE_OBJECT   pDeviceObj,
        PIRP            pIrp)
{
	DbgPrint("%s", "Read Called\n");

	PIO_STACK_LOCATION stack_location = IoGetCurrentIrpStackLocation(pIrp);
	ULONG read_size = stack_location->Parameters.Read.Length;
	PVOID& system_buffer = pIrp->AssociatedIrp.SystemBuffer;
	PVOID &context = stack_location->FileObject->FsContext;
	ANSI_STRING ansi_string = {};

	if(context == NULL)
	{
		pIrp->IoStatus.Information = 0;
		pIrp->IoStatus.Status = STATUS_INVALID_PARAMETER;
		IoCompleteRequest(pIrp, IO_NO_INCREMENT);
		return STATUS_INVALID_PARAMETER;
	}

	if(read_size > ((PUNICODE_STRING)context)->Length)
	{
		pIrp->IoStatus.Information = 0;
		pIrp->IoStatus.Status = STATUS_INSUFFICIENT_RESOURCES;
		IoCompleteRequest(pIrp, IO_NO_INCREMENT);
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	RtlUnicodeStringToAnsiString(&ansi_string, (PUNICODE_STRING)context, TRUE);
	RtlCopyMemory(pIrp->AssociatedIrp.SystemBuffer, ansi_string.Buffer, read_size);
	RtlFreeAnsiString(&ansi_string);
	RtlFreeUnicodeString((PUNICODE_STRING)context);
	ExFreePoolWithTag(context, TAG_CONVERSION);
	context = NULL;

	pIrp->IoStatus.Information = read_size;
    pIrp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
    return STATUS_SUCCESS;
}