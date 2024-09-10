/******************************************************************
 *		create_scsi_entry
 *
 * Initializes registry to contain scsi info about the cdrom in NT.
 * All devices (even not real scsi ones) have this info in NT.
 * NOTE: programs usually read these registry entries after sending the
 *       IOCTL_SCSI_GET_ADDRESS ioctl to the cdrom
 */
static void create_scsi_entry( PSCSI_ADDRESS scsi_addr, LPCSTR lpDriver, UINT uDriveType,
    LPSTR lpDriveName, LPSTR lpUnixDeviceName )
{
    static UCHAR uCdromNumber = 0;
    static UCHAR uTapeNumber = 0;

    OBJECT_ATTRIBUTES attr;
    UNICODE_STRING nameW;
    WCHAR dataW[50];
    DWORD lenW;
    char buffer[40];
    DWORD value;
    const char *data;
    HANDLE scsiKey;
    HANDLE portKey;
    HANDLE busKey;
    HANDLE targetKey;
    HANDLE lunKey;
    DWORD disp;

    attr.Length = sizeof(attr);
    attr.RootDirectory = 0;
    attr.ObjectName = &nameW;
    attr.Attributes = 0;
    attr.SecurityDescriptor = NULL;
    attr.SecurityQualityOfService = NULL;

    /* Ensure there is Scsi key */
    if (!RtlCreateUnicodeStringFromAsciiz( &nameW, "Machine\\HARDWARE\\DEVICEMAP\\Scsi" ) ||
        NtCreateKey( &scsiKey, KEY_ALL_ACCESS, &attr, 0,
                     NULL, REG_OPTION_VOLATILE, &disp ))
    {
        ERR("Cannot create DEVICEMAP\\Scsi registry key\n" );
        return;
    }
    RtlFreeUnicodeString( &nameW );

    snprintf(buffer,sizeof(buffer),"Scsi Port %d",scsi_addr->PortNumber);
    attr.RootDirectory = scsiKey;
    if (!RtlCreateUnicodeStringFromAsciiz( &nameW, buffer ) ||
        NtCreateKey( &portKey, KEY_ALL_ACCESS, &attr, 0,
                     NULL, REG_OPTION_VOLATILE, &disp ))
    {
        ERR("Cannot create DEVICEMAP\\Scsi Port registry key\n" );
        return;
    }
    RtlFreeUnicodeString( &nameW );

    RtlCreateUnicodeStringFromAsciiz( &nameW, "Driver" );
    RtlMultiByteToUnicodeN( dataW, sizeof(dataW), &lenW, lpDriver, strlen(lpDriver));
    NtSetValueKey( portKey, &nameW, 0, REG_SZ, (BYTE*)dataW, lenW );
    RtlFreeUnicodeString( &nameW );
    value = 10;
    RtlCreateUnicodeStringFromAsciiz( &nameW, "FirstBusTimeScanInMs" );
    NtSetValueKey( portKey,&nameW, 0, REG_DWORD, (BYTE *)&value, sizeof(DWORD));
    RtlFreeUnicodeString( &nameW );

    value = 0;
    if (strcmp(lpDriver, "atapi") == 0)
    {
#ifdef HDIO_GET_DMA
        int fd, dma;
        
        fd = open(lpUnixDeviceName, O_RDONLY|O_NONBLOCK);
        if (fd != -1)
        {
            if (ioctl(fd, HDIO_GET_DMA, &dma) != -1) value = dma;
            close(fd);
        }
#endif
        RtlCreateUnicodeStringFromAsciiz( &nameW, "DMAEnabled" );
        NtSetValueKey( portKey,&nameW, 0, REG_DWORD, (BYTE *)&value, sizeof(DWORD));
        RtlFreeUnicodeString( &nameW );
    }

    snprintf(buffer, sizeof(buffer),"Scsi Bus %d", scsi_addr->PathId);
    attr.RootDirectory = portKey;
    if (!RtlCreateUnicodeStringFromAsciiz( &nameW, buffer ) ||
        NtCreateKey( &busKey, KEY_ALL_ACCESS, &attr, 0,
                     NULL, REG_OPTION_VOLATILE, &disp ))
    {
        ERR("Cannot create DEVICEMAP\\Scsi Port\\Scsi Bus registry key\n" );
        return;
    }
    RtlFreeUnicodeString( &nameW );

    attr.RootDirectory = busKey;
    /* FIXME: get real controller Id for SCSI */
    if (!RtlCreateUnicodeStringFromAsciiz( &nameW, "Initiator Id 255" ) ||
        NtCreateKey( &targetKey, KEY_ALL_ACCESS, &attr, 0,
                     NULL, REG_OPTION_VOLATILE, &disp ))
    {
        ERR("Cannot create DEVICEMAP\\Scsi Port\\Scsi Bus\\Initiator Id 255 registry key\n" );
        return;
    }
    RtlFreeUnicodeString( &nameW );
    NtClose( targetKey );

    snprintf(buffer, sizeof(buffer),"Target Id %d", scsi_addr->TargetId);
    attr.RootDirectory = busKey;
    if (!RtlCreateUnicodeStringFromAsciiz( &nameW, buffer ) ||
        NtCreateKey( &targetKey, KEY_ALL_ACCESS, &attr, 0,
                     NULL, REG_OPTION_VOLATILE, &disp ))
    {
        ERR("Cannot create DEVICEMAP\\Scsi Port\\Scsi Bus 0\\Target Id registry key\n" );
        return;
    }
    RtlFreeUnicodeString( &nameW );

    snprintf(buffer, sizeof(buffer),"Logical Unit Id %d", scsi_addr->Lun);
    attr.RootDirectory = targetKey;
    if (!RtlCreateUnicodeStringFromAsciiz( &nameW, buffer ) ||
        NtCreateKey( &lunKey, KEY_ALL_ACCESS, &attr, 0,
                     NULL, REG_OPTION_VOLATILE, &disp ))
    {
        ERR("Cannot create DEVICEMAP\\Scsi Port\\Scsi Bus 0\\Target Id registry key\\Logical Unit Id\n" );
        return;
    }
    RtlFreeUnicodeString( &nameW );

    switch (uDriveType)
    {
        case DRIVE_NO_ROOT_DIR:
        default:
            data = "OtherPeripheral"; break;
        case DRIVE_FIXED:
            data = "DiskPeripheral"; break;
        case DRIVE_REMOVABLE:
            data = "TapePeripheral";
            snprintf(buffer, sizeof(buffer), "Tape%d", uTapeNumber++);
            break;
        case DRIVE_CDROM:
            data = "CdRomPeripheral";
            snprintf(buffer, sizeof(buffer), "Cdrom%d", uCdromNumber++);
            break;
    }
    RtlCreateUnicodeStringFromAsciiz( &nameW, "Type" );
    RtlMultiByteToUnicodeN( dataW, sizeof(dataW), &lenW, data, strlen(data));
    NtSetValueKey( lunKey, &nameW, 0, REG_SZ, (BYTE*)dataW, lenW );
    RtlFreeUnicodeString( &nameW );

    RtlCreateUnicodeStringFromAsciiz( &nameW, "Identifier" );
    RtlMultiByteToUnicodeN( dataW, sizeof(dataW), &lenW, lpDriveName, strlen(lpDriveName));
    NtSetValueKey( lunKey, &nameW, 0, REG_SZ, (BYTE*)dataW, lenW );
    RtlFreeUnicodeString( &nameW );

    if (uDriveType == DRIVE_CDROM || uDriveType == DRIVE_REMOVABLE)
    {
        RtlCreateUnicodeStringFromAsciiz( &nameW, "DeviceName" );
        RtlMultiByteToUnicodeN( dataW, sizeof(dataW), &lenW, buffer, strlen(buffer));
        NtSetValueKey( lunKey, &nameW, 0, REG_SZ, (BYTE*)dataW, lenW );
        RtlFreeUnicodeString( &nameW );
    }

    RtlCreateUnicodeStringFromAsciiz( &nameW, "UnixDeviceName" );
    RtlMultiByteToUnicodeN( dataW, sizeof(dataW), &lenW, lpUnixDeviceName, strlen(lpUnixDeviceName));
    NtSetValueKey( lunKey, &nameW, 0, REG_SZ, (BYTE*)dataW, lenW );
    RtlFreeUnicodeString( &nameW );

    NtClose( lunKey );
    NtClose( targetKey );
    NtClose( busKey );
    NtClose( portKey );
    NtClose( scsiKey );
}