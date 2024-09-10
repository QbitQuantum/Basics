// Initialize the window to recieve raw-input messages
// This needs to be called initially so that Windows will send the messages from the 3D mouse to the window.
bool ConnexionClient::InitializeRawInput(HWND hwndTarget) {
    fWindow = hwndTarget;

    // Simply fail if there is no window
    if (!hwndTarget) {
        return false;
    }

    unsigned int numDevices = 0;
    PRAWINPUTDEVICE devicesToRegister = GetDevicesToRegister(&numDevices);

    if (numDevices == 0) {
        return false;
    }

    unsigned int cbSize = sizeof(devicesToRegister[0]);
    for (size_t i = 0; i < numDevices; i++) {
        // Set the target window to use
        //devicesToRegister[i].hwndTarget = hwndTarget;

        // If Vista or newer, enable receiving the WM_INPUT_DEVICE_CHANGE message.
        if (IsWindowsVistaOrGreater()) {
            devicesToRegister[i].dwFlags |= RIDEV_DEVNOTIFY;
        }
    }
    return (::RegisterRawInputDevices(devicesToRegister, numDevices, cbSize) != FALSE);
}