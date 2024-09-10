static VOID NTAPI ProcessesUpdatedCallback(
    __in_opt PVOID Parameter,
    __in_opt PVOID Context
    )
{
    static ULONG runCount = 0;

    PSLIST_ENTRY listEntry;
    PLIST_ENTRY ageListEntry;

    // Process incoming disk event packets.

    listEntry = RtlInterlockedFlushSList(&EtDiskPacketListHead);

    while (listEntry)
    {
        PETP_DISK_PACKET packet;

        packet = CONTAINING_RECORD(listEntry, ETP_DISK_PACKET, ListEntry);
        listEntry = listEntry->Next;

        EtpProcessDiskPacket(packet, runCount);

        if (packet->FileName)
            PhDereferenceObject(packet->FileName);

        PhFreeToFreeList(&EtDiskPacketFreeList, packet);
    }

    // Remove old entries.

    ageListEntry = EtDiskAgeListHead.Blink;

    while (ageListEntry != &EtDiskAgeListHead)
    {
        PET_DISK_ITEM diskItem;

        diskItem = CONTAINING_RECORD(ageListEntry, ET_DISK_ITEM, AgeListEntry);
        ageListEntry = ageListEntry->Blink;

        if (runCount - diskItem->FreshTime < HISTORY_SIZE) // must compare like this to avoid overflow/underflow problems
            break;

        PhInvokeCallback(&EtDiskItemRemovedEvent, diskItem);

        PhAcquireQueuedLockExclusive(&EtDiskHashtableLock);
        EtpRemoveDiskItem(diskItem);
        PhReleaseQueuedLockExclusive(&EtDiskHashtableLock);
    }

    // Update existing items.

    ageListEntry = EtDiskAgeListHead.Flink;

    while (ageListEntry != &EtDiskAgeListHead)
    {
        PET_DISK_ITEM diskItem;

        diskItem = CONTAINING_RECORD(ageListEntry, ET_DISK_ITEM, AgeListEntry);

        // Update statistics.

        if (diskItem->HistoryPosition != 0)
            diskItem->HistoryPosition--;
        else
            diskItem->HistoryPosition = HISTORY_SIZE - 1;

        diskItem->ReadHistory[diskItem->HistoryPosition] = diskItem->ReadDelta;
        diskItem->WriteHistory[diskItem->HistoryPosition] = diskItem->WriteDelta;

        if (diskItem->HistoryCount < HISTORY_SIZE)
            diskItem->HistoryCount++;

        if (diskItem->ResponseTimeCount != 0)
        {
            diskItem->ResponseTimeAverage = (FLOAT)diskItem->ResponseTimeTotal / diskItem->ResponseTimeCount;

            // Reset the total once in a while to avoid the number getting too large (and thus losing precision).
            if (diskItem->ResponseTimeCount >= 1000)
            {
                diskItem->ResponseTimeTotal = diskItem->ResponseTimeAverage;
                diskItem->ResponseTimeCount = 1;
            }
        }

        diskItem->ReadTotal += diskItem->ReadDelta;
        diskItem->WriteTotal += diskItem->WriteDelta;
        diskItem->ReadDelta = 0;
        diskItem->WriteDelta = 0;
        diskItem->ReadAverage = EtpCalculateAverage(diskItem->ReadHistory, HISTORY_SIZE, diskItem->HistoryPosition, diskItem->HistoryCount, HISTORY_SIZE);
        diskItem->WriteAverage = EtpCalculateAverage(diskItem->WriteHistory, HISTORY_SIZE, diskItem->HistoryPosition, diskItem->HistoryCount, HISTORY_SIZE);

        if (diskItem->AddTime != runCount)
        {
            BOOLEAN modified = FALSE;
            PPH_PROCESS_ITEM processItem;

            if (!diskItem->ProcessName || !diskItem->ProcessIcon || !diskItem->ProcessRecord)
            {
                if (processItem = PhReferenceProcessItem(diskItem->ProcessId))
                {
                    if (!diskItem->ProcessName)
                    {
                        diskItem->ProcessName = processItem->ProcessName;
                        PhReferenceObject(processItem->ProcessName);
                        modified = TRUE;
                    }

                    if (!diskItem->ProcessIcon)
                    {
                        diskItem->ProcessIcon = EtProcIconReferenceSmallProcessIcon(EtGetProcessBlock(processItem));

                        if (diskItem->ProcessIcon)
                            modified = TRUE;
                    }

                    if (!diskItem->ProcessRecord)
                    {
                        diskItem->ProcessRecord = processItem->Record;
                        PhReferenceProcessRecord(diskItem->ProcessRecord);
                    }

                    PhDereferenceObject(processItem);
                }
            }

            if (modified)
            {
                // Raise the disk item modified event.
                PhInvokeCallback(&EtDiskItemModifiedEvent, diskItem);
            }
        }

        ageListEntry = ageListEntry->Flink;
    }

    PhInvokeCallback(&EtDiskItemsUpdatedEvent, NULL);
    runCount++;
}