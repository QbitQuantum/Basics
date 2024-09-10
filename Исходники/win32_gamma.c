void _glfwPlatformSetGammaRamp(_GLFWmonitor* monitor, const GLFWgammaramp* ramp)
{
    HDC dc;
    WORD values[768];
    DISPLAY_DEVICE display;

    if (ramp->size != 256)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Win32: Gamma ramp size must be 256");
        return;
    }

    memcpy(values +   0, ramp->red,   256 * sizeof(unsigned short));
    memcpy(values + 256, ramp->green, 256 * sizeof(unsigned short));
    memcpy(values + 512, ramp->blue,  256 * sizeof(unsigned short));

    ZeroMemory(&display, sizeof(DISPLAY_DEVICE));
    display.cb = sizeof(DISPLAY_DEVICE);
    EnumDisplayDevices(monitor->win32.name, 0, &display, 0);

    dc = CreateDC(L"DISPLAY", display.DeviceString, NULL, NULL);
    SetDeviceGammaRamp(dc, values);
    DeleteDC(dc);
}