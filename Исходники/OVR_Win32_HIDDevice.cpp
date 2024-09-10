bool HIDDeviceManager::Enumerate(HIDEnumerateVisitor* enumVisitor)
{
    HDEVINFO                 hdevInfoSet;
    SP_DEVICE_INTERFACE_DATA interfaceData;
    interfaceData.cbSize = sizeof(interfaceData);

    // Get handle to info data set describing all available HIDs.
    hdevInfoSet = SetupDiGetClassDevsA(&HidGuid, NULL, NULL, DIGCF_INTERFACEDEVICE | DIGCF_PRESENT);
    if (hdevInfoSet == INVALID_HANDLE_VALUE)
        return false;

    for(int deviceIndex = 0;
            SetupDiEnumDeviceInterfaces(hdevInfoSet, NULL, &HidGuid, deviceIndex, &interfaceData);
            deviceIndex++)
    {
        // For each device, we extract its file path and open it to get attributes,
        // such as vendor and product id. If anything goes wrong, we move onto next device.
        HIDDevicePathWrapper pathWrapper;
        if (!pathWrapper.InitPathFromInterfaceData(hdevInfoSet, &interfaceData))
            continue;

        // Look for the device to check if it is already opened.
        Ptr<DeviceCreateDesc> existingDevice = Manager->FindDevice(pathWrapper.GetPath());
        // if device exists and it is opened then most likely the CreateHIDFile
        // will fail; therefore, we just set Enumerated to 'true' and continue.
        if (existingDevice && existingDevice->pDevice)
        {
            existingDevice->Enumerated = true;
            continue;
        }

        // open device in non-exclusive mode for detection...
        HANDLE hidDev = CreateHIDFile(pathWrapper.GetPath(), false);
        if (hidDev == INVALID_HANDLE_VALUE)
            continue;

        HIDDeviceDesc devDesc;
        devDesc.Path = pathWrapper.GetPath();
        if (initVendorProductVersion(hidDev, &devDesc) &&
                enumVisitor->MatchVendorProduct(devDesc.VendorId, devDesc.ProductId) &&
                initUsage(hidDev, &devDesc))
        {
            initStrings(hidDev, &devDesc);

            // Construct minimal device that the visitor callback can get feature reports from.
            Win32::HIDDevice device(this, hidDev);
            enumVisitor->Visit(device, devDesc);
        }

        ::CloseHandle(hidDev);
    }

    SetupDiDestroyDeviceInfoList(hdevInfoSet);
    return true;
}