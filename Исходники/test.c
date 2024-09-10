VOID
FormatSomeTracks (
	CHAR DeviceId
	)

{
    HANDLE FileHandle;
    OBJECT_ATTRIBUTES ObjectAttributes;
    STRING NameString;
    UNICODE_STRING UnicodeString;
    IO_STATUS_BLOCK IoStatus;
    NTSTATUS Status;
	PCHAR DeviceName;
	FORMAT_PARAMETERS FormatParameters;
	BAD_TRACK_NUMBER BadTracks[80];
	ULONG i;


	if (DeviceId == '1') {
		DeviceName = &DriveA[0];
	} else if (DeviceId == '2') {
		DeviceName = &DriveB[0];
	} else {
		DbgPrint( "Format: invalid drive id '%c'\n", DeviceId );
		return;
	}

	GetMediaTypes( NULL );

	Zero( &Buffer[0], 10 );
	DbgPrompt( "Enter media type code: ", Buffer, 10 );
	FormatParameters.MediaType = (MEDIA_TYPE) atoi( &Buffer[0] );
	Zero( &Buffer[0], 10 );
	DbgPrompt( "Enter start cylinder: ", Buffer, 10 );
	FormatParameters.StartCylinderNumber = (ULONG) atoi( &Buffer[0] );
	Zero( &Buffer[0], 10 );
	DbgPrompt( "Enter end cylinder: ", Buffer, 10 );
	FormatParameters.EndCylinderNumber = (ULONG) atoi( &Buffer[0] );
	Zero( &Buffer[0], 10 );
	DbgPrompt( "Enter start head: ", Buffer, 10 );
	FormatParameters.StartHeadNumber = (ULONG) atoi( &Buffer[0] );
	Zero( &Buffer[0], 10 );
	DbgPrompt( "Enter end head: ", Buffer, 10 );
	FormatParameters.EndHeadNumber = (ULONG) atoi( &Buffer[0] );


	RtlInitString( &NameString, DeviceName );

    Status = RtlAnsiStringToUnicodeString( &UnicodeString, &NameString, TRUE );

    ASSERT( NT_SUCCESS( Status ) );

    //
    // Open the device.
    //

    InitializeObjectAttributes( &ObjectAttributes,
                                  &UnicodeString,
                                  OBJ_CASE_INSENSITIVE,
                                  (HANDLE) NULL,
                                  (PSECURITY_DESCRIPTOR) NULL
                                );
    Status = NtOpenFile( &FileHandle,
                         FILE_WRITE_DATA | FILE_READ_DATA | FILE_READ_ATTRIBUTES | SYNCHRONIZE,
                         &ObjectAttributes,
                         &IoStatus,
                         FILE_SHARE_READ,
                         FILE_SYNCHRONOUS_IO_ALERT );
    RtlFreeUnicodeString( &UnicodeString );
    if (!NT_SUCCESS( Status )) {
        DbgPrint( "format:  error opening %s for input;  error %X\n",
                 DeviceName,
                 Status );
        return;
    }


	DbgPrompt( "\nInsert diskette and press RETURN when ready ", Buffer, 256 );

    //
    // Issue the format command.
    //

	Status = NtDeviceIoControlFile( FileHandle,
									(HANDLE) NULL,
                                    (PIO_APC_ROUTINE) NULL,
                                    (PVOID) NULL,
                                    &IoStatus,
									IOCTL_DISK_FORMAT_TRACKS,
									&FormatParameters,
									(ULONG) sizeof( FormatParameters ),
									&BadTracks[0],
									(ULONG) sizeof( BadTracks )
									);
									
    if (!NT_SUCCESS( Status )) {
        DbgPrint( "format:  error on NtDeviceIoControlFile;  error %X\n", Status );
    } else if (Status != STATUS_SUCCESS) {
        Status = NtWaitForSingleObject( FileHandle, TRUE, NULL );
        if (Status == STATUS_SUCCESS) {
        	if (!NT_SUCCESS( IoStatus.Status )) {
            	if (IoStatus.Status == STATUS_NOT_IMPLEMENTED) {
                	DbgPrint( "format: control function not implemented\n" );
            	}
            	if (IoStatus.Status == STATUS_MEDIA_WRITE_PROTECTED) {
            		DbgPrint( "format: media is write protected\n" );
				} else if (IoStatus.Status == STATUS_DEVICE_NOT_READY) {
            		DbgPrint( "format: device not ready\n" );
				} else {
               		DbgPrint( "format:  error %X\n", IoStatus.Status );
				}
        	}
		}
    } else {

		if (IoStatus.Information) {

			//
			// Found some bad tracks.
			//

			i = 0;
			DbgPrint( "Bad tracks: " );
			while (IoStatus.Information >= sizeof( BAD_TRACK_NUMBER )) {
				DbgPrint( "%d  ", BadTracks[i++] );
				IoStatus.Information -= sizeof( BAD_TRACK_NUMBER );
			}
			DbgPrint( "  \n" );
		}
	}


    //
    // Close the file.
    //

    (VOID) NtClose( FileHandle );

    return;
}