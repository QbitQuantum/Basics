/* Called for IOCTL_VIDEO_MAP_VIDEO_MEMORY.
 * Maps FrameBuffer and video RAM to a caller's virtual adress space.
 */
BOOLEAN VBoxMPMapVideoMemory(PVBOXMP_DEVEXT pExt, PVIDEO_MEMORY pRequestedAddress,
                             PVIDEO_MEMORY_INFORMATION pMapInfo, PSTATUS_BLOCK pStatus)
{
    PHYSICAL_ADDRESS framebuffer;
    ULONG inIoSpace = 0;

    LOGF(("framebuffer offset %#x", pExt->ulFrameBufferOffset));

    framebuffer.QuadPart = VBoxCommonFromDeviceExt(pExt)->phVRAM.QuadPart + pExt->ulFrameBufferOffset;

    pMapInfo->VideoRamBase = pRequestedAddress->RequestedVirtualAddress;
    VBOXMPIOCTL_HIDE(pRequestedAddress);
    pMapInfo->VideoRamLength = pExt->pPrimary->u.primary.ulMaxFrameBufferSize;

    pStatus->Status = VideoPortMapMemory(pExt, framebuffer, &pMapInfo->VideoRamLength,
                                         &inIoSpace, &pMapInfo->VideoRamBase);

    if (NO_ERROR == pStatus->Status)
    {
        pMapInfo->FrameBufferBase = (PUCHAR)pMapInfo->VideoRamBase;
        pMapInfo->FrameBufferLength =
            VBoxMPXpdmCurrentVideoMode(pExt)->VisScreenHeight*
            VBoxMPXpdmCurrentVideoMode(pExt)->ScreenStride;

        pStatus->Information = sizeof(VIDEO_MEMORY_INFORMATION);

        /* Save the new framebuffer size */
        pExt->ulFrameBufferSize = pMapInfo->FrameBufferLength;
        HGSMIAreaInitialize(&pExt->areaDisplay, pMapInfo->FrameBufferBase,
                            pMapInfo->FrameBufferLength, pExt->ulFrameBufferOffset);
    }

    VBOXMPIOCTL_UNHIDE();
    LOGF_LEAVE();
    return NO_ERROR == pStatus->Status;
}