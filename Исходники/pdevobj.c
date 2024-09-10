PPDEVOBJ
NTAPI
EngpGetPDEV(
    PUNICODE_STRING pustrDeviceName)
{
    UNICODE_STRING ustrCurrent;
    PPDEVOBJ ppdev;
    PGRAPHICS_DEVICE pGraphicsDevice;

    /* Acquire PDEV lock */
    EngAcquireSemaphore(ghsemPDEV);

    /* If no device name is given, ... */
    if (!pustrDeviceName && gppdevPrimary)
    {
        /* ... use the primary PDEV */
        ppdev = gppdevPrimary;

        /* Reference the pdev */
        InterlockedIncrement(&ppdev->cPdevRefs);
        goto leave;
    }

    /* Loop all present PDEVs */
    for (ppdev = gppdevList; ppdev; ppdev = ppdev->ppdevNext)
    {
        /* Get a pointer to the GRAPHICS_DEVICE */
        pGraphicsDevice = ppdev->pGraphicsDevice;

        /* Compare the name */
        RtlInitUnicodeString(&ustrCurrent, pGraphicsDevice->szWinDeviceName);
        if (RtlEqualUnicodeString(pustrDeviceName, &ustrCurrent, FALSE))
        {
            /* Found! Reference the PDEV */
            InterlockedIncrement(&ppdev->cPdevRefs);
            break;
        }
    }

    /* Did we find one? */
    if (!ppdev)
    {
        /* No, create a new PDEV */
        ppdev = EngpCreatePDEV(pustrDeviceName, NULL);
        if (ppdev)
        {
            /* Insert the PDEV into the list */
            ppdev->ppdevNext = gppdevList;
            gppdevList = ppdev;

            /* Set as primary PDEV, if we don't have one yet */
            if (!gppdevPrimary)
            {
                gppdevPrimary = ppdev;
                ppdev->pGraphicsDevice->StateFlags |= DISPLAY_DEVICE_PRIMARY_DEVICE;
            }
        }
    }

leave:
    /* Release PDEV lock */
    EngReleaseSemaphore(ghsemPDEV);

    return ppdev;
}