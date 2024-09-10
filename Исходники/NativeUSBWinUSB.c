int
USBGetInterfaceDescriptor(void *deviceHandle, struct USBInterfaceDescriptor *desc) {
    DWORD bytesReturned = 0;
    BOOL flag = FALSE;
    BYTE temp[DEVICE_PATH_SIZE];
    PUSB_COMMON_DESCRIPTOR retval;
    __usb_interface_t *usb;

    if(0 == desc) {
        return -1;
    }

    if(0 == deviceHandle) {
        return -2;
    }

    usb = (__usb_interface_t *)deviceHandle;
    memset(temp, 0, sizeof(temp));

    flag = WinUsb_GetDescriptor(usb->winUSBHandle,
        USB_CONFIGURATION_DESCRIPTOR_TYPE, 0, 0, temp,
        sizeof(temp), &bytesReturned);

    if(FALSE == flag) {
        return -3;
    }

    retval = WinUsb_ParseDescriptors(temp, bytesReturned, temp,
        USB_INTERFACE_DESCRIPTOR_TYPE);

    if(NULL == retval) {
        return -4;
    }

    memcpy(desc, retval, sizeof(struct USBInterfaceDescriptor));

    return 0;
}