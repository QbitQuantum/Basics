LRESULT APIENTRY WndProc4(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)

{

    static PARAMS params;

    switch (message)

    {

    case   WM_CREATE:

        params.hwnd = hwnd;

        params.cyChar = HIWORD(GetDialogBaseUnits());

        _beginthread(Thread4, 0, &params);

        return 0;



    case   WM_SIZE:

        params.cxClient = LOWORD(lParam);

        params.cyClient = HIWORD(lParam);

        return 0;



    case   WM_DESTROY:

        params.bKill = TRUE;

        return 0;

    }

    return DefWindowProc(hwnd, message, wParam, lParam);

}