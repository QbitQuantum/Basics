static
NTSTATUS
OpenRegistryHandlesFromSymbolicLink(IN PUNICODE_STRING SymbolicLinkName,
                                    IN ACCESS_MASK DesiredAccess,
                                    IN OPTIONAL PHANDLE GuidKey,
                                    IN OPTIONAL PHANDLE DeviceKey,
                                    IN OPTIONAL PHANDLE InstanceKey)
{
    OBJECT_ATTRIBUTES ObjectAttributes;
    WCHAR PathBuffer[MAX_PATH];
    UNICODE_STRING BaseKeyU;
    UNICODE_STRING GuidString, SubKeyName, ReferenceString;
    PWCHAR StartPosition, EndPosition;
    HANDLE ClassesKey;
    PHANDLE GuidKeyRealP, DeviceKeyRealP, InstanceKeyRealP;
    HANDLE GuidKeyReal, DeviceKeyReal, InstanceKeyReal;
    NTSTATUS Status;

    SubKeyName.Buffer = NULL;

    if (GuidKey != NULL)
        GuidKeyRealP = GuidKey;
    else
        GuidKeyRealP = &GuidKeyReal;

    if (DeviceKey != NULL)
        DeviceKeyRealP = DeviceKey;
    else
        DeviceKeyRealP = &DeviceKeyReal;

    if (InstanceKey != NULL)
        InstanceKeyRealP = InstanceKey;
    else
        InstanceKeyRealP = &InstanceKeyReal;

    *GuidKeyRealP = INVALID_HANDLE_VALUE;
    *DeviceKeyRealP = INVALID_HANDLE_VALUE;
    *InstanceKeyRealP = INVALID_HANDLE_VALUE;

    BaseKeyU.Buffer = PathBuffer;
    BaseKeyU.Length = 0;
    BaseKeyU.MaximumLength = MAX_PATH * sizeof(WCHAR);

    RtlAppendUnicodeToString(&BaseKeyU, BaseKeyString);

    /* Open the DeviceClasses key */
    InitializeObjectAttributes(&ObjectAttributes,
                               &BaseKeyU,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               NULL,
                               NULL);
    Status = ZwOpenKey(&ClassesKey,
                       DesiredAccess | KEY_ENUMERATE_SUB_KEYS,
                       &ObjectAttributes);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Failed to open %wZ\n", &BaseKeyU);
        goto cleanup;
    }

    StartPosition = wcschr(SymbolicLinkName->Buffer, L'{');
    EndPosition = wcschr(SymbolicLinkName->Buffer, L'}');
    if (!StartPosition || !EndPosition || StartPosition > EndPosition)
    {
        DPRINT1("Bad symbolic link: %wZ\n", SymbolicLinkName);
        return STATUS_INVALID_PARAMETER_1;
    }
    GuidString.Buffer = StartPosition;
    GuidString.MaximumLength = GuidString.Length = (USHORT)((ULONG_PTR)(EndPosition + 1) - (ULONG_PTR)StartPosition);

    InitializeObjectAttributes(&ObjectAttributes,
                               &GuidString,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               ClassesKey,
                               NULL);
    Status = ZwOpenKey(GuidKeyRealP,
                       DesiredAccess | KEY_ENUMERATE_SUB_KEYS,
                       &ObjectAttributes);
    ZwClose(ClassesKey);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Failed to open %wZ%wZ (%x)\n", &BaseKeyU, &GuidString, Status);
        goto cleanup;
    }

    SubKeyName.MaximumLength = SymbolicLinkName->Length + sizeof(WCHAR);
    SubKeyName.Length = 0;
    SubKeyName.Buffer = ExAllocatePool(PagedPool, SubKeyName.MaximumLength);
    if (!SubKeyName.Buffer)
    {
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto cleanup;
    }

    RtlAppendUnicodeStringToString(&SubKeyName,
                                   SymbolicLinkName);

    SubKeyName.Buffer[SubKeyName.Length / sizeof(WCHAR)] = UNICODE_NULL;

    SubKeyName.Buffer[0] = L'#';
    SubKeyName.Buffer[1] = L'#';
    SubKeyName.Buffer[2] = L'?';
    SubKeyName.Buffer[3] = L'#';

    ReferenceString.Buffer = wcsrchr(SubKeyName.Buffer, '\\');
    if (ReferenceString.Buffer != NULL)
    {
        ReferenceString.Buffer[0] = L'#';

        SubKeyName.Length = (USHORT)((ULONG_PTR)(ReferenceString.Buffer) - (ULONG_PTR)SubKeyName.Buffer);
        ReferenceString.Length = SymbolicLinkName->Length - SubKeyName.Length;
    }
    else
    {
        RtlInitUnicodeString(&ReferenceString, L"#");
    }

    InitializeObjectAttributes(&ObjectAttributes,
                               &SubKeyName,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               *GuidKeyRealP,
                               NULL);
    Status = ZwOpenKey(DeviceKeyRealP,
                       DesiredAccess | KEY_ENUMERATE_SUB_KEYS,
                       &ObjectAttributes);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Failed to open %wZ%wZ\\%wZ\n", &BaseKeyU, &GuidString, &SubKeyName);
        goto cleanup;
    }

    InitializeObjectAttributes(&ObjectAttributes,
                               &ReferenceString,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               *DeviceKeyRealP,
                               NULL);
    Status = ZwOpenKey(InstanceKeyRealP,
                       DesiredAccess,
                       &ObjectAttributes);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Failed to open %wZ%wZ\\%wZ%\\%wZ (%x)\n", &BaseKeyU, &GuidString, &SubKeyName, &ReferenceString, Status);
        goto cleanup;
    }

    Status = STATUS_SUCCESS;

cleanup:
    if (SubKeyName.Buffer != NULL)
       ExFreePool(SubKeyName.Buffer);

    if (NT_SUCCESS(Status))
    {
       if (!GuidKey)
          ZwClose(*GuidKeyRealP);

       if (!DeviceKey)
          ZwClose(*DeviceKeyRealP);

       if (!InstanceKey)
          ZwClose(*InstanceKeyRealP);
    }
    else
    {
       if (*GuidKeyRealP != INVALID_HANDLE_VALUE)
          ZwClose(*GuidKeyRealP);

       if (*DeviceKeyRealP != INVALID_HANDLE_VALUE)
          ZwClose(*DeviceKeyRealP);

       if (*InstanceKeyRealP != INVALID_HANDLE_VALUE)
          ZwClose(*InstanceKeyRealP);
    }

    return Status;
}