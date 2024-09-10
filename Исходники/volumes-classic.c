void ShowVolume(char* VolumeName, int flgShowDevName, int flgVerbose, int flgUnit, int flgGauge, int flgRemoveable, uint64_t* AllTotalSize, uint64_t* AllFreeSize) {
    DWORD  Error                = ERROR_SUCCESS;
    DWORD  CharCount            = 0;
    char   tmp[MAX_PATH]        = "";
    char   DeviceName[MAX_PATH] = "";
    char*  VolumeTypeName       = 0;
    UINT   VolumeType           = 0;
    size_t Index                = 0;
    DWORD  SectorsPerCluster    = 0;
    DWORD  BytesPerSector       = 0;
    DWORD  NumberOfFreeClusters = 0;
    DWORD  TotalNumberOfClusters= 0;
    uint64_t TotalSize          = 0;
    uint64_t FreeSize           = 0;

    UINT   flgIsRealFloppy      = 0;

    double den                  = 0.0f;
    double percent              = 0.0f;

    strcpy(tmp, VolumeName);

    VolumeType = GetDriveTypeA(tmp);
    switch(VolumeType) {
        case 0:
            VolumeTypeName = "(Unknown)";
            break;
        case 1:
            VolumeTypeName = "(invalid root path)";
            break;
        case 2:
            VolumeTypeName = "(Removable)";
            break;
        case 3:
            VolumeTypeName = "(Fixed)";
            break;
        case 4:
            VolumeTypeName = "(Remote)";
            break;
        case 5:
            VolumeTypeName = "(CD-ROM)";
            break;
        case 6:
            VolumeTypeName = "(RAM Disk)";
            break;
    }

    if(!flgVerbose && !IsTargetDrive(VolumeType,7,0)) return;
    // get free space information
    if(IsTargetDrive(VolumeType,flgRemoveable,flgIsRealFloppy)) {
        GetDiskFreeSpaceA(tmp, &SectorsPerCluster, &BytesPerSector, &NumberOfFreeClusters, &TotalNumberOfClusters);
        FreeSize = TotalSize = SectorsPerCluster;
        FreeSize *= BytesPerSector;
        TotalSize *= BytesPerSector;
        FreeSize *= NumberOfFreeClusters;
        TotalSize *= TotalNumberOfClusters;

        if(VolumeType == 3) {
            *AllTotalSize += TotalSize;
            *AllFreeSize += FreeSize;
        }

        den = TotalSize;
        percent = FreeSize;
        percent /= den;
        percent *= 100;
    }

    if(flgVerbose) {
        printf("\nFound a device: %s", DeviceName);
        printf("\nVolume name: %s %s", tmp, VolumeTypeName);
        printf("\nPaths:");
    }
    else if(flgGauge) {
        DrawGauge(36,(int)percent,!IsTargetDrive(VolumeType,flgRemoveable,flgIsRealFloppy)|!TotalSize);
    }

    if (!flgShowDevName)
        printf("  %s", tmp);


    if(IsTargetDrive(VolumeType,flgRemoveable,flgIsRealFloppy)) {
        // VolumeName is reused here
        strcpy(tmp, ComputerUnits(FreeSize, flgUnit));

        // DeviceName is reused here
        if(TotalSize)
            sprintf(DeviceName, "%.2f", percent);
        else
            strcpy(DeviceName, "--");

        printf(" (%s / %s) %s%%", tmp, ComputerUnits(TotalSize, flgUnit), DeviceName);
    }
    if(!flgVerbose) {
        if(VolumeType != 3) printf(" %s", VolumeTypeName);
    }
    printf("\n");
}