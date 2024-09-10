// start event dispatching
NTSTATUS
DokanEventStart(
    __in PDEVICE_OBJECT DeviceObject,
    __in PIRP Irp
   )
{
	ULONG				outBufferLen;
	ULONG				inBufferLen;
	PIO_STACK_LOCATION	irpSp;
	EVENT_START			eventStart;
	PEVENT_DRIVER_INFO	driverInfo;
	PDOKAN_GLOBAL		dokanGlobal;
	PDokanDCB			dcb;
	NTSTATUS			status;
	DEVICE_TYPE			deviceType;
	ULONG				deviceCharacteristics;
	WCHAR				baseGuidString[64];
	GUID				baseGuid = DOKAN_BASE_GUID;
	UNICODE_STRING		unicodeGuid;
	ULONG				deviceNamePos;
	

	DDbgPrint("==> DokanEventStart\n");

	dokanGlobal = DeviceObject->DeviceExtension;
	if (GetIdentifierType(dokanGlobal) != DGL) {
		return STATUS_INVALID_PARAMETER;
	}

	irpSp = IoGetCurrentIrpStackLocation(Irp);

	outBufferLen = irpSp->Parameters.DeviceIoControl.OutputBufferLength;
	inBufferLen = irpSp->Parameters.DeviceIoControl.InputBufferLength;

	if (outBufferLen != sizeof(EVENT_DRIVER_INFO) ||
		inBufferLen != sizeof(EVENT_START)) {
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	RtlCopyMemory(&eventStart, Irp->AssociatedIrp.SystemBuffer, sizeof(EVENT_START));
	driverInfo = Irp->AssociatedIrp.SystemBuffer;

	if (eventStart.UserVersion != DOKAN_DRIVER_VERSION) {
		driverInfo->DriverVersion = DOKAN_DRIVER_VERSION;
		driverInfo->Status = DOKAN_START_FAILED;
		Irp->IoStatus.Status = STATUS_SUCCESS;
		Irp->IoStatus.Information = sizeof(EVENT_DRIVER_INFO);
		return STATUS_SUCCESS;
	}

	deviceCharacteristics = FILE_DEVICE_IS_MOUNTED;

	switch (eventStart.DeviceType) {
	case DOKAN_DISK_FILE_SYSTEM:
		deviceType = FILE_DEVICE_DISK_FILE_SYSTEM;
		break;
	case DOKAN_NETWORK_FILE_SYSTEM:
		deviceType = FILE_DEVICE_NETWORK_FILE_SYSTEM;
		deviceCharacteristics |= FILE_REMOTE_DEVICE;
		break;
	default:
		DDbgPrint("  Unknown device type: %d\n", eventStart.DeviceType);
		deviceType = FILE_DEVICE_DISK_FILE_SYSTEM;
	}

	if (eventStart.Flags & DOKAN_EVENT_REMOVABLE) {
		DDbgPrint("  DeviceCharacteristics |= FILE_REMOVABLE_MEDIA\n");
		deviceCharacteristics |= FILE_REMOVABLE_MEDIA;
	}

	baseGuid.Data2 = (USHORT)(dokanGlobal->MountId & 0xFFFF) ^ baseGuid.Data2;
	baseGuid.Data3 = (USHORT)(dokanGlobal->MountId >> 16) ^ baseGuid.Data3;

	status = RtlStringFromGUID(&baseGuid, &unicodeGuid);
	if (!NT_SUCCESS(status)) {
		return status;
	}
	RtlZeroMemory(baseGuidString, sizeof(baseGuidString));
	RtlStringCchCopyW(baseGuidString, sizeof(baseGuidString) / sizeof(WCHAR), unicodeGuid.Buffer);
	RtlFreeUnicodeString(&unicodeGuid);

	InterlockedIncrement((LONG*)&dokanGlobal->MountId);

	KeEnterCriticalRegion();
	ExAcquireResourceExclusiveLite(&dokanGlobal->Resource, TRUE);

	status = DokanCreateDiskDevice(
				DeviceObject->DriverObject,
				dokanGlobal->MountId,
				baseGuidString,
				dokanGlobal,
				deviceType,
				deviceCharacteristics,
				&dcb);

	if (!NT_SUCCESS(status)) {
		ExReleaseResourceLite(&dokanGlobal->Resource);
		KeLeaveCriticalRegion();
		return status;
	}

	DDbgPrint("  MountId:%d\n", dcb->MountId);
	driverInfo->DeviceNumber = dokanGlobal->MountId;
	driverInfo->MountId = dokanGlobal->MountId;
	driverInfo->Status = DOKAN_MOUNTED;
	driverInfo->DriverVersion = DOKAN_DRIVER_VERSION;

	// SymbolicName is \\DosDevices\\Global\\Volume{D6CC17C5-1734-4085-BCE7-964F1E9F5DE9}
	// Finds the last '\' and copy into DeviceName.
	// DeviceName is \Volume{D6CC17C5-1734-4085-BCE7-964F1E9F5DE9}
	deviceNamePos = dcb->SymbolicLinkName->Length / sizeof(WCHAR) - 1;
	for (; dcb->SymbolicLinkName->Buffer[deviceNamePos] != L'\\'; --deviceNamePos)
		;
	RtlStringCchCopyW(driverInfo->DeviceName,
			sizeof(driverInfo->DeviceName) / sizeof(WCHAR),
			&(dcb->SymbolicLinkName->Buffer[deviceNamePos]));

	DDbgPrint("  DeviceName:%ws\n", driverInfo->DeviceName);
	DokanUpdateTimeout(&dcb->TickCount, DOKAN_KEEPALIVE_TIMEOUT);

	dcb->UseAltStream = 0;
	if (eventStart.Flags & DOKAN_EVENT_ALTERNATIVE_STREAM_ON) {
		DDbgPrint("  ALT_STREAM_ON\n");
		dcb->UseAltStream = 1;
	}
	dcb->UseKeepAlive = 0;
	if (eventStart.Flags & DOKAN_EVENT_KEEP_ALIVE_ON) {
		DDbgPrint("  KEEP_ALIVE_ON\n");
		dcb->UseKeepAlive = 1;
	}
	dcb->Mounted = 1;

	DokanStartEventNotificationThread(dcb);
	DokanStartCheckThread(dcb);

	ExReleaseResourceLite(&dokanGlobal->Resource);
	KeLeaveCriticalRegion();

	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = sizeof(EVENT_DRIVER_INFO);

	DDbgPrint("<== DokanEventStart\n");

	return Irp->IoStatus.Status;
}