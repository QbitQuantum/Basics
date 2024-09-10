BOOL NTAPI bInitPointer(PPDEV ppdev, DEVINFO *pdevinfo)
{
    DWORD    returnedDataLength;

    ppdev->pPointerAttributes = (PVIDEO_POINTER_ATTRIBUTES) NULL;
    ppdev->cjPointerAttributes = 0; // initialized in screen.c

    //
    // Ask the miniport whether it provides pointer support.
    //

    if (EngDeviceIoControl(ppdev->hDriver,
                           IOCTL_VIDEO_QUERY_POINTER_CAPABILITIES,
                           NULL,
                           0,
                           &ppdev->PointerCapabilities,
                           sizeof(ppdev->PointerCapabilities),
                           &returnedDataLength))
    {
         return(FALSE);
    }

    //
    // If neither mono nor color hardware pointer is supported, there's no
    // hardware pointer support and we're done.
    //

    if ((!(ppdev->PointerCapabilities.Flags & VIDEO_MODE_MONO_POINTER)) &&
        (!(ppdev->PointerCapabilities.Flags & VIDEO_MODE_COLOR_POINTER)))
    {
        return(TRUE);
    }

    //
    // Note: The buffer itself is allocated after we set the
    // mode. At that time we know the pixel depth and we can
    // allocate the correct size for the color pointer if supported.
    //

    //
    // Set the asynchronous support status (async means miniport is capable of
    // drawing the Pointer at any time, with no interference with any ongoing
    // drawing operation)
    //

    if (ppdev->PointerCapabilities.Flags & VIDEO_MODE_ASYNC_POINTER)
    {
       pdevinfo->flGraphicsCaps |= GCAPS_ASYNCMOVE;
    }
    else
    {
       pdevinfo->flGraphicsCaps &= ~GCAPS_ASYNCMOVE;
    }

    return(TRUE);
}