VOID FindNetworkAdapters(
    _In_ PDV_NETADAPTER_CONTEXT Context
    )
{
    if (Context->UseAlternateMethod)
    {
        ULONG flags = GAA_FLAG_SKIP_UNICAST | GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_DNS_SERVER | GAA_FLAG_INCLUDE_ALL_INTERFACES;
        ULONG bufferLength = 0;
        PVOID buffer;

        if (GetAdaptersAddresses(AF_UNSPEC, flags, NULL, NULL, &bufferLength) != ERROR_BUFFER_OVERFLOW)
            return;

        buffer = PhAllocate(bufferLength);
        memset(buffer, 0, bufferLength);

        if (GetAdaptersAddresses(AF_UNSPEC, flags, NULL, buffer, &bufferLength) == ERROR_SUCCESS)
        {
            PhAcquireQueuedLockShared(&NetworkAdaptersListLock);

            for (PIP_ADAPTER_ADDRESSES i = buffer; i; i = i->Next)
            {
                PPH_STRING description;

                if (description = PhCreateString(i->Description))
                {
                    AddNetworkAdapterToListView(
                        Context,
                        TRUE,
                        i->IfIndex,
                        i->Luid,
                        PhConvertMultiByteToUtf16(i->AdapterName),
                        description
                        );

                    PhDereferenceObject(description);
                }
            }

            PhReleaseQueuedLockShared(&NetworkAdaptersListLock);
        }

        PhFree(buffer);
    }
    else
    {
        static PH_STRINGREF devicePathSr = PH_STRINGREF_INIT(L"\\\\.\\");
        PPH_LIST deviceList;
        PWSTR deviceInterfaceList;
        ULONG deviceInterfaceListLength = 0;
        PWSTR deviceInterface;

        if (CM_Get_Device_Interface_List_Size(
            &deviceInterfaceListLength,
            (PGUID)&GUID_DEVINTERFACE_NET,
            NULL,
            CM_GET_DEVICE_INTERFACE_LIST_ALL_DEVICES
            ) != CR_SUCCESS)
        {
            return;
        }

        deviceInterfaceList = PhAllocate(deviceInterfaceListLength * sizeof(WCHAR));
        memset(deviceInterfaceList, 0, deviceInterfaceListLength * sizeof(WCHAR));

        if (CM_Get_Device_Interface_List(
            (PGUID)&GUID_DEVINTERFACE_NET,
            NULL,
            deviceInterfaceList,
            deviceInterfaceListLength,
            CM_GET_DEVICE_INTERFACE_LIST_ALL_DEVICES
            ) != CR_SUCCESS)
        {
            PhFree(deviceInterfaceList);
            return;
        }

        deviceList = PH_AUTO(PhCreateList(1));

        for (deviceInterface = deviceInterfaceList; *deviceInterface; deviceInterface += PhCountStringZ(deviceInterface) + 1)
        {
            HKEY keyHandle;
            DEVINST deviceInstanceHandle;
            PPH_STRING deviceDescription = NULL;

            if (!QueryNetworkDeviceInterfaceDescription(deviceInterface, &deviceInstanceHandle, &deviceDescription))
                continue;

            if (CM_Open_DevInst_Key(
                deviceInstanceHandle,
                KEY_QUERY_VALUE,
                0,
                RegDisposition_OpenExisting,
                &keyHandle,
                CM_REGISTRY_SOFTWARE
                ) == CR_SUCCESS)
            {
                PNET_ENUM_ENTRY adapterEntry;
                HANDLE deviceHandle;

                adapterEntry = PhAllocate(sizeof(NET_ENUM_ENTRY));
                memset(adapterEntry, 0, sizeof(NET_ENUM_ENTRY));

                adapterEntry->DeviceGuid = PhQueryRegistryString(keyHandle, L"NetCfgInstanceId");
                adapterEntry->DeviceInterface = PhConcatStringRef2(&devicePathSr, &adapterEntry->DeviceGuid->sr);
                adapterEntry->DeviceLuid.Info.IfType = PhQueryRegistryUlong64(keyHandle, L"*IfType");
                adapterEntry->DeviceLuid.Info.NetLuidIndex = PhQueryRegistryUlong64(keyHandle, L"NetLuidIndex");

                if (NT_SUCCESS(PhCreateFileWin32(
                    &deviceHandle,
                    PhGetString(adapterEntry->DeviceInterface),
                    FILE_GENERIC_READ,
                    FILE_ATTRIBUTE_NORMAL,
                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                    FILE_OPEN,
                    FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT
                    )))
                {
                    PPH_STRING adapterName;

                    // Try query the full adapter name
                    adapterName = NetworkAdapterQueryName(deviceHandle, adapterEntry->DeviceGuid);

                    if (adapterName)
                        adapterEntry->DeviceName = adapterName;

                    adapterEntry->DevicePresent = TRUE;

                    NtClose(deviceHandle);
                }

                if (!adapterEntry->DeviceName)
                    adapterEntry->DeviceName = PhCreateString2(&deviceDescription->sr);

                PhAddItemList(deviceList, adapterEntry);

                NtClose(keyHandle);
            }

            PhClearReference(&deviceDescription);
        }

        // Cleanup.
        PhFree(deviceInterfaceList);

        // Sort the entries
        qsort(deviceList->Items, deviceList->Count, sizeof(PVOID), AdapterEntryCompareFunction);

        PhAcquireQueuedLockShared(&NetworkAdaptersListLock);

        for (ULONG i = 0; i < deviceList->Count; i++)
        {
            PNET_ENUM_ENTRY entry = deviceList->Items[i];

            AddNetworkAdapterToListView(
                Context,
                entry->DevicePresent,
                0,
                entry->DeviceLuid,
                entry->DeviceGuid,
                entry->DeviceName
                );

            if (entry->DeviceName)
                PhDereferenceObject(entry->DeviceName);
            if (entry->DeviceInterface)
                PhDereferenceObject(entry->DeviceInterface);
            // Note: DeviceGuid is disposed by WM_DESTROY.

            PhFree(entry);
        }

        PhReleaseQueuedLockShared(&NetworkAdaptersListLock);
    }

    // HACK: Show all unknown devices.
    PhAcquireQueuedLockShared(&NetworkAdaptersListLock);

    for (ULONG i = 0; i < NetworkAdaptersList->Count; i++)
    {
        ULONG index = ULONG_MAX;
        BOOLEAN found = FALSE;
        PDV_NETADAPTER_ENTRY entry = PhReferenceObjectSafe(NetworkAdaptersList->Items[i]);

        if (!entry)
            continue;

        while ((index = PhFindListViewItemByFlags(
            Context->ListViewHandle,
            index,
            LVNI_ALL
            )) != ULONG_MAX)
        {
            PDV_NETADAPTER_ID param;

            if (PhGetListViewItemParam(Context->ListViewHandle, index, &param))
            {
                if (EquivalentNetAdapterId(param, &entry->AdapterId))
                {
                    found = TRUE;
                }
            }
        }

        if (!found)
        {
            PPH_STRING description;
            MIB_IF_ROW2 interfaceRow;

            memset(&interfaceRow, 0, sizeof(MIB_IF_ROW2));
            interfaceRow.InterfaceLuid = entry->AdapterId.InterfaceLuid;
            interfaceRow.InterfaceIndex = entry->AdapterId.InterfaceIndex;

            // HACK: Try query the description from the interface entry (if it exists).
            if (GetIfEntry2(&interfaceRow) == NO_ERROR)
                description = PhCreateString(interfaceRow.Description);
            else
                description = PhCreateString(L"Unknown network adapter");

            if (description)
            {
                AddNetworkAdapterToListView(
                    Context,
                    FALSE,
                    entry->AdapterId.InterfaceIndex,
                    entry->AdapterId.InterfaceLuid,
                    entry->AdapterId.InterfaceGuid,
                    description
                    );

                PhDereferenceObject(description);
            }
        }

        PhDereferenceObjectDeferDelete(entry);
    }

    PhReleaseQueuedLockShared(&NetworkAdaptersListLock);
}