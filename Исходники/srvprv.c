VOID PhServiceProviderUpdate(
    _In_ PVOID Object
    )
{
    static SC_HANDLE scManagerHandle = NULL;
    static ULONG runCount = 0;

    static PPH_HASH_ENTRY nameHashSet[256];
    static PPHP_SERVICE_NAME_ENTRY nameEntries = NULL;
    static ULONG nameEntriesCount;
    static ULONG nameEntriesAllocated = 0;

    LPENUM_SERVICE_STATUS_PROCESS services;
    ULONG numberOfServices;
    ULONG i;
    PPH_HASH_ENTRY hashEntry;

    // We always execute the first run, and we only initialize non-polling after the first run.
    if (PhEnableServiceNonPoll && runCount != 0)
    {
        if (!PhpNonPollInitialized)
        {
            if (WindowsVersion >= WINDOWS_VISTA)
            {
                PhpInitializeServiceNonPoll();
            }

            PhpNonPollInitialized = TRUE;
        }

        if (PhpNonPollActive)
        {
            if (InterlockedExchange(&PhpNonPollGate, 0) == 0)
            {
                // Non-poll gate is closed; skip all processing.
                goto UpdateEnd;
            }
        }
    }

    if (!scManagerHandle)
    {
        scManagerHandle = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT | SC_MANAGER_ENUMERATE_SERVICE);

        if (!scManagerHandle)
            return;
    }

    services = PhEnumServices(scManagerHandle, 0, 0, &numberOfServices);

    if (!services)
        return;

    // Build a hash set containing the service names.

    // This has caused a massive decrease in background CPU usage, and
    // is certainly much better than the quadratic-time string comparisons
    // we were doing before (in the "Look for dead services" section).

    nameEntriesCount = 0;

    if (nameEntriesAllocated < numberOfServices)
    {
        nameEntriesAllocated = numberOfServices + 32;

        if (nameEntries) PhFree(nameEntries);
        nameEntries = PhAllocate(sizeof(PHP_SERVICE_NAME_ENTRY) * nameEntriesAllocated);
    }

    PhInitializeHashSet(nameHashSet, PH_HASH_SET_SIZE(nameHashSet));

    for (i = 0; i < numberOfServices; i++)
    {
        PPHP_SERVICE_NAME_ENTRY entry;

        entry = &nameEntries[nameEntriesCount++];
        PhInitializeStringRefLongHint(&entry->Name, services[i].lpServiceName);
        entry->ServiceEntry = &services[i];
        PhAddEntryHashSet(
            nameHashSet,
            PH_HASH_SET_SIZE(nameHashSet),
            &entry->HashEntry,
            PhpHashServiceNameEntry(entry)
            );
    }

    // Look for dead services.
    {
        PPH_LIST servicesToRemove = NULL;
        PH_HASHTABLE_ENUM_CONTEXT enumContext;
        PPH_SERVICE_ITEM *serviceItem;

        PhBeginEnumHashtable(PhServiceHashtable, &enumContext);

        while (serviceItem = PhNextEnumHashtable(&enumContext))
        {
            BOOLEAN found = FALSE;
            PHP_SERVICE_NAME_ENTRY lookupNameEntry;

            // Check if the service still exists.

            lookupNameEntry.Name = (*serviceItem)->Name->sr;
            hashEntry = PhFindEntryHashSet(
                nameHashSet,
                PH_HASH_SET_SIZE(nameHashSet),
                PhpHashServiceNameEntry(&lookupNameEntry)
                );

            for (; hashEntry; hashEntry = hashEntry->Next)
            {
                PPHP_SERVICE_NAME_ENTRY nameEntry;

                nameEntry = CONTAINING_RECORD(hashEntry, PHP_SERVICE_NAME_ENTRY, HashEntry);

                if (PhpCompareServiceNameEntry(&lookupNameEntry, nameEntry))
                {
                    found = TRUE;
                    break;
                }
            }

            if (!found)
            {
                // Remove the service from its process.
                if ((*serviceItem)->ProcessId)
                {
                    PPH_PROCESS_ITEM processItem;

                    processItem = PhReferenceProcessItem((HANDLE)(*serviceItem)->ProcessId);

                    if (processItem)
                    {
                        PhpRemoveProcessItemService(processItem, *serviceItem);
                        PhDereferenceObject(processItem);
                    }
                }

                // Raise the service removed event.
                PhInvokeCallback(&PhServiceRemovedEvent, *serviceItem);

                if (!servicesToRemove)
                    servicesToRemove = PhCreateList(2);

                PhAddItemList(servicesToRemove, *serviceItem);
            }
        }

        if (servicesToRemove)
        {
            PhAcquireQueuedLockExclusive(&PhServiceHashtableLock);

            for (i = 0; i < servicesToRemove->Count; i++)
            {
                PhpRemoveServiceItem((PPH_SERVICE_ITEM)servicesToRemove->Items[i]);
            }

            PhReleaseQueuedLockExclusive(&PhServiceHashtableLock);
            PhDereferenceObject(servicesToRemove);
        }
    }

    // Look for new services and update existing ones.
    for (i = 0; i < PH_HASH_SET_SIZE(nameHashSet); i++)
    {
        for (hashEntry = nameHashSet[i]; hashEntry; hashEntry = hashEntry->Next)
        {
            PPH_SERVICE_ITEM serviceItem;
            PPHP_SERVICE_NAME_ENTRY nameEntry;
            ENUM_SERVICE_STATUS_PROCESS *serviceEntry;

            nameEntry = CONTAINING_RECORD(hashEntry, PHP_SERVICE_NAME_ENTRY, HashEntry);
            serviceEntry = nameEntry->ServiceEntry;
            serviceItem = PhpLookupServiceItem(&nameEntry->Name);

            if (!serviceItem)
            {
                // Create the service item and fill in basic information.

                serviceItem = PhCreateServiceItem(serviceEntry);

                PhpUpdateServiceItemConfig(scManagerHandle, serviceItem);

                // Add the service to its process, if appropriate.
                if (
                    (
                    serviceItem->State == SERVICE_RUNNING ||
                    serviceItem->State == SERVICE_PAUSED
                    ) &&
                    serviceItem->ProcessId
                    )
                {
                    PPH_PROCESS_ITEM processItem;

                    if (processItem = PhReferenceProcessItem(serviceItem->ProcessId))
                    {
                        PhpAddProcessItemService(processItem, serviceItem);
                        PhDereferenceObject(processItem);
                    }
                    else
                    {
                        // The process doesn't exist yet (to us). Set the pending
                        // flag and when the process is added this will be
                        // fixed.
                        serviceItem->PendingProcess = TRUE;
                    }
                }

                // Add the service item to the hashtable.
                PhAcquireQueuedLockExclusive(&PhServiceHashtableLock);
                PhAddEntryHashtable(PhServiceHashtable, &serviceItem);
                PhReleaseQueuedLockExclusive(&PhServiceHashtableLock);

                // Raise the service added event.
                PhInvokeCallback(&PhServiceAddedEvent, serviceItem);
            }
            else
            {
                if (
                    serviceItem->Type != serviceEntry->ServiceStatusProcess.dwServiceType ||
                    serviceItem->State != serviceEntry->ServiceStatusProcess.dwCurrentState ||
                    serviceItem->ControlsAccepted != serviceEntry->ServiceStatusProcess.dwControlsAccepted ||
                    serviceItem->ProcessId != UlongToHandle(serviceEntry->ServiceStatusProcess.dwProcessId) ||
                    serviceItem->NeedsConfigUpdate
                    )
                {
                    PH_SERVICE_MODIFIED_DATA serviceModifiedData;
                    PH_SERVICE_CHANGE serviceChange;

                    // The service has been "modified".

                    serviceModifiedData.Service = serviceItem;
                    memset(&serviceModifiedData.OldService, 0, sizeof(PH_SERVICE_ITEM));
                    serviceModifiedData.OldService.Type = serviceItem->Type;
                    serviceModifiedData.OldService.State = serviceItem->State;
                    serviceModifiedData.OldService.ControlsAccepted = serviceItem->ControlsAccepted;
                    serviceModifiedData.OldService.ProcessId = serviceItem->ProcessId;

                    // Update the service item.
                    serviceItem->Type = serviceEntry->ServiceStatusProcess.dwServiceType;
                    serviceItem->State = serviceEntry->ServiceStatusProcess.dwCurrentState;
                    serviceItem->ControlsAccepted = serviceEntry->ServiceStatusProcess.dwControlsAccepted;
                    serviceItem->ProcessId = UlongToHandle(serviceEntry->ServiceStatusProcess.dwProcessId);

                    if (serviceItem->ProcessId)
                        PhPrintUInt32(serviceItem->ProcessIdString, HandleToUlong(serviceItem->ProcessId));
                    else
                        serviceItem->ProcessIdString[0] = 0;

                    // Add/remove the service from its process.

                    serviceChange = PhGetServiceChange(&serviceModifiedData);

                    if (
                        (serviceChange == ServiceStarted && serviceItem->ProcessId) ||
                        (serviceChange == ServiceStopped && serviceModifiedData.OldService.ProcessId)
                        )
                    {
                        PPH_PROCESS_ITEM processItem;

                        if (serviceChange == ServiceStarted)
                            processItem = PhReferenceProcessItem(serviceItem->ProcessId);
                        else
                            processItem = PhReferenceProcessItem(serviceModifiedData.OldService.ProcessId);

                        if (processItem)
                        {
                            if (serviceChange == ServiceStarted)
                                PhpAddProcessItemService(processItem, serviceItem);
                            else
                                PhpRemoveProcessItemService(processItem, serviceItem);

                            PhDereferenceObject(processItem);
                        }
                        else
                        {
                            if (serviceChange == ServiceStarted)
                                serviceItem->PendingProcess = TRUE;
                            else
                                serviceItem->PendingProcess = FALSE;
                        }
                    }
                    else if (
                        serviceItem->State == SERVICE_RUNNING &&
                        serviceItem->ProcessId != serviceModifiedData.OldService.ProcessId &&
                        serviceItem->ProcessId
                        )
                    {
                        PPH_PROCESS_ITEM processItem;

                        // The service stopped and started, and the only change we have detected
                        // is in the process ID.

                        if (processItem = PhReferenceProcessItem(serviceModifiedData.OldService.ProcessId))
                        {
                            PhpRemoveProcessItemService(processItem, serviceItem);
                            PhDereferenceObject(processItem);
                        }

                        if (processItem = PhReferenceProcessItem(serviceItem->ProcessId))
                        {
                            PhpAddProcessItemService(processItem, serviceItem);
                            PhDereferenceObject(processItem);
                        }
                        else
                        {
                            serviceItem->PendingProcess = TRUE;
                        }
                    }

                    // Do a config update if necessary.
                    if (serviceItem->NeedsConfigUpdate)
                    {
                        PhpUpdateServiceItemConfig(scManagerHandle, serviceItem);
                        serviceItem->NeedsConfigUpdate = FALSE;
                    }

                    // Raise the service modified event.
                    PhInvokeCallback(&PhServiceModifiedEvent, &serviceModifiedData);
                }
            }
        }
    }

    PhFree(services);

UpdateEnd:
    PhInvokeCallback(&PhServicesUpdatedEvent, NULL);
    runCount++;
}