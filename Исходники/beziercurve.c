LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {
    
    HDC hdc;
    PAINTSTRUCT ps;

    POINT points[4] = { 20, 40, 320, 200, 330, 110, 450, 40 };

    switch(msg) {
    
        case WM_PAINT:

            hdc = BeginPaint(hwnd, &ps);

            PolyBezier(hdc, points, 4);

            EndPaint(hwnd, &ps);
            break;

        case WM_DESTROY:
 
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}