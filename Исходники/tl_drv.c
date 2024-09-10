void
TLInspectLoadConfig(
    IN  PUNICODE_STRING registryPath
)
{
    NTSTATUS status;

    OBJECT_ATTRIBUTES objectAttributes;
    UNICODE_STRING valueName;
    KEY_VALUE_PARTIAL_INFORMATION* regValue =
        (KEY_VALUE_PARTIAL_INFORMATION*)gRegValueStorage;
    ULONG resultLength;

    InitializeObjectAttributes(
        &objectAttributes,
        registryPath,
        OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
        NULL,
        NULL
    );

    status = ZwOpenKey(
                 &gRegistryKey,
                 KEY_READ,
                 &objectAttributes
             );
    if (NT_SUCCESS(status))
    {
        RtlInitUnicodeString(
            &valueName,
            L"RemoteAddressToInspect"
        );

        status = ZwQueryValueKey(
                     gRegistryKey,
                     &valueName,
                     KeyValuePartialInformation,
                     regValue,
                     sizeof(gRegValueStorage),
                     &resultLength
                 );

        if (NT_SUCCESS(status))
        {
            PWSTR terminator;

            status = RtlIpv4StringToAddressW(
                         (PCWSTR)(regValue->Data),
                         TRUE,
                         &terminator,
                         &remoteAddrStorageV4
                     );

            if (NT_SUCCESS(status))
            {
                remoteAddrStorageV4.S_un.S_addr =
                    RtlUlongByteSwap(remoteAddrStorageV4.S_un.S_addr);
                configInspectRemoteAddrV4 = &remoteAddrStorageV4.S_un.S_un_b.s_b1;
            }
            else
            {
                status = RtlIpv6StringToAddressW(
                             (PCWSTR)(regValue->Data),
                             &terminator,
                             &remoteAddrStorageV6
                         );

                if (NT_SUCCESS(status))
                {
                    configInspectRemoteAddrV6 = (UINT8*)(&remoteAddrStorageV6.u.Byte[0]);
                }
            }
        }
    }
}