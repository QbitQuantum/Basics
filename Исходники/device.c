NTSTATUS _IoCreateDeviceEx(PDRIVER_OBJECT_EX DriverObject, ULONG DeviceExtensionSize, PUNICODE_STRING DeviceName,
		DEVICE_TYPE DeviceType, ULONG DeviceCharacteristics, BOOLEAN Exclusive, PDEVICE_OBJECT_EX* DeviceObject)
{
	int status;
	char* DeviceBasePath;
	DEVICE_OBJECT_EX* pDeviceObjectEx;

	DeviceBasePath = GetDeviceFileUnixDomainSocketBaseFilePathA();

	if (!PathFileExistsA(DeviceBasePath))
	{
		if (!mkdir(DeviceBasePath, S_IRUSR | S_IWUSR | S_IXUSR))
		{
			free(DeviceBasePath);
			return STATUS_ACCESS_DENIED;
		}
	}

	pDeviceObjectEx = (DEVICE_OBJECT_EX*) malloc(sizeof(DEVICE_OBJECT_EX));

	if (!pDeviceObjectEx)
	{
		return STATUS_NO_MEMORY;
	}

	ZeroMemory(pDeviceObjectEx, sizeof(DEVICE_OBJECT_EX));

	ConvertFromUnicode(CP_UTF8, 0, DeviceName->Buffer, DeviceName->Length / 2, &(pDeviceObjectEx->DeviceName), 0, NULL, NULL);

	pDeviceObjectEx->DeviceFileName = GetDeviceFileUnixDomainSocketFilePathA(pDeviceObjectEx->DeviceName);

	if (PathFileExistsA(pDeviceObjectEx->DeviceFileName))
	{
		unlink(pDeviceObjectEx->DeviceFileName);
	}

	status = mkfifo(pDeviceObjectEx->DeviceFileName, 0666);

	*((ULONG_PTR*) (DeviceObject)) = (ULONG_PTR) pDeviceObjectEx;

	return STATUS_SUCCESS;
}