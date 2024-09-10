static VOID
OnResolutionChanged(PINFO pInfo, INT position)
{
    WCHAR Buffer[64];
    INT MaxSlider;

    MaxSlider = SendDlgItemMessageW(pInfo->hDisplayPage,
                                    IDC_GEOSLIDER,
                                    TBM_GETRANGEMAX,
                                    0,
                                    0);

    if (position == MaxSlider)
    {
        LoadStringW(hInst,
                    IDS_FULLSCREEN,
                    Buffer,
                    sizeof(Buffer) / sizeof(WCHAR));
    }
    else
    {
        WCHAR Pixel[64];

        if (LoadStringW(hInst,
                        IDS_PIXEL,
                        Pixel,
                        sizeof(Pixel) / sizeof(WCHAR)))
        {
#ifdef _MSC_VER
             _swprintf(Buffer,
                       Pixel,
                       pInfo->DisplayDeviceList->Resolutions[position].dmPelsWidth,
                       pInfo->DisplayDeviceList->Resolutions[position].dmPelsHeight,
                       Pixel);
#else
             swprintf(Buffer,
                      Pixel,
                      pInfo->DisplayDeviceList->Resolutions[position].dmPelsWidth,
                      pInfo->DisplayDeviceList->Resolutions[position].dmPelsHeight,
                      Pixel);
#endif
        }
    }

    SendDlgItemMessageW(pInfo->hDisplayPage,
                        IDC_SETTINGS_RESOLUTION_TEXT,
                        WM_SETTEXT,
                        0,
                        (LPARAM)Buffer);
}