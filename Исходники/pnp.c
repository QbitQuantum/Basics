static
VOID
ProcessorSetFriendlyName(
    PDEVICE_OBJECT DeviceObject)
{
    KEY_VALUE_PARTIAL_INFORMATION *Buffer = NULL;
    OBJECT_ATTRIBUTES ObjectAttributes;
    UNICODE_STRING HardwareKeyName, ValueName, EnumKeyName;
    HANDLE KeyHandle = NULL;
    ULONG DataLength = 0;
    ULONG BufferLength = 0;
    NTSTATUS Status;
    PWSTR KeyNameBuffer = NULL;
    PWSTR DeviceId = NULL;
    PWSTR InstanceId = NULL;
    PWSTR pszPrefix = L"\\Registry\\Machine\\System\\CurrentcontrolSet\\Enum";

    RtlInitUnicodeString(&HardwareKeyName,
                         L"\\Registry\\Machine\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0");
    InitializeObjectAttributes(&ObjectAttributes,
                               &HardwareKeyName,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               NULL,
                               NULL);
    Status = ZwOpenKey(&KeyHandle,
                       KEY_READ,
                       &ObjectAttributes);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("ZwOpenKey() failed (Status 0x%08lx)\n", Status);
        return;
    }

    RtlInitUnicodeString(&ValueName,
                         L"ProcessorNameString");
    Status = ZwQueryValueKey(KeyHandle,
                             &ValueName,
                             KeyValuePartialInformation,
                             NULL,
                             0,
                             &DataLength);
    if (Status != STATUS_BUFFER_OVERFLOW && Status != STATUS_BUFFER_TOO_SMALL && Status != STATUS_SUCCESS)
    {
        DPRINT1("ZwQueryValueKey() failed (Status 0x%08lx)\n", Status);
        goto done;
    }

    Buffer = ExAllocatePool(PagedPool,
                            DataLength + sizeof(KEY_VALUE_PARTIAL_INFORMATION));
    if (Buffer == NULL)
    {
        DPRINT1("ExAllocatePool() failed\n");
        goto done;
    }

    Status = ZwQueryValueKey(KeyHandle,
                             &ValueName,
                             KeyValuePartialInformation,
                             Buffer,
                             DataLength + sizeof(KEY_VALUE_PARTIAL_INFORMATION),
                             &DataLength);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("ZwQueryValueKey() failed (Status 0x%08lx)\n", Status);
        goto done;
    }

    DPRINT("ProcessorNameString: %S\n", (PWSTR)&Buffer->Data[0]);

    ZwClose(KeyHandle);
    KeyHandle = NULL;

    Status = GetDeviceId(DeviceObject,
                         BusQueryDeviceID,
                         &DeviceId);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("GetDeviceId() failed (Status 0x%08lx)\n", Status);
        goto done;
    }

    DPRINT("DeviceId: %S\n", DeviceId);

    Status = GetDeviceId(DeviceObject,
                         BusQueryInstanceID,
                         &InstanceId);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("GetDeviceId() failed (Status 0x%08lx)\n", Status);
        goto done;
    }

    DPRINT("InstanceId: %S\n", InstanceId);

    BufferLength = wcslen(pszPrefix) + 1 + wcslen(DeviceId) + 1 + wcslen(InstanceId) + 1;

    KeyNameBuffer = ExAllocatePool(PagedPool, BufferLength * sizeof(WCHAR));
    if (KeyNameBuffer == NULL)
    {
        DPRINT1("ExAllocatePool() failed\n");
        goto done;
    }

    swprintf(KeyNameBuffer, L"%s\\%s\\%s", pszPrefix, DeviceId, InstanceId);

    RtlInitUnicodeString(&EnumKeyName, KeyNameBuffer);
    InitializeObjectAttributes(&ObjectAttributes,
                               &EnumKeyName,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               NULL,
                               NULL);
    Status = ZwOpenKey(&KeyHandle,
                       KEY_WRITE,
                       &ObjectAttributes);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("ZwOpenKey() failed (Status 0x%08lx)\n", Status);
        goto done;
    }

    RtlInitUnicodeString(&ValueName,
                         L"FriendlyName");
    Status = ZwSetValueKey(KeyHandle,
                           &ValueName,
                           0,
                           REG_SZ,
                           (PVOID)&Buffer->Data[0],
                           Buffer->DataLength);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("ZwSetValueKey() failed (Status 0x%08lx)\n", Status);
        goto done;
    }

done:
    if (KeyHandle != NULL)
        ZwClose(KeyHandle);

    if (KeyNameBuffer != NULL)
        ExFreePool(KeyNameBuffer);

    if (InstanceId != NULL)
        ExFreePool(InstanceId);

    if (DeviceId != NULL)
        ExFreePool(DeviceId);

    if (Buffer != NULL)
        ExFreePool(Buffer);
}