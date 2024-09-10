int hidOpenDevice( unsigned short vendor, unsigned short product, hidlib_t *outHidhandle )
{
    HDEVINFO deviceInfoList;
    SP_DEVICE_INTERFACE_DATA deviceInfo;
    SP_DEVICE_INTERFACE_DETAIL_DATA *deviceDetails = NULL;
    DWORD size;
    int i;
    HANDLE handle = INVALID_HANDLE_VALUE;
    char matchName[64];
    int matchLength;
    int matchOffset = 4;
    int error = HIDLIB_OK;

    *outHidhandle = (hidlib_t)INVALID_HANDLE_VALUE;

    sprintf( matchName, "hid#vid_%04x&pid_%04x", vendor, product );
    matchLength = strlen( matchName );

    deviceInfoList = SetupDiGetClassDevs( &hidGuid, NULL, NULL,
            DIGCF_PRESENT | DIGCF_INTERFACEDEVICE );
    if( deviceInfoList == NULL ) {
        return HIDLIB_ERR_INTERNAL;
    }
    deviceInfo.cbSize = sizeof(deviceInfo);

    for( i=0; ; i++ ) {
        if( handle != INVALID_HANDLE_VALUE ) {
            CloseHandle( handle );
            handle = INVALID_HANDLE_VALUE;
        }

        if( !SetupDiEnumDeviceInterfaces( deviceInfoList, 0, &hidGuid, i, &deviceInfo ) ) {
            error = HIDLIB_ERR_NOT_FOUND;
            break;
        }

        size = 0;
        if( !SetupDiGetDeviceInterfaceDetail( deviceInfoList, &deviceInfo,
                NULL, 0, &size, NULL ) && 
                GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
            error = HIDLIB_ERR_INTERNAL;
            break;
        }
        deviceDetails = (SP_DEVICE_INTERFACE_DETAIL_DATA *)malloc( size );
        if( deviceDetails == NULL ) {
            error = HIDLIB_ERR_OUT_OF_MEMORY;
        }
        deviceDetails->cbSize = sizeof(*deviceDetails);

        if( SetupDiGetDeviceInterfaceDetail( deviceInfoList, &deviceInfo,
                    deviceDetails, size, &size, NULL ) ) {
            if( strlen( deviceDetails->DevicePath ) > matchOffset + matchLength  &&
                    memcmp( deviceDetails->DevicePath+4, matchName, matchLength ) == 0 ) {
                handle = CreateFile( deviceDetails->DevicePath,
                        GENERIC_READ|GENERIC_WRITE,
                        FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
                        0, NULL );
            }
        }
        free( deviceDetails );

        if( handle == INVALID_HANDLE_VALUE ) {
            // Cannot open device. Probably a standard HID device, in which
            // case Windows already has the device open.
            continue;
        }

        // We found the device we are looking for!
        error = HIDLIB_OK;
        break;
    }

    SetupDiDestroyDeviceInfoList( deviceInfoList );

    if( handle != INVALID_HANDLE_VALUE ) {
        *outHidhandle = (hidlib_t)handle;
        return 0;
    } else {
        return error;
    }
}