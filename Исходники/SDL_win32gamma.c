int
WIN_GetDisplayGammaRamp(_THIS, Uint16 * ramp)
{
#ifdef _WIN32_WCE
	return -1;
#else
    SDL_DisplayData *data = (SDL_DisplayData *) SDL_CurrentDisplay.driverdata;
    HDC hdc;
    BOOL succeeded = FALSE;

    hdc = CreateDC(data->DeviceName, NULL, NULL, NULL);
    if (hdc) {
        succeeded = GetDeviceGammaRamp(hdc, ramp);
        if (!succeeded) {
            WIN_SetError("GetDeviceGammaRamp()");
        }
        DeleteDC(hdc);
    }
    return succeeded ? 0 : -1;
#endif
}