NTSTATUS
Fat32Format(IN HANDLE FileHandle,
            IN PPARTITION_INFORMATION PartitionInfo,
            IN PDISK_GEOMETRY DiskGeometry,
            IN PUNICODE_STRING Label,
            IN BOOLEAN QuickFormat,
            IN ULONG ClusterSize,
            IN OUT PFORMAT_CONTEXT Context)
{
    FAT32_BOOT_SECTOR BootSector;
    OEM_STRING VolumeLabel;
    ULONG TmpVal1;
    ULONG TmpVal2;
    NTSTATUS Status;

    /* Calculate cluster size */
    if (ClusterSize == 0)
    {
        if (PartitionInfo->PartitionLength.QuadPart < 8LL * 1024LL * 1024LL * 1024LL)
        {
            /* Partition < 8GB ==> 4KB Cluster */
            ClusterSize = 4096;
        }
        else if (PartitionInfo->PartitionLength.QuadPart < 16LL * 1024LL * 1024LL * 1024LL)
        {
            /* Partition 8GB - 16GB ==> 8KB Cluster */
            ClusterSize = 8192;
        }
        else if (PartitionInfo->PartitionLength.QuadPart < 32LL * 1024LL * 1024LL * 1024LL)
        {
            /* Partition 16GB - 32GB ==> 16KB Cluster */
            ClusterSize = 16384;
        }
        else
        {
            /* Partition >= 32GB ==> 32KB Cluster */
            ClusterSize = 32768;
        }
    }

    memset(&BootSector, 0, sizeof(FAT32_BOOT_SECTOR));
    memcpy(&BootSector.OEMName[0], "MSWIN4.1", 8);
    BootSector.BytesPerSector = DiskGeometry->BytesPerSector;
    BootSector.SectorsPerCluster = ClusterSize / BootSector.BytesPerSector;
    BootSector.ReservedSectors = 32;
    BootSector.FATCount = 2;
    BootSector.RootEntries = 0;
    BootSector.Sectors = 0;
    BootSector.Media = 0xf8;
    BootSector.FATSectors = 0;
    BootSector.SectorsPerTrack = DiskGeometry->SectorsPerTrack;
    BootSector.Heads = DiskGeometry->TracksPerCylinder;
    BootSector.HiddenSectors = PartitionInfo->HiddenSectors;
    BootSector.SectorsHuge = PartitionInfo->PartitionLength.QuadPart >>
        GetShiftCount(BootSector.BytesPerSector); /* Use shifting to avoid 64-bit division */
    BootSector.FATSectors32 = 0; /* Set later */
    BootSector.ExtFlag = 0; /* Mirror all FATs */
    BootSector.FSVersion = 0x0000; /* 0:0 */
    BootSector.RootCluster = 2;
    BootSector.FSInfoSector = 1;
    BootSector.BootBackup = 6;
    BootSector.Drive = (DiskGeometry->MediaType == FixedMedia) ? 0x80 : 0x00;
    BootSector.ExtBootSignature = 0x29;
    BootSector.VolumeID = CalcVolumeSerialNumber ();
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

    memcpy(&BootSector.SysType[0], "FAT32   ", 8);

    /* Calculate number of FAT sectors */
    /* (BytesPerSector / 4) FAT entries (32bit) fit into one sector */
    TmpVal1 = BootSector.SectorsHuge - BootSector.ReservedSectors;
    TmpVal2 = ((BootSector.BytesPerSector / 4) * BootSector.SectorsPerCluster) + BootSector.FATCount;
    BootSector.FATSectors32 = (TmpVal1 + (TmpVal2 - 1)) / TmpVal2;
    DPRINT("FATSectors32 = %lu\n", BootSector.FATSectors32);

    /* Init context data */
    Context->TotalSectorCount =
        2 + (BootSector.FATSectors32 * BootSector.FATCount) + BootSector.SectorsPerCluster;

    if (!QuickFormat)
    {
        Context->TotalSectorCount += BootSector.SectorsHuge;

        Status = Fat32WipeSectors(FileHandle,
                                  &BootSector,
                                  Context);
        if (!NT_SUCCESS(Status))
        {
            DPRINT("Fat32WipeSectors() failed with status 0x%.08x\n", Status);
            return Status;
        }
    }

    Status = Fat32WriteBootSector(FileHandle,
                                  &BootSector,
                                  Context);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("Fat32WriteBootSector() failed with status 0x%.08x\n", Status);
        return Status;
    }

    Status = Fat32WriteFsInfo(FileHandle,
                              &BootSector,
                              Context);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("Fat32WriteFsInfo() failed with status 0x%.08x\n", Status);
        return Status;
    }

    /* Write first FAT copy */
    Status = Fat32WriteFAT(FileHandle,
                           0,
                           &BootSector,
                           Context);
    if (!NT_SUCCESS(Status))
    {
      DPRINT("Fat32WriteFAT() failed with status 0x%.08x\n", Status);
      return Status;
    }

    /* Write second FAT copy */
    Status = Fat32WriteFAT(FileHandle,
                           BootSector.FATSectors32,
                           &BootSector,
                           Context);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("Fat32WriteFAT() failed with status 0x%.08x.\n", Status);
        return Status;
    }

    Status = Fat32WriteRootDirectory(FileHandle,
                                     &BootSector,
                                     Context);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("Fat32WriteRootDirectory() failed with status 0x%.08x\n", Status);
    }

    return Status;
}