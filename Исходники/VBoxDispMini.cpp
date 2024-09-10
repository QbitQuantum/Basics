/* Map device framebuffer and VRAM to our virtual address space */
int VBoxDispMPMapMemory(PVBOXDISPDEV pDev, PVIDEO_MEMORY_INFORMATION pMemInfo)
{
    DWORD dwrc;
    ULONG cbReturned;
    VIDEO_MEMORY vMem;
    VIDEO_MEMORY_INFORMATION vMemInfo;
    LOGF_ENTER();

    Assert(!pDev->memInfo.FrameBufferBase && !pDev->memInfo.VideoRamBase);

    vMem.RequestedVirtualAddress = NULL;
    dwrc = EngDeviceIoControl(pDev->hDriver, IOCTL_VIDEO_MAP_VIDEO_MEMORY, &vMem, sizeof(vMem), &vMemInfo, sizeof(vMemInfo), &cbReturned);
    VBOX_CHECK_WINERR_RETRC(dwrc, VERR_DEV_IO_ERROR);
    VBOX_WARN_IOCTLCB_RETRC("IOCTL_VIDEO_MAP_VIDEO_MEMORY", cbReturned, sizeof(vMemInfo), VERR_DEV_IO_ERROR);

    if (vMemInfo.FrameBufferBase != vMemInfo.VideoRamBase)
    {
        WARN(("FrameBufferBase!=VideoRamBase."));
        return VERR_GENERAL_FAILURE;
    }

    /* Check if we can access mapped memory */
    uint32_t magic = (*(ULONG *)vMemInfo.FrameBufferBase == 0xDEADF00D) ? 0xBAADF00D : 0xDEADF00D;

    ASMAtomicWriteU32((uint32_t *)vMemInfo.FrameBufferBase, magic);
    if (ASMAtomicReadU32((uint32_t *)vMemInfo.FrameBufferBase) != magic)
    {
        WARN(("can't write to framebuffer memory!"));
        return VERR_GENERAL_FAILURE;
    }

    memcpy(pMemInfo, &vMemInfo, sizeof(vMemInfo));

    LOGF_LEAVE();
    return VINF_SUCCESS;
}