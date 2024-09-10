bool HIDDeviceManager::Enumerate(HIDEnumerateVisitor* enumVisitor)
{
    if (!initializeManager())
    {
        return false;
    }
    

	CFSetRef deviceSet = IOHIDManagerCopyDevices(HIDManager);
    if (!deviceSet)
        return false;
    
	CFIndex deviceCount = CFSetGetCount(deviceSet);
    
    // Allocate a block of memory and read the set into it.
    IOHIDDeviceRef* devices = (IOHIDDeviceRef*) OVR_ALLOC(sizeof(IOHIDDeviceRef) * deviceCount);
    CFSetGetValues(deviceSet, (const void **) devices);
    

    // Iterate over devices.
    for (CFIndex deviceIndex = 0; deviceIndex < deviceCount; deviceIndex++)
    {
        IOHIDDeviceRef hidDev = devices[deviceIndex];
        
        if (!hidDev)
        {
            continue;
        }
        
        HIDDeviceDesc devDesc;
                
        if (getPath(hidDev, &(devDesc.Path)) &&
            initVendorProductVersion(hidDev, &devDesc) &&
            enumVisitor->MatchVendorProduct(devDesc.VendorId, devDesc.ProductId) &&
            initUsage(hidDev, &devDesc))
        {
            initStrings(hidDev, &devDesc);
            initSerialNumber(hidDev, &devDesc);

            // Look for the device to check if it is already opened.
            Ptr<DeviceCreateDesc> existingDevice = DevManager->FindHIDDevice(devDesc, true);
            // if device exists and it is opened then most likely the CreateHIDFile
            // will fail; therefore, we just set Enumerated to 'true' and continue.
            if (existingDevice && existingDevice->pDevice)
            {
                existingDevice->Enumerated = true;
                continue;
            }

            // open the device temporarily for startup communication
            if (IOHIDDeviceOpen(hidDev, kIOHIDOptionsTypeSeizeDevice) == kIOReturnSuccess)
            {
                // Construct minimal device that the visitor callback can get feature reports from.
                OSX::HIDDevice device(this, hidDev);

                enumVisitor->Visit(device, devDesc);

                IOHIDDeviceClose(hidDev, kIOHIDOptionsTypeSeizeDevice);
            }
        }
    }
    
    OVR_FREE(devices);
    CFRelease(deviceSet);
    
    return true;
}