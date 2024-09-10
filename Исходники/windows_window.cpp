static LRESULT window_proc(HWND window_handle, UINT message, WPARAM wparam, LPARAM lparam)
{
    WindowsWindow* window = (WindowsWindow*)GetWindowLongPtr(window_handle, GWLP_USERDATA);

    if (window == nullptr)
        return DefWindowProc(window_handle, message, wparam, lparam);

    WindowState* state = &window->state;

    switch(message)
    {
    case WM_QUIT:
    case WM_CLOSE:
        state->closed = true;
        return 0;
    case WM_KEYDOWN:
        if (state->key_pressed_callback != nullptr)
        {
            state->key_pressed_callback(key_from_windows_key_code(wparam, lparam));
        }
        return 0;
    case WM_KEYUP:
        if (state->key_released_callback != nullptr)
        {
            state->key_released_callback(key_from_windows_key_code(wparam, lparam));
        }
        return 0;
    case WM_INPUT:
        {
            unsigned size;
            GetRawInputData((HRAWINPUT)lparam, RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER));
            unsigned char* lpb = new unsigned char[size];

            if (lpb == nullptr)
                return 0;

            if (GetRawInputData((HRAWINPUT)lparam, RID_INPUT, lpb, &size, sizeof(RAWINPUTHEADER)) != size)
                return 0;

            RAWINPUT* raw = (RAWINPUT*)lpb;

            if (raw->header.dwType == RIM_TYPEMOUSE && state->mouse_moved_callback && (raw->data.mouse.lLastX != 0 || raw->data.mouse.lLastY != 0))
                state->mouse_moved_callback({raw->data.mouse.lLastX, raw->data.mouse.lLastY});

            return 0;
        }
    }

    return DefWindowProc(window_handle, message, wparam, lparam);
}