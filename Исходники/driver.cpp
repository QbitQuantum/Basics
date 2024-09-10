NTSTATUS
OnRead(PDEVICE_OBJECT pDeviceObj, PIRP pIrp)
{
	DbgPrint("OnRead\n");
	PIO_STACK_LOCATION pStack;
	PUNICODE_STRING us;

	pStack = IoGetCurrentIrpStackLocation(pIrp);
	us = (PUNICODE_STRING)pStack->FileObject->FsContext;
	ANSI_STRING as;

	RtlUnicodeStringToAnsiString(&as, us, TRUE);

	RtlZeroMemory(pIrp->AssociatedIrp.SystemBuffer, pStack->Parameters.Read.Length);
	RtlCopyMemory(pIrp->AssociatedIrp.SystemBuffer, as.Buffer, min(pStack->Parameters.Write.Length, as.Length));
	pIrp->IoStatus.Information = min(pStack->Parameters.Write.Length, as.Length);

	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	pIrp->IoStatus.Status = STATUS_SUCCESS;	
    return pIrp->IoStatus.Status;
}