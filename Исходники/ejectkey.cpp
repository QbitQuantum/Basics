LRESULT CALLBACK EjectKey::OnRawInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // Determine size of raw input data
    UINT dwSize = 0;
    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));

    // Allocate enough room for input data and read it
    std::unique_ptr<BYTE[]> lpb(new BYTE[dwSize]);
    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb.get(), &dwSize, sizeof(RAWINPUTHEADER));

    // Get actual HID report
    RAWINPUT* rawinput = reinterpret_cast<RAWINPUT*>(lpb.get());
    RAWHID* rawhid = &(rawinput)->data.hid;
    uint32_t* report = reinterpret_cast<uint32_t*>(rawhid->bRawData);

    if (rawhid->dwSizeHid == 4)
    {
        // We may receive more than one report from each VM_INPUT, loop  through them
        for (unsigned int p = 0; p<rawhid->dwCount; p++)
        {
            // Eject down
            if (0x00200002 ==  *report)
            {
                SendKeyPress(&timer_param, false);
                SetTimer(hWnd, reinterpret_cast<UINT_PTR>(&timer_param), timer_param.delay, TimerProc);

            }
            // Eject up
            else if (0x00000002 == *report)
            {
                SendKeyPress(&timer_param, true);
                KillTimer(hWnd, reinterpret_cast<UINT_PTR>(&timer_param));
            }
            report++;
        }
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}