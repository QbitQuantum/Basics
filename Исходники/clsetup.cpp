void ClSetup::SetupCl(int platform_index, int device_index)
{
    platform = GetPlatformID(platform_index);
    PrintPlatformInfo(platform);
    device = GetDeviceID(device_index);
    PrintDeviceInfo(device);
    context = CreateContext();
    queue = CreateCommandQueue();
    bInit = true;
}