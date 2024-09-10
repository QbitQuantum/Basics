VOID
__cdecl
main(
    _In_ int argc,
    _In_z_ char *argv[]
    )

{
    BOOL status = 0;
    DWORD accessMode = 0, shareMode = 0;
    HANDLE fileHandle = NULL;
    ULONG alignmentMask = 0; // default == no alignment requirement
    UCHAR srbType = 0; // default == SRB_TYPE_SCSI_REQUEST_BLOCK
    PUCHAR dataBuffer = NULL;
    PUCHAR pUnAlignedBuffer = NULL;
    SCSI_PASS_THROUGH_WITH_BUFFERS sptwb;
    SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER sptdwb;
    SCSI_PASS_THROUGH_WITH_BUFFERS_EX sptwb_ex;
    SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER_EX sptdwb_ex;
    CHAR string[NAME_COUNT];

    ULONG length = 0,
          errorCode = 0,
          returned = 0,
          sectorSize = 512;

    if ((argc < 2) || (argc > 3)) {
       printf("Usage:  %s <port-name> [-mode]\n", argv[0] );
       printf("Examples:\n");
       printf("    spti g:       (open the disk class driver in SHARED READ/WRITE mode)\n");
       printf("    spti Scsi2:   (open the miniport driver for the 3rd host adapter)\n");
       printf("    spti Tape0 w  (open the tape class driver in SHARED WRITE mode)\n");
       printf("    spti i: c     (open the CD-ROM class driver in SHARED READ mode)\n");
       return;
    }

    StringCbPrintf(string, sizeof(string), "\\\\.\\%s", argv[1]);

    shareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;  // default
    accessMode = GENERIC_WRITE | GENERIC_READ;       // default

    if (argc == 3) {

        switch(tolower(argv[2][0])) {
            case 'r':
                shareMode = FILE_SHARE_READ;
                break;

            case 'w':
                shareMode = FILE_SHARE_WRITE;
                break;

            case 'c':
                shareMode = FILE_SHARE_READ;
                sectorSize = 2048;
                break;

            default:
                printf("%s is an invalid mode.\n", argv[2]);
                puts("\tr = read");
                puts("\tw = write");
                puts("\tc = read CD (2048 byte sector mode)");
                return;
        }
    }

    fileHandle = CreateFile(string,
       accessMode,
       shareMode,
       NULL,
       OPEN_EXISTING,
       0,
       NULL);

    if (fileHandle == INVALID_HANDLE_VALUE) {
        errorCode = GetLastError();
        printf("Error opening %s. Error: %d\n",
               string, errorCode);
        PrintError(errorCode);
        return;
    }

    //
    // Get the alignment requirements
    //

    status = QueryPropertyForDevice(fileHandle, &alignmentMask, &srbType);
    if (!status ) {
        errorCode = GetLastError();
        printf("Error getting device and/or adapter properties; "
               "error was %d\n", errorCode);
        PrintError(errorCode);
        CloseHandle(fileHandle);
        return;
    }

    printf("\n"
           "            *****     Detected Alignment Mask    *****\n"
           "            *****             was %08x       *****\n\n\n",
           alignmentMask);

    //
    // Send SCSI Pass Through
    //

    puts("            ***** MODE SENSE -- return all pages *****");
    puts("            *****      with SenseInfo buffer     *****\n");

    if(srbType == 1)
    {
        ZeroMemory(&sptwb_ex,sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX));
        sptwb_ex.spt.Version = 0;
        sptwb_ex.spt.Length = sizeof(SCSI_PASS_THROUGH_EX);
        sptwb_ex.spt.ScsiStatus = 0;
        sptwb_ex.spt.CdbLength = CDB6GENERIC_LENGTH;
        sptwb_ex.spt.StorAddressLength = sizeof(STOR_ADDR_BTL8);
        sptwb_ex.spt.SenseInfoLength = SPT_SENSE_LENGTH;
        sptwb_ex.spt.DataOutTransferLength = 0;
        sptwb_ex.spt.DataInTransferLength = 192;
        sptwb_ex.spt.DataDirection = SCSI_IOCTL_DATA_IN;
        sptwb_ex.spt.TimeOutValue = 2;
        sptwb_ex.spt.StorAddressOffset =
            offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,StorAddress);
        sptwb_ex.StorAddress.Type = STOR_ADDRESS_TYPE_BTL8;
        sptwb_ex.StorAddress.Port = 0;
        sptwb_ex.StorAddress.AddressLength = STOR_ADDR_BTL8_ADDRESS_LENGTH;
        sptwb_ex.StorAddress.Path = 0;
        sptwb_ex.StorAddress.Target = 1;
        sptwb_ex.StorAddress.Lun = 0;
        sptwb_ex.spt.SenseInfoOffset =
           offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,ucSenseBuf);
        sptwb_ex.spt.DataOutBufferOffset = 0;
        sptwb_ex.spt.DataInBufferOffset =
           offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,ucDataBuf);
        sptwb_ex.spt.Cdb[0] = SCSIOP_MODE_SENSE;
        sptwb_ex.spt.Cdb[2] = MODE_SENSE_RETURN_ALL;
        sptwb_ex.spt.Cdb[4] = 192;
        length = offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,ucDataBuf) +
           sptwb_ex.spt.DataInTransferLength;

        status = DeviceIoControl(fileHandle,
                                 IOCTL_SCSI_PASS_THROUGH_EX,
                                 &sptwb_ex,
                                 sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX),
                                 &sptwb_ex,
                                 length,
                                 &returned,
                                 FALSE);

        PrintStatusResultsEx(status,returned,&sptwb_ex,length);
    }
    else
    {
        ZeroMemory(&sptwb,sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS));
        sptwb.spt.Length = sizeof(SCSI_PASS_THROUGH);
        sptwb.spt.PathId = 0;
        sptwb.spt.TargetId = 1;
        sptwb.spt.Lun = 0;
        sptwb.spt.CdbLength = CDB6GENERIC_LENGTH;
        sptwb.spt.SenseInfoLength = SPT_SENSE_LENGTH;
        sptwb.spt.DataIn = SCSI_IOCTL_DATA_IN;
        sptwb.spt.DataTransferLength = 192;
        sptwb.spt.TimeOutValue = 2;
        sptwb.spt.DataBufferOffset =
           offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS,ucDataBuf);
        sptwb.spt.SenseInfoOffset =
           offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS,ucSenseBuf);
        sptwb.spt.Cdb[0] = SCSIOP_MODE_SENSE;
        sptwb.spt.Cdb[2] = MODE_SENSE_RETURN_ALL;
        sptwb.spt.Cdb[4] = 192;
        length = offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS,ucDataBuf) +
           sptwb.spt.DataTransferLength;

        status = DeviceIoControl(fileHandle,
                                 IOCTL_SCSI_PASS_THROUGH,
                                 &sptwb,
                                 sizeof(SCSI_PASS_THROUGH),
                                 &sptwb,
                                 length,
                                 &returned,
                                 FALSE);

        PrintStatusResults(status,returned,&sptwb,length);
    }


    printf("            ***** MODE SENSE -- return all pages *****\n");
    printf("            *****    without SenseInfo buffer    *****\n\n");

    if(srbType == 1)
    {
        ZeroMemory(&sptwb_ex,sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX));
        sptwb_ex.spt.Version = 0;
        sptwb_ex.spt.Length = sizeof(SCSI_PASS_THROUGH_EX);
        sptwb_ex.spt.ScsiStatus = 0;
        sptwb_ex.spt.CdbLength = CDB6GENERIC_LENGTH;
        sptwb_ex.spt.StorAddressLength = sizeof(STOR_ADDR_BTL8);
        sptwb_ex.spt.SenseInfoLength = 0;
        sptwb_ex.spt.DataOutTransferLength = 0;
        sptwb_ex.spt.DataInTransferLength = 192;
        sptwb_ex.spt.DataDirection = SCSI_IOCTL_DATA_IN;
        sptwb_ex.spt.TimeOutValue = 2;
        sptwb_ex.spt.StorAddressOffset =
            offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,StorAddress);
        sptwb_ex.StorAddress.Type = STOR_ADDRESS_TYPE_BTL8;
        sptwb_ex.StorAddress.Port = 0;
        sptwb_ex.StorAddress.AddressLength = STOR_ADDR_BTL8_ADDRESS_LENGTH;
        sptwb_ex.StorAddress.Path = 0;
        sptwb_ex.StorAddress.Target = 1;
        sptwb_ex.StorAddress.Lun = 0;
        sptwb_ex.spt.SenseInfoOffset = 0;
        sptwb_ex.spt.DataOutBufferOffset = 0;
        sptwb_ex.spt.DataInBufferOffset =
           offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,ucDataBuf);
        sptwb_ex.spt.Cdb[0] = SCSIOP_MODE_SENSE;
        sptwb_ex.spt.Cdb[2] = MODE_SENSE_RETURN_ALL;
        sptwb_ex.spt.Cdb[4] = 192;
        length = offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,ucDataBuf) +
           sptwb_ex.spt.DataInTransferLength;

        status = DeviceIoControl(fileHandle,
                                 IOCTL_SCSI_PASS_THROUGH_EX,
                                 &sptwb_ex,
                                 sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX),
                                 &sptwb_ex,
                                 length,
                                 &returned,
                                 FALSE);

        PrintStatusResultsEx(status,returned,&sptwb_ex,length);
    }
    else
    {
        ZeroMemory(&sptwb,sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS));
        sptwb.spt.Length = sizeof(SCSI_PASS_THROUGH);
        sptwb.spt.PathId = 0;
        sptwb.spt.TargetId = 1;
        sptwb.spt.Lun = 0;
        sptwb.spt.CdbLength = CDB6GENERIC_LENGTH;
        sptwb.spt.SenseInfoLength = 0;
        sptwb.spt.DataIn = SCSI_IOCTL_DATA_IN;
        sptwb.spt.DataTransferLength = 192;
        sptwb.spt.TimeOutValue = 2;
        sptwb.spt.DataBufferOffset =
           offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS,ucDataBuf);
        sptwb.spt.Cdb[0] = SCSIOP_MODE_SENSE;
        sptwb.spt.Cdb[2] = MODE_SENSE_RETURN_ALL;
        sptwb.spt.Cdb[4] = 192;
        length = offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS,ucDataBuf) +
           sptwb.spt.DataTransferLength;

        status = DeviceIoControl(fileHandle,
                                 IOCTL_SCSI_PASS_THROUGH,
                                 &sptwb,
                                 sizeof(SCSI_PASS_THROUGH),
                                 &sptwb,
                                 length,
                                 &returned,
                                 FALSE);

        PrintStatusResults(status,returned,&sptwb,length);
    }


    printf("            *****      TEST UNIT READY      *****\n");
    printf("            *****   DataInBufferLength = 0  *****\n\n");

    if(srbType == 1)
    {
        ZeroMemory(&sptwb_ex,sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX));
        sptwb_ex.spt.Version = 0;
        sptwb_ex.spt.Length = sizeof(SCSI_PASS_THROUGH_EX);
        sptwb_ex.spt.ScsiStatus = 0;
        sptwb_ex.spt.CdbLength = CDB6GENERIC_LENGTH;
        sptwb_ex.spt.StorAddressLength = sizeof(STOR_ADDR_BTL8);
        sptwb_ex.spt.SenseInfoLength = SPT_SENSE_LENGTH;
        sptwb_ex.spt.DataOutTransferLength = 0;
        sptwb_ex.spt.DataInTransferLength = 0;
        sptwb_ex.spt.DataDirection = SCSI_IOCTL_DATA_IN;
        sptwb_ex.spt.TimeOutValue = 2;
        sptwb_ex.spt.StorAddressOffset =
            offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,StorAddress);
        sptwb_ex.StorAddress.Type = STOR_ADDRESS_TYPE_BTL8;
        sptwb_ex.StorAddress.Port = 0;
        sptwb_ex.StorAddress.AddressLength = STOR_ADDR_BTL8_ADDRESS_LENGTH;
        sptwb_ex.StorAddress.Path = 0;
        sptwb_ex.StorAddress.Target = 1;
        sptwb_ex.StorAddress.Lun = 0;
        sptwb_ex.spt.SenseInfoOffset =
           offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,ucSenseBuf);
        sptwb_ex.spt.DataOutBufferOffset = 0;
        sptwb_ex.spt.DataInBufferOffset = 0;
        sptwb_ex.spt.Cdb[0] = SCSIOP_TEST_UNIT_READY;
        length = offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,ucDataBuf);

        status = DeviceIoControl(fileHandle,
                                 IOCTL_SCSI_PASS_THROUGH_EX,
                                 &sptwb_ex,
                                 sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX),
                                 &sptwb_ex,
                                 length,
                                 &returned,
                                 FALSE);

        PrintStatusResultsEx(status,returned,&sptwb_ex,length);
    }
    else
    {
        ZeroMemory(&sptwb,sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS));
        sptwb.spt.Length = sizeof(SCSI_PASS_THROUGH);
        sptwb.spt.PathId = 0;
        sptwb.spt.TargetId = 1;
        sptwb.spt.Lun = 0;
        sptwb.spt.CdbLength = CDB6GENERIC_LENGTH;
        sptwb.spt.SenseInfoLength = SPT_SENSE_LENGTH;
        sptwb.spt.DataIn = SCSI_IOCTL_DATA_IN;
        sptwb.spt.DataTransferLength = 0;
        sptwb.spt.TimeOutValue = 2;
        sptwb.spt.DataBufferOffset = 0;
        sptwb.spt.SenseInfoOffset =
           offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS,ucSenseBuf);
        sptwb.spt.Cdb[0] = SCSIOP_TEST_UNIT_READY;
        length = offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS,ucDataBuf);

        status = DeviceIoControl(fileHandle,
                                 IOCTL_SCSI_PASS_THROUGH,
                                 &sptwb,
                                 sizeof(SCSI_PASS_THROUGH),
                                 &sptwb,
                                 length,
                                 &returned,
                                 FALSE);

        PrintStatusResults(status,returned,&sptwb,length);
    }


    //
    //  Do a mode sense with a bad data buffer offset.  This will fail.
    //
    printf("            *****      MODE SENSE -- return all pages      *****\n");
    printf("            *****   bad DataBufferOffset -- should fail    *****\n\n");

    if(srbType == 1)
    {
        ZeroMemory(&sptwb_ex,sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX));
        sptwb_ex.spt.Version = 0;
        sptwb_ex.spt.Length = sizeof(SCSI_PASS_THROUGH_EX);
        sptwb_ex.spt.ScsiStatus = 0;
        sptwb_ex.spt.CdbLength = CDB6GENERIC_LENGTH;
        sptwb_ex.spt.StorAddressLength = sizeof(STOR_ADDR_BTL8);
        sptwb_ex.spt.SenseInfoLength = SPT_SENSE_LENGTH;
        sptwb_ex.spt.DataOutTransferLength = 0;
        sptwb_ex.spt.DataInTransferLength = 192;
        sptwb_ex.spt.DataDirection = SCSI_IOCTL_DATA_IN;
        sptwb_ex.spt.TimeOutValue = 2;
        sptwb_ex.spt.StorAddressOffset =
            offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,StorAddress);
        sptwb_ex.StorAddress.Type = STOR_ADDRESS_TYPE_BTL8;
        sptwb_ex.StorAddress.Port = 0;
        sptwb_ex.StorAddress.AddressLength = STOR_ADDR_BTL8_ADDRESS_LENGTH;
        sptwb_ex.StorAddress.Path = 0;
        sptwb_ex.StorAddress.Target = 1;
        sptwb_ex.StorAddress.Lun = 0;
        sptwb_ex.spt.SenseInfoOffset =
           offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,ucSenseBuf);
        sptwb_ex.spt.DataOutBufferOffset = 0;
        sptwb_ex.spt.DataInBufferOffset = 0;
        sptwb_ex.spt.Cdb[0] = SCSIOP_MODE_SENSE;
        sptwb_ex.spt.Cdb[2] = MODE_SENSE_RETURN_ALL;
        sptwb_ex.spt.Cdb[4] = 192;
        length = offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,ucDataBuf) +
           sptwb_ex.spt.DataInTransferLength;

        status = DeviceIoControl(fileHandle,
                                 IOCTL_SCSI_PASS_THROUGH_EX,
                                 &sptwb_ex,
                                 sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX),
                                 &sptwb_ex,
                                 length,
                                 &returned,
                                 FALSE);

        PrintStatusResultsEx(status,returned,&sptwb_ex,length);
    }
    else
    {
        ZeroMemory(&sptwb,sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS));
        sptwb.spt.Length = sizeof(SCSI_PASS_THROUGH);
        sptwb.spt.PathId = 0;
        sptwb.spt.TargetId = 1;
        sptwb.spt.Lun = 0;
        sptwb.spt.CdbLength = CDB6GENERIC_LENGTH;
        sptwb.spt.SenseInfoLength = 0;
        sptwb.spt.DataIn = SCSI_IOCTL_DATA_IN;
        sptwb.spt.DataTransferLength = 192;
        sptwb.spt.TimeOutValue = 2;
        sptwb.spt.DataBufferOffset = 0;
        sptwb.spt.SenseInfoOffset =
           offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS,ucSenseBuf);
        sptwb.spt.Cdb[0] = SCSIOP_MODE_SENSE;
        sptwb.spt.Cdb[2] = MODE_SENSE_RETURN_ALL;
        sptwb.spt.Cdb[4] = 192;
        length = offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS,ucDataBuf) +
           sptwb.spt.DataTransferLength;

        status = DeviceIoControl(fileHandle,
                                 IOCTL_SCSI_PASS_THROUGH,
                                 &sptwb,
                                 sizeof(SCSI_PASS_THROUGH),
                                 &sptwb,
                                 length,
                                 &returned,
                                 FALSE);

        PrintStatusResults(status,returned,&sptwb,length);
    }


    //
    // Get caching mode sense page.
    //
    printf("            *****               MODE SENSE                  *****\n");
    printf("            *****     return caching mode sense page        *****\n\n");

    if(srbType == 1)
    {
        ZeroMemory(&sptwb_ex,sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX));
        sptwb_ex.spt.Version = 0;
        sptwb_ex.spt.Length = sizeof(SCSI_PASS_THROUGH_EX);
        sptwb_ex.spt.ScsiStatus = 0;
        sptwb_ex.spt.CdbLength = CDB6GENERIC_LENGTH;
        sptwb_ex.spt.StorAddressLength = sizeof(STOR_ADDR_BTL8);
        sptwb_ex.spt.SenseInfoLength = SPT_SENSE_LENGTH;
        sptwb_ex.spt.DataOutTransferLength = 0;
        sptwb_ex.spt.DataInTransferLength = 192;
        sptwb_ex.spt.DataDirection = SCSI_IOCTL_DATA_IN;
        sptwb_ex.spt.TimeOutValue = 2;
        sptwb_ex.spt.StorAddressOffset =
            offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,StorAddress);
        sptwb_ex.StorAddress.Type = STOR_ADDRESS_TYPE_BTL8;
        sptwb_ex.StorAddress.Port = 0;
        sptwb_ex.StorAddress.AddressLength = STOR_ADDR_BTL8_ADDRESS_LENGTH;
        sptwb_ex.StorAddress.Path = 0;
        sptwb_ex.StorAddress.Target = 1;
        sptwb_ex.StorAddress.Lun = 0;
        sptwb_ex.spt.SenseInfoOffset =
           offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,ucSenseBuf);
        sptwb_ex.spt.DataOutBufferOffset = 0;
        sptwb_ex.spt.DataInBufferOffset =
           offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,ucDataBuf);
        sptwb_ex.spt.Cdb[0] = SCSIOP_MODE_SENSE;
        sptwb_ex.spt.Cdb[1] = 0x08; // target shall not return any block descriptors
        sptwb_ex.spt.Cdb[2] = MODE_PAGE_CACHING;
        sptwb_ex.spt.Cdb[4] = 192;
        length = offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX,ucDataBuf) +
           sptwb_ex.spt.DataInTransferLength;

        status = DeviceIoControl(fileHandle,
                                 IOCTL_SCSI_PASS_THROUGH_EX,
                                 &sptwb_ex,
                                 sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS_EX),
                                 &sptwb_ex,
                                 length,
                                 &returned,
                                 FALSE);

        PrintStatusResultsEx(status,returned,&sptwb_ex,length);
    }
    else
    {
        ZeroMemory(&sptwb,sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS));
        sptwb.spt.Length = sizeof(SCSI_PASS_THROUGH);
        sptwb.spt.PathId = 0;
        sptwb.spt.TargetId = 1;
        sptwb.spt.Lun = 0;
        sptwb.spt.CdbLength = CDB6GENERIC_LENGTH;
        sptwb.spt.SenseInfoLength = SPT_SENSE_LENGTH;
        sptwb.spt.DataIn = SCSI_IOCTL_DATA_IN;
        sptwb.spt.DataTransferLength = 192;
        sptwb.spt.TimeOutValue = 2;
        sptwb.spt.DataBufferOffset =
           offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS,ucDataBuf);
        sptwb.spt.SenseInfoOffset =
           offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS,ucSenseBuf);
        sptwb.spt.Cdb[0] = SCSIOP_MODE_SENSE;
        sptwb.spt.Cdb[1] = 0x08; // target shall not return any block descriptors
        sptwb.spt.Cdb[2] = MODE_PAGE_CACHING;
        sptwb.spt.Cdb[4] = 192;
        length = offsetof(SCSI_PASS_THROUGH_WITH_BUFFERS,ucDataBuf) +
           sptwb.spt.DataTransferLength;

        status = DeviceIoControl(fileHandle,
                                 IOCTL_SCSI_PASS_THROUGH,
                                 &sptwb,
                                 sizeof(SCSI_PASS_THROUGH),
                                 &sptwb,
                                 length,
                                 &returned,
                                 FALSE);

        PrintStatusResults(status,returned,&sptwb,length);
    }


    printf("            *****       WRITE DATA BUFFER operation         *****\n");
    
    dataBuffer = AllocateAlignedBuffer(sectorSize,alignmentMask, &pUnAlignedBuffer);
    FillMemory(dataBuffer,sectorSize/2,'N');
    FillMemory(dataBuffer + sectorSize/2,sectorSize/2,'T');

    if(srbType == 1)
    {
        ZeroMemory(&sptdwb_ex,sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER_EX));
        sptdwb_ex.sptd.Version = 0;
        sptdwb_ex.sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT_EX);
        sptdwb_ex.sptd.ScsiStatus = 0;
        sptdwb_ex.sptd.CdbLength = CDB10GENERIC_LENGTH;
        sptdwb_ex.sptd.StorAddressLength = sizeof(STOR_ADDR_BTL8);
        sptdwb_ex.sptd.SenseInfoLength = SPT_SENSE_LENGTH;
        sptdwb_ex.sptd.DataOutTransferLength = sectorSize;
        sptdwb_ex.sptd.DataInTransferLength = 0;
        sptdwb_ex.sptd.DataDirection = SCSI_IOCTL_DATA_OUT;
        sptdwb_ex.sptd.TimeOutValue = 2;
        sptdwb_ex.sptd.StorAddressOffset =
            offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER_EX,StorAddress);
        sptdwb_ex.StorAddress.Type = STOR_ADDRESS_TYPE_BTL8;
        sptdwb_ex.StorAddress.Port = 0;
        sptdwb_ex.StorAddress.AddressLength = STOR_ADDR_BTL8_ADDRESS_LENGTH;
        sptdwb_ex.StorAddress.Path = 0;
        sptdwb_ex.StorAddress.Target = 1;
        sptdwb_ex.StorAddress.Lun = 0;
        sptdwb_ex.sptd.SenseInfoOffset = 
           offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER_EX,ucSenseBuf);
        sptdwb_ex.sptd.DataOutBuffer = dataBuffer;
        sptdwb_ex.sptd.DataInBuffer = NULL;
        sptdwb_ex.sptd.Cdb[0] = SCSIOP_WRITE_DATA_BUFF;
        sptdwb_ex.sptd.Cdb[1] = 2;                         // Data mode
        sptdwb_ex.sptd.Cdb[7] = (UCHAR)(sectorSize >> 8);  // Parameter List length
        sptdwb_ex.sptd.Cdb[8] = 0;
        length = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER_EX);

        status = DeviceIoControl(fileHandle,
                                 IOCTL_SCSI_PASS_THROUGH_DIRECT_EX,
                                 &sptdwb_ex,
                                 length,
                                 &sptdwb_ex,
                                 length,
                                 &returned,
                                 FALSE);

        PrintStatusResultsEx(status,returned,
           (PSCSI_PASS_THROUGH_WITH_BUFFERS_EX)&sptdwb_ex,length);

        if ((sptdwb_ex.sptd.ScsiStatus == 0) && (status != 0)) {
           PrintDataBuffer(dataBuffer,sptdwb_ex.sptd.DataOutTransferLength);
        }
    }