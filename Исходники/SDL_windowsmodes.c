static SDL_bool
WIN_GetDisplayMode(_THIS, LPCTSTR deviceName, DWORD index, SDL_DisplayMode * mode)
{
    SDL_VideoData *vid_data = (SDL_VideoData *) _this->driverdata;
    SDL_DisplayModeData *data;
    DEVMODE devmode;
    HDC hdc;

    devmode.dmSize = sizeof(devmode);
    devmode.dmDriverExtra = 0;
    if (!EnumDisplaySettings(deviceName, index, &devmode)) {
        return SDL_FALSE;
    }

    data = (SDL_DisplayModeData *) SDL_malloc(sizeof(*data));
    if (!data) {
        return SDL_FALSE;
    }
    data->DeviceMode = devmode;
    data->DeviceMode.dmFields =
        (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY |
         DM_DISPLAYFLAGS);
    data->ScaleX = 1.0f;
    data->ScaleY = 1.0f;
    data->DiagDPI = 0.0f;
    data->HorzDPI = 0.0f;
    data->VertDPI = 0.0f;

    /* Fill in the mode information */
    mode->format = SDL_PIXELFORMAT_UNKNOWN;
    mode->w = devmode.dmPelsWidth;
    mode->h = devmode.dmPelsHeight;
    mode->refresh_rate = devmode.dmDisplayFrequency;
    mode->driverdata = data;

    if (index == ENUM_CURRENT_SETTINGS
        && (hdc = CreateDC(deviceName, NULL, NULL, NULL)) != NULL) {
        char bmi_data[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)];
        LPBITMAPINFO bmi;
        HBITMAP hbm;
        int logical_width = GetDeviceCaps( hdc, HORZRES );
        int logical_height = GetDeviceCaps( hdc, VERTRES );

        data->ScaleX = (float)logical_width / devmode.dmPelsWidth;
        data->ScaleY = (float)logical_height / devmode.dmPelsHeight;
        mode->w = logical_width;
        mode->h = logical_height;

        // WIN_GetMonitorDPI needs mode->w and mode->h
        // so only call after those are set.
        if (vid_data->GetDpiForMonitor) {
            WIN_GetMonitorDPIData dpi_data;
            RECT monitor_rect;

            dpi_data.vid_data = vid_data;
            dpi_data.mode = mode;
            dpi_data.mode_data = data;
            monitor_rect.left = devmode.dmPosition.x;
            monitor_rect.top = devmode.dmPosition.y;
            monitor_rect.right = monitor_rect.left + 1;
            monitor_rect.bottom = monitor_rect.top + 1;
            EnumDisplayMonitors(NULL, &monitor_rect, WIN_GetMonitorDPI, (LPARAM)&dpi_data);
        } else {
            // We don't have the Windows 8.1 routine so just
            // get system DPI.
            data->HorzDPI = (float)GetDeviceCaps( hdc, LOGPIXELSX );
            data->VertDPI = (float)GetDeviceCaps( hdc, LOGPIXELSY );
            if (data->HorzDPI == data->VertDPI) {
                data->DiagDPI = data->HorzDPI;
            } else {
                data->DiagDPI = SDL_ComputeDiagonalDPI( mode->w,
                                                        mode->h,
                                                        (float)GetDeviceCaps( hdc, HORZSIZE ) / 25.4f,
                                                        (float)GetDeviceCaps( hdc, VERTSIZE ) / 25.4f );
            }
        }
        
        SDL_zero(bmi_data);
        bmi = (LPBITMAPINFO) bmi_data;
        bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

        hbm = CreateCompatibleBitmap(hdc, 1, 1);
        GetDIBits(hdc, hbm, 0, 1, NULL, bmi, DIB_RGB_COLORS);
        GetDIBits(hdc, hbm, 0, 1, NULL, bmi, DIB_RGB_COLORS);
        DeleteObject(hbm);
        DeleteDC(hdc);
        if (bmi->bmiHeader.biCompression == BI_BITFIELDS) {
            switch (*(Uint32 *) bmi->bmiColors) {
            case 0x00FF0000:
                mode->format = SDL_PIXELFORMAT_RGB888;
                break;
            case 0x000000FF:
                mode->format = SDL_PIXELFORMAT_BGR888;
                break;
            case 0xF800:
                mode->format = SDL_PIXELFORMAT_RGB565;
                break;
            case 0x7C00:
                mode->format = SDL_PIXELFORMAT_RGB555;
                break;
            }
        } else if (bmi->bmiHeader.biBitCount == 8) {
            mode->format = SDL_PIXELFORMAT_INDEX8;
        } else if (bmi->bmiHeader.biBitCount == 4) {
            mode->format = SDL_PIXELFORMAT_INDEX4LSB;
        }
    } else {
        /* FIXME: Can we tell what this will be? */
        if ((devmode.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
            switch (devmode.dmBitsPerPel) {
            case 32:
                mode->format = SDL_PIXELFORMAT_RGB888;
                break;
            case 24:
                mode->format = SDL_PIXELFORMAT_RGB24;
                break;
            case 16:
                mode->format = SDL_PIXELFORMAT_RGB565;
                break;
            case 15:
                mode->format = SDL_PIXELFORMAT_RGB555;
                break;
            case 8:
                mode->format = SDL_PIXELFORMAT_INDEX8;
                break;
            case 4:
                mode->format = SDL_PIXELFORMAT_INDEX4LSB;
                break;
            }
        }
    }
    return SDL_TRUE;
}