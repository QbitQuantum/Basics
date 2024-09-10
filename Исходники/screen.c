BOOL DeinitVGA(PPDEV ppdev)
{
    VIDEO_MEMORY VideoMemory;
    ULONG ReturnedDataLength;

    VideoMemory.RequestedVirtualAddress = (PVOID)ppdev->fbScreen;

    if (EngDeviceIoControl(ppdev->KMDriver,
                           IOCTL_VIDEO_UNMAP_VIDEO_MEMORY,
                           (PVOID)&VideoMemory,
                           sizeof(VIDEO_MEMORY),
                           NULL,
                           0,
                           &ReturnedDataLength))
    {
        DPRINT1("Failed to unmap video memory.\n");
        EngDebugBreak();
        return FALSE;
    }
    return TRUE;
}