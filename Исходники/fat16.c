NTSTATUS
Fat16Format(IN HANDLE FileHandle,
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
        if (PartitionInfo->PartitionLength.QuadPart < 16LL * 1024LL * 1024LL)
        {
            /* Partition < 16MB ==> 1KB Cluster */
            ClusterSize = 1024;
        }
        else if (PartitionInfo->PartitionLength.QuadPart < 128LL * 1024LL * 1024LL)
        {
            /* Partition < 128MB ==> 2KB Cluster */
            ClusterSize = 2048;
        }
        else if (PartitionInfo->PartitionLength.QuadPart < 256LL * 1024LL * 1024LL)
        {
            /* Partition < 256MB ==> 4KB Cluster */
            ClusterSize = 4096;
        }
        else
        {
            /* Partition >= 256MB (< 512MB) ==> 8KB Cluster */
            ClusterSize = 8192;
        }
    }

    SectorCount = PartitionInfo->PartitionLength.QuadPart >>
        GetShiftCount(DiskGeometry->BytesPerSector); /* Use shifting to avoid 64-bit division */

    RtlZeroMemory(&BootSector, sizeof(FAT16_BOOT_SECTOR));
    memcpy(&BootSector.OEMName[0], "MSWIN4.1", 8);
    /* FIXME: Add dummy bootloader for real */
    BootSector.Jump[0] = 0xeb;
    BootSector.Jump[1] = 0x3c;
    BootSector.Jump[2] = 0x90;
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
    BootSector.Drive = (DiskGeometry->MediaType == FixedMedia) ? 0x80 : 0x00;
    BootSector.ExtBootSignature = 0x29;
    BootSector.VolumeID = CalcVolumeSerialNumber();
    if ((Label == NULL) || (Label->Buffer == NULL))
    {
        memcpy(&BootSector.VolumeLabel[0], "NO NAME    ", 11);
    }
    else
    {
        RtlUnicodeStringToOemString(&VolumeLabel, Label, TRUE);
        RtlFillMemory(&BootSector.VolumeLabel[0], 11, ' ');
        memcpy(&BootSector.VolumeLabel[0], VolumeLabel.Buffer,
               VolumeLabel.Length < 11 ? VolumeLabel.Length : 11);
        RtlFreeOemString(&VolumeLabel);
    }

    memcpy(&BootSector.SysType[0], "FAT16   ", 8);

    DPRINT("BootSector.SectorsHuge = %lx\n", BootSector.SectorsHuge);

    RootDirSectors = ((BootSector.RootEntries * 32) +
        (BootSector.BytesPerSector - 1)) / BootSector.BytesPerSector;

    /* Calculate number of FAT sectors */
    /* (BootSector.BytesPerSector / 2) FAT entries (16bit) fit into one sector */
    TmpVal1 = SectorCount - (BootSector.ReservedSectors + RootDirSectors);
    TmpVal2 = ((BootSector.BytesPerSector / 2) * BootSector.SectorsPerCluster) + BootSector.FATCount;
    TmpVal3 = (TmpVal1 + (TmpVal2 - 1)) / TmpVal2;
    BootSector.FATSectors = (unsigned short)(TmpVal3 & 0xffff);
    DPRINT("BootSector.FATSectors = %hu\n", BootSector.FATSectors);

    /* Init context data */
    Context->TotalSectorCount =
        1 + (BootSector.FATSectors * 2) + RootDirSectors;

    if (!QuickFormat)
    {
        Context->TotalSectorCount += SectorCount;

        Status = FatWipeSectors(FileHandle,
                                SectorCount,
                                (ULONG)BootSector.SectorsPerCluster,
                                (ULONG)BootSector.BytesPerSector,
                                Context);
        if (!NT_SUCCESS(Status))
        {
            DPRINT("FatWipeSectors() failed with status 0x%.08x\n", Status);
            return Status;
        }
    }

    Status = Fat16WriteBootSector(FileHandle,
                                  &BootSector,
                                  Context);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("Fat16WriteBootSector() failed with status 0x%.08x\n", Status);
        return Status;
    }

    /* Write first FAT copy */
    Status = Fat16WriteFAT(FileHandle,
                           0,
                           &BootSector,
                           Context);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("Fat16WriteFAT() failed with status 0x%.08x\n", Status);
        return Status;
    }

    /* Write second FAT copy */
    Status = Fat16WriteFAT(FileHandle,
                           (ULONG)BootSector.FATSectors,
                           &BootSector,
                           Context);
    if (!NT_SUCCESS(Status))
    {
       DPRINT("Fat16WriteFAT() failed with status 0x%.08x.\n", Status);
        return Status;
    }

    Status = Fat16WriteRootDirectory(FileHandle,
                                     &BootSector,
                                     Context);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("Fat16WriteRootDirectory() failed with status 0x%.08x\n", Status);
    }

    return Status;
}