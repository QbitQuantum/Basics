/*
    PSYCHHIDCheckInit() 
    
    Check to see if we need to create the USB-HID device list. If it has not been created then create it.   
*/
void PsychHIDVerifyInit(void)
{
    int busId, devId;
    pRecDevice currentDevice = NULL;
    struct hid_device_info* hid_dev = NULL;
    
    // If hid_devices list of all HID devices not yet initialized,
    // perform device enumeration:
    if (!hidlib_devices) {        
        // Low-Level enumeration by HIDLIB:
        hidlib_devices = hid_enumerate(0x0, 0x0);
        
        // Build our own higher-level device list filled with info
        // from the low-level list:
        for (hid_dev = hidlib_devices; hid_dev != NULL; hid_dev = hid_dev->next) {
            // Allocate and zero-init high level struct currentDevice:
            currentDevice = calloc(1, sizeof(recDevice));
            
            // Copy low-level props to corresponding high-level props:
            currentDevice->usagePage = hid_dev->usage_page;
            currentDevice->usage = hid_dev->usage;
            // Abuse the "transport" string for the device path. On OS/X this just contains "USB":
            sprintf(&currentDevice->transport[0], "%s", hid_dev->path);
            currentDevice->vendorID = hid_dev->vendor_id;
            currentDevice->productID = hid_dev->product_id;
            currentDevice->version = hid_dev->release_number;
            if (hid_dev->manufacturer_string) wcstombs(&currentDevice->manufacturer[0], hid_dev->manufacturer_string, 256);
            if (hid_dev->product_string) wcstombs(&currentDevice->product[0], hid_dev->product_string, 256);
            if (hid_dev->serial_number) wcstombs(&currentDevice->serial[0], hid_dev->serial_number, 256);

            // Convert unique device path into unique numeric location id:
            if (PSYCH_SYSTEM == PSYCH_LINUX) {
                // Use USB bus-id and device-id as unique location identifier:
                sscanf(hid_dev->path, "%x:%x", &busId, &devId);
                currentDevice->locID = (double) ((busId << 16) + (devId << 0));
            }
        
            if (PSYCH_SYSTEM == PSYCH_WINDOWS) {
                // Use device container id as unique location identifier.
                // This may only work on Windows-7+ and is a bit of a hack here,
                // the id is a GUID, nothing related to busId or devId. We init
                // devId with the hid_dev pointer value, to get a devId and thereby
                // location id in case proper parsing of a container id doesn't work:
                busId = 0;
                devId = (int) hid_dev;
                if (strstr(hid_dev->path, "{")) sscanf(strstr(hid_dev->path, "{"), "{%x-%x", &busId, &devId);
                currentDevice->locID = (double) (((psych_uint64) busId << 32) + devId);
            }

            // Interface number is great for identifying DAQ devices, but not available
            // on OS/X, so this will be a Linux/Windows only thing.
            currentDevice->interfaceId = hid_dev->interface_number;

            // Enqueue record into linked list:
            currentDevice->pNext = hid_devices;
            hid_devices = currentDevice;
        }
    }
    
    return;
}