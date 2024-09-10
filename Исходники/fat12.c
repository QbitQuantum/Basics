NTSTATUS
Fat12Format(IN HANDLE FileHandle,
            IN PPARTITION_INFORMATION PartitionInfo,
            IN PDISK_GEOMETRY DiskGeometry,
            IN PUNICODE_STRING Label,
            IN BOOLEAN QuickFormat,
            IN ULONG ClusterSize,
            IN OUT PFORMAT_CONTEXT Context)
{
    FAT16_BOOT_SECTOR BootSector;
    OEM_STRING VolumeLabel;
    ULONG SectorCount;
    ULONG RootDirSectors;
    ULONG TmpVal1;
    ULONG TmpVal2;
    ULONG TmpVal3;
    NTSTATUS Status;

    /* Calculate cluster size */
    if (ClusterSize == 0)
    {
        if (DiskGeometry->MediaType == FixedMedia)
        {
            /* 4KB Cluster (Harddisk only) */
            ClusterSize = 4096;
        }
        else
        {
            /* 512 byte cluster (floppy) */
            ClusterSize = 512;
        }
    }

    SectorCount = PartitionInfo->PartitionLength.QuadPart >>
        GetShiftCount(DiskGeometry->BytesPerSector); /* Use shifting to avoid 64-bit division */

    DPRINT("SectorCount = %lu\n", SectorCount);

    memset(&BootSector, 0, sizeof(FAT16_BOOT_SECTOR));
    memcpy(&BootSector.OEMName[0], "MSWIN4.1", 8);
    BootSector.BytesPerSector = DiskGeometry->BytesPerSector;
    BootSector.SectorsPerCluster = ClusterSize / BootSector.BytesPerSector;
    BootSector.ReservedSectors = 1;
    BootSector.FATCount = 2;
    BootSector.RootEntries = 512;
    BootSector.Sectors = (SectorCount < 0x10000) ? (unsigned short)SectorCount : 0;
    BootSector.Media = 0xf8;
    BootSector.FATSectors = 0;  /* Set later. See below. */
    BootSector.SectorsPerTrack = DiskGeometry->SectorsPerTrack;
    BootSector.Heads = DiskGeometry->TracksPerCylinder;
    BootSector.HiddenSectors = PartitionInfo->HiddenSectors;
    BootSector.SectorsHuge = (SectorCount >= 0x10000) ? (unsigned long)SectorCount : 0;
    BootSector.Drive = DiskGeometry->MediaType == FixedMedia ? 0x80 : 0x00;
    BootSector.ExtBootSignature = 0x29;
    BootSector.VolumeID = CalcVolumeSerialNumber();
    if ((Label == NULL) || (Label->Buffer == NULL))
    {
        memcpy(&BootSector.VolumeLabel[0], "NO NAME    ", 11);
    }
    else
    {
        RtlUnicodeStringToOemString(&VolumeLabel, Label, TRUE);
        memset(&BootSector.VolumeLabel[0], ' ', 11);
        memcpy(&BootSector.VolumeLabel[0], VolumeLabel.Buffer,
               VolumeLabel.Length < 11 ? VolumeLabel.Length : 11);
        RtlFreeOemString(&VolumeLabel);
    }

    memcpy(&BootSector.SysType[0], "FAT12   ", 8);

    RootDirSectors = ((BootSector.RootEntries * 32) +
        (BootSector.BytesPerSector - 1)) / BootSector.BytesPerSector;

    /* Calculate number of FAT sectors */
    /* ((BootSector.BytesPerSector * 2) / 3) FAT entries (12bit) fit into one sector */
    TmpVal1 = SectorCount - (BootSector.ReservedSectors + RootDirSectors);
    TmpVal2 = (((BootSector.BytesPerSector * 2) / 3) * BootSector.SectorsPerCluster) + BootSector.FATCount;
    TmpVal3 = (TmpVal1 + (TmpVal2 - 1)) / TmpVal2;
    BootSector.FATSectors = (unsigned short)(TmpVal3 & 0xffff);

    DPRINT("BootSector.FATSectors = %hx\n", BootSector.FATSectors);

    /* Init context data */
    Context->TotalSectorCount =
        1 + (BootSector.FATSectors * 2) + RootDirSectors;

    Status = Fat12WriteBootSector(FileHandle,
                                  &BootSector,
                                  Context);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("Fat12WriteBootSector() failed with status 0x%.08x\n", Status);
        return Status;
    }

    /* Write first FAT copy */
    Status = Fat12WriteFAT(FileHandle,
                           0,
                           &BootSector,
                           Context);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("Fat12WriteFAT() failed with status 0x%.08x\n", Status);
        return Status;
    }

    /* Write second FAT copy */
    Status = Fat12WriteFAT(FileHandle,
                           (ULONG)BootSector.FATSectors,
                           &BootSector,
                           Context);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("Fat12WriteFAT() failed with status 0x%.08x.\n", Status);
        return Status;
    }

    Status = Fat12WriteRootDirectory(FileHandle,
                                     &BootSector,
                                     Context);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("Fat12WriteRootDirectory() failed with status 0x%.08x\n", Status);
    }

    if (!QuickFormat)
    {
        /* FIXME: Fill remaining sectors */
    }

    return Status;
}