static void test_GetDeviceStatus(void)
{
    IDirectInput8A *pDI;
    HRESULT hr;

    hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, &IID_IDirectInput8A, (void **)&pDI, NULL);
    if (FAILED(hr))
    {
        win_skip("Failed to instantiate a IDirectInputA instance: 0x%08x\n", hr);
        return;
    }

    hr = IDirectInput8_GetDeviceStatus(pDI, NULL);
    ok(hr == E_POINTER, "IDirectInput8_GetDeviceStatus returned 0x%08x\n", hr);

    hr = IDirectInput8_GetDeviceStatus(pDI, &GUID_Unknown);
    todo_wine
    ok(hr == DIERR_DEVICENOTREG, "IDirectInput8_GetDeviceStatus returned 0x%08x\n", hr);

    hr = IDirectInput8_GetDeviceStatus(pDI, &GUID_SysMouse);
    ok(hr == DI_OK, "IDirectInput8_GetDeviceStatus returned 0x%08x\n", hr);

    IDirectInput8_Release(pDI);
}