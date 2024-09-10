void openusb(usbdevice* kb, short vendor, short product){
    kb->lastkeypress = KEY_NONE;
    if(IS_RGB(vendor, product))
        // Handle 3 is the control handle
        kb->handle = kb->handles[3];
    else
        // Non RGB keyboards don't have one, so just use 0
        kb->handle = kb->handles[0];

    // Set up the device
    int setup = setupusb(kb, vendor, product);
    if(setup == -1 || (setup && usb_tryreset(kb))){
        closehandle(kb);
        pthread_mutex_unlock(&kb->mutex);
        pthread_mutex_destroy(&kb->mutex);
        pthread_mutex_destroy(&kb->keymutex);
        return;
    }

    // Start handling HID reports for the input
    IOHIDDeviceRegisterInputReportCallback(kb->handles[0], kb->urbinput, 8, reportcallback, kb);
    if(IS_RGB(vendor, product))
        IOHIDDeviceRegisterInputReportCallback(kb->handles[1], kb->urbinput + 8, 21, reportcallback, kb);
    else
        IOHIDDeviceRegisterInputReportCallback(kb->handles[1], kb->urbinput + 8, 4, reportcallback, kb);
    if(IS_RGB(vendor, product))
        IOHIDDeviceRegisterInputReportCallback(kb->handles[2], kb->kbinput, MSG_SIZE, reportcallback, kb);
    else
        IOHIDDeviceRegisterInputReportCallback(kb->handles[2], kb->urbinput + 8 + 4, 15, reportcallback, kb);

    // Register for close notification
    IOHIDDeviceRegisterRemovalCallback(kb->handle, usbremove, kb);

    // Update connected
    updateconnected();
    notifyconnect(kb, 1);
    int index = INDEX_OF(kb, keyboard);
    printf("Device ready at %s%d\n", devpath, index);
    pthread_mutex_unlock(&kb->mutex);
}