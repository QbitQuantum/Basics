/* Returns video modes supported by our device/driver
 * Note: If we fail here we'd be asked to enter 800x600@4bpp mode later in VBoxDispDrvEnablePDEV.
 */
ULONG APIENTRY VBoxDispDrvGetModes(HANDLE hDriver, ULONG cjSize, DEVMODEW *pdm)
{
    int rc;
    VIDEO_MODE_INFORMATION *pModesTable;
    ULONG cModes;
    LOGF_ENTER();

    rc = VBoxDispMPGetVideoModes(hDriver, &pModesTable, &cModes);
    VBOX_WARNRC_RETV(rc, 0);

    if (!pdm) /* return size of buffer required to store all supported modes */
    {
        EngFreeMem(pModesTable);
        LOGF_LEAVE();
        return cModes * sizeof(DEVMODEW);
    }

    ULONG mode, cMaxNodes=cjSize/sizeof(DEVMODEW);

    for (mode=0; mode<cModes && mode<cMaxNodes; ++mode, ++pdm)
    {
        memset(pdm, 0, sizeof(DEVMODEW));
        memcpy(pdm->dmDeviceName, VBOXDISP_DEVICE_NAME, sizeof(VBOXDISP_DEVICE_NAME));

        pdm->dmSpecVersion   = DM_SPECVERSION;
        pdm->dmDriverVersion = DM_SPECVERSION;
        pdm->dmSize          = sizeof(DEVMODEW);
        pdm->dmDriverExtra   = 0;

        pdm->dmBitsPerPel       = pModesTable[mode].NumberOfPlanes*pModesTable[mode].BitsPerPlane;
        pdm->dmPelsWidth        = pModesTable[mode].VisScreenWidth;
        pdm->dmPelsHeight       = pModesTable[mode].VisScreenHeight;
        pdm->dmDisplayFrequency = pModesTable[mode].Frequency;
        pdm->dmDisplayFlags     = 0;
        pdm->dmFields           = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT|DM_DISPLAYFREQUENCY|DM_DISPLAYFLAGS;
    }
    EngFreeMem(pModesTable);

    LOG(("%d mode(s) reported", mode));

    LOGF_LEAVE();
    return mode * sizeof(DEVMODEW);
}