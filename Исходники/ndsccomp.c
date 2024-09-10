NTSTATUS
IoctlToLanscsiBusByWorker(
	IN PDEVICE_OBJECT	WorkerDeviceObject,
	IN ULONG			IoControlCode,
    IN PVOID			InputBuffer  OPTIONAL,
    IN ULONG			InputBufferLength
) {
	NDSC_WORKITEM_INIT	WorkitemCtx;
	NTSTATUS			status;

	NDSC_INIT_WORKITEM(	&WorkitemCtx,
							IoctlToLanscsiBus_Worker,
							(PCCB)UlongToPtr(IoControlCode),
							InputBuffer,
							UlongToPtr(InputBufferLength),
							NULL);
	status = MiniQueueWorkItem(&NdasMiniGlobalData, WorkerDeviceObject, &WorkitemCtx);
	if(!NT_SUCCESS(status)) {
		if(InputBufferLength && InputBuffer)
			ExFreePoolWithTag(InputBuffer, NDSC_PTAG_IOCTL);
	}

	return status;
}