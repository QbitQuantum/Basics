    HOOKFUNC LONG WINAPI MyChangeDisplaySettingsA(LPDEVMODEA lpDevMode, DWORD dwFlags)
    {
        if (lpDevMode)
        {
            ENTER(lpDevMode->dmPelsWidth, lpDevMode->dmPelsHeight, dwFlags);
        }
        else
        {
            ENTER(dwFlags);
        }
        if (tasflags.forceWindowed && lpDevMode /*&& (dwFlags & CDS_FULLSCREEN)*/)
        {
            fakeDisplayWidth = lpDevMode->dmPelsWidth;
            fakeDisplayHeight = lpDevMode->dmPelsHeight;
            fakePixelFormatBPP = lpDevMode->dmBitsPerPel;
            fakeDisplayValid = TRUE;
            FakeBroadcastDisplayChange(fakeDisplayWidth, fakeDisplayHeight, fakePixelFormatBPP);
            if (gamehwnd)
                MakeWindowWindowed(gamehwnd, fakeDisplayWidth, fakeDisplayHeight);

            return DISP_CHANGE_SUCCESSFUL;
        }
        LONG rv = ChangeDisplaySettingsA(lpDevMode, dwFlags);
        if (lpDevMode) FakeBroadcastDisplayChange(lpDevMode->dmPelsWidth, lpDevMode->dmPelsHeight, lpDevMode->dmBitsPerPel);
        return rv;
    }