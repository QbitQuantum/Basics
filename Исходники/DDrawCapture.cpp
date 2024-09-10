bool InitDDrawCapture()
{
    bool versionSupported = false;
    HMODULE hDDrawLib = NULL;
    if (hDDrawLib = GetModuleHandle(TEXT("ddraw.dll")))
    {
        bool isWinVistaMin = IsWindowsVistaOrGreater();
        bool isWin7min = IsWindows7OrGreater();
        bool isWin8min = IsWindows8OrGreater();

        UPARAM libBaseAddr = UPARAM(hDDrawLib);
        UPARAM surfCreateOffset;
        UPARAM surfUnlockOffset;
        UPARAM surfReleaseOffset;
        UPARAM surfRestoreOffset;
        UPARAM surfBltOffset;
        UPARAM surfFlipOffset;
        UPARAM surfSetPaletteOffset;
        UPARAM palSetEntriesOffset;

        if (isWinVistaMin)
        {
            if (!isWin7min)
            {
                RUNEVERYRESET logOutput << CurrentTimeString() << "Windows Vista not supported yet" << endl;
            }
            else if (isWin7min && !isWin8min)
            {
                surfCreateOffset = 0x617E;
                surfUnlockOffset = 0x4C40;
                surfReleaseOffset = 0x3239;
                surfRestoreOffset = 0x3E9CB;
                surfBltOffset = surfCreateOffset + 0x44F63;
                surfFlipOffset = surfCreateOffset + 0x37789;
                surfSetPaletteOffset = surfCreateOffset + 0x4D2D3;
                palSetEntriesOffset = surfCreateOffset + 0x4CE68;
                versionSupported = true;
            }
            else if (isWin8min)
            {
                surfCreateOffset = 0x9530 + 0xC00;
                surfUnlockOffset = surfCreateOffset + 0x2A1D0;
                surfReleaseOffset = surfCreateOffset - 0x1A80;
                surfRestoreOffset = surfCreateOffset + 0x36000;
                surfBltOffset = surfCreateOffset + 0x438DC;
                surfFlipOffset = surfCreateOffset + 0x33EF3;
                surfSetPaletteOffset = surfCreateOffset + 0x4D3B8;
                palSetEntriesOffset = surfCreateOffset + 0x4CF4C;
                versionSupported = false;	// some crash bugs remaining

                RUNEVERYRESET logOutput << CurrentTimeString() << "Windows 8 not supported yet" << endl;
            }
            else
            {
                RUNEVERYRESET logOutput << CurrentTimeString() << "Unknown OS version" << endl;
            }
        }
        else
        {
            RUNEVERYRESET logOutput << CurrentTimeString() << "OS version not supported" << endl;
        }

        if (versionSupported)
        {
            ddrawSurfaceCreate.Hook((FARPROC)(libBaseAddr + surfCreateOffset), (FARPROC)CreateSurface);
            ddrawSurfaceRestore.Hook((FARPROC)(libBaseAddr + surfRestoreOffset), (FARPROC)Restore);
            ddrawSurfaceRelease.Hook((FARPROC)(libBaseAddr + surfReleaseOffset), (FARPROC)Release);
            ddrawSurfaceUnlock.Hook((FARPROC)(libBaseAddr + surfUnlockOffset), (FARPROC)Unlock);
            ddrawSurfaceBlt.Hook((FARPROC)(libBaseAddr + surfBltOffset), (FARPROC)Blt);
            ddrawSurfaceFlip.Hook((FARPROC)(libBaseAddr + surfFlipOffset), (FARPROC)Flip);
            ddrawSurfaceSetPalette.Hook((FARPROC)(libBaseAddr + surfSetPaletteOffset), (FARPROC)SetPalette);
            ddrawPaletteSetEntries.Hook((FARPROC)(libBaseAddr + palSetEntriesOffset), (FARPROC)PaletteSetEntries);

            ddrawSurfaceUnlock.Rehook();
            ddrawSurfaceFlip.Rehook();
            ddrawSurfaceBlt.Rehook();
            /*
            ddrawSurfaceCreate.Rehook();
            ddrawSurfaceRestore.Rehook();
            ddrawSurfaceRelease.Rehook();
            ddrawSurfaceSetPalette.Rehook();
            ddrawPaletteSetEntries.Rehook();
            */
        }
    }

    return versionSupported;
}