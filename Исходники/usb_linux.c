int openusb(struct udev_device* dev, int model){
    // Make sure it's not connected yet
    const char* path = udev_device_get_devnode(dev);
    for(int i = 1; i < DEV_MAX; i++){
        if(keyboard[i].udev && !strcmp(path, udev_device_get_devnode(keyboard[i].udev)))
            return 0;
    }
    // Find a free USB slot
    for(int index = 1; index < DEV_MAX; index++){
        usbdevice* kb = keyboard + index;
        if(!IS_ACTIVE(kb)){
            // Open the sysfs device
            kb->udev = dev;
            kb->handle = open(path, O_RDWR);
            kb->model = model;
            if(kb->handle <= 0){
                printf("Error: Failed to open USB device: %s\n", strerror(errno));
                closehandle(kb);
                connectstatus |= 2;
                return -1;
            }

            // Copy device description and serial
            strncpy(kb->name, udev_device_get_sysattr_value(dev, "product"), NAME_LEN);
            strncpy(kb->setting.serial, udev_device_get_sysattr_value(dev, "serial"), SERIAL_LEN);
            printf("Connecting %s (S/N: %s)\n", kb->name, kb->setting.serial);

            // A USB reset is almost always required in order for it to work correctly
            printf("Resetting device\n");
            if(ioctl(kb->handle, USBDEVFS_RESET, 0)){
                printf("Reset failed (%s). Disconnecting.\n", strerror(errno));
                closehandle(kb);
                connectstatus |= 2;
                return -1;
            }

            // Claim the USB interfaces
            if(usbclaim(kb)){
                printf("Error: Failed to claim interface: %s\n", strerror(errno));
                closehandle(kb);
                connectstatus |= 2;
                return -1;
            }

            // Put the M-keys (K95) as well as the Brightness/Lock keys into software-controlled mode. This packet disables their
            // hardware-based functions.
            unsigned char datapkt[MSG_SIZE] = { 0x07, 0x04, 0x02 };
            struct usbdevfs_ctrltransfer transfer = { 0x21, 0x09, 0x0300, 0x03, MSG_SIZE, 500, datapkt };
            // This packet doesn't always succeed, so reset the device if that happens
            if(ioctl(kb->handle, USBDEVFS_CONTROL, &transfer) != MSG_SIZE){
                printf("Couldn't talk to device (%s), trying to reset again...\n", strerror(errno));
                if(resetusb(kb) || ioctl(kb->handle, USBDEVFS_CONTROL, &transfer) != MSG_SIZE){
                    printf("Reset failed (%s). Disconnecting.\n", strerror(errno));
                    closehandle(kb);
                    connectstatus |= 2;
                    return -1;
                }
            }

            // Set up the device
            if(setupusb(index)){
                closehandle(kb);
                connectstatus |= 2;
                return -1;
            }

            // Set up the interrupt transfers.
            kb->INPUT_TEST = 0;
            setint(kb);

            // We should receive an interrupt transfer shortly after setting them up. If it doesn't happen, the device
            // isn't working correctly and needs to be reset
            int received = 0;
            for(int wait = 0; wait < 10; wait++){
                usleep(50000);
                if(kb->INPUT_TEST){
                    received = 1;
                    break;
                }
            }
            if(!received){
                printf("Didn't get input, trying to reset again...\n");
                if(resetusb(kb)){
                    printf("Reset failed (%s). Disconnecting.\n", strerror(errno));
                    closehandle(kb);
                    connectstatus |= 2;
                    return -1;
                }
            }

            updateconnected();
            printf("Device ready at %s%d\n", devpath, index);
            connectstatus |= 1;
            return 0;
        }
    }
    printf("Error: No free devices\n");
    return -1;
}