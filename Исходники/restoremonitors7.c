/*
    Gets GDI Device name from Source (e.g. \\.\DISPLAY4).
*/
void getGDIDeviceNameFromSource(LUID adapterId, UINT32 sourceId) {
    DISPLAYCONFIG_SOURCE_DEVICE_NAME deviceName;
    DISPLAYCONFIG_DEVICE_INFO_HEADER header;
    header.size = sizeof(DISPLAYCONFIG_SOURCE_DEVICE_NAME);
    header.adapterId = adapterId;
    header.id = sourceId;
    header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
    deviceName.header = header;
    if (!Result_DCGDI(DisplayConfigGetDeviceInfo( (DISPLAYCONFIG_DEVICE_INFO_HEADER*) &deviceName )))
        return;
    printf("  GDI Device name: ");
    wprintf(deviceName.viewGdiDeviceName);
    puts("");
}