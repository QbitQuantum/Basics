PartitionStream* PartitionContext::
createPartition(const char* name, u8 type)
{
    int id = getId(name, getPrefix(name));
    if (id < 0  || 3 < id || (type == TYPE_EXTENDED && id != 0))
    {
        return 0;
    }

    if (type == TYPE_PRIMARY && 0 < id &&
            lookupPartitionStream(type, id - 1) == 0)
    {
        // A primary partition must be created in numerical order.
        return 0;
    }

    es::DiskManagement::Geometry geometry;
    getGeometry(&geometry);

    // Read MBR
    u8 mbr[geometry.bytesPerSector];
    disk->read(mbr, geometry.bytesPerSector, 0);
    if (word(mbr + MBR_Signature) != MBR_SIGNATURE)
    {
        esReport("Not found MBR.\n");
        return 0;
    }

    u8* entry = getEntry(mbr, TYPE_EMPTY, 0);
    if (!entry)
    {
        // no empty partition entry.
        return 0;
    }

    u8 entryNo = (entry - &mbr[MBR_PartitionTable]) / MBR_EntrySize;

    unsigned prevOffset;
    unsigned prevSize;
    if (entryNo == 0)
    {
        prevOffset = geometry.sectorsPerTrack;
        prevSize = 0;
    }
    else
    {
        u8* prev = entry - MBR_EntrySize;
        prevOffset = dword(prev + MBR_StartingSector);
        prevSize = dword(prev + MBR_TotalSectors);
    }

    // Create a stream for the partition.
    PartitionStream* stream = new PartitionStream(this, id, entry, entryNo);
    if (!stream)
    {
        return 0;
    }
    switch (type)
    {
    case TYPE_PRIMARY:
        partitionList.addFirst(stream);
        break;

    case TYPE_EXTENDED:
        partitionList.addLast(stream);
        break;
    }

    PartitionStream::Partition partition;
    partition.startingOffset = (long long) (prevOffset + prevSize) * geometry.bytesPerSector;
    partition.hiddenSectors = 0;
    partition.bootIndicator = 0;

    partition.partitionLength = (long long) geometry.heads *
                                geometry.sectorsPerTrack * geometry.bytesPerSector;
    stream->adjustSize(&geometry, &partition, partition.partitionLength);

    switch (type)
    {
    case TYPE_EXTENDED:
        if (MAX_CHS <= (long long) prevOffset + (long long) prevSize +
                partition.partitionLength / geometry.bytesPerSector)
        {
            partition.partitionType = PT_EXTENDED_LBA;
        }
        else
        {
            partition.partitionType = PT_EXTENDED;
        }
        stream->setType(TYPE_EXTENDED);
        break;
    case TYPE_PRIMARY:
        partition.partitionType = getDefaultPartitionType(partition.partitionLength);
        stream->setType(TYPE_PRIMARY);
        break;
    }

    stream->setLayout(&partition);
    return stream;
}