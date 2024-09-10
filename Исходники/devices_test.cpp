BOOL CALLBACK EnumDevicesCallback(const DIDEVICEINSTANCE* instance, VOID* context)
{
    HRESULT hr;
    LPDIRECTINPUTDEVICE8 lpdid;

    if (GET_DIDEVICE_TYPE(instance->dwDevType) == DI8DEVTYPE_MOUSE ||
        GET_DIDEVICE_TYPE(instance->dwDevType) == DI8DEVTYPE_KEYBOARD
    )
        return DIENUM_CONTINUE;

    hr = gp_DI->CreateDevice(instance->guidInstance, &lpdid, NULL);

    if(SUCCEEDED(hr)) {
        _dump_DIDEVICEINSTANCE(instance);
        printf("Objects:\n");
        lpdid->EnumObjects(enumObjectsCallback, NULL, DIDFT_ALL);
    } else {
        printf("Error\n");
        HRNAME(hr);
    }

    return DIENUM_CONTINUE;
}