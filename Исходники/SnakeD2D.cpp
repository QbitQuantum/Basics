LRESULT CALLBACK SnakeD2D::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    bool wasHandled = false;

    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        SnakeD2D *app = (SnakeD2D*)pcs->lpCreateParams;

        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            PtrToUlong(app)
        );
    }
    else
    {
        SnakeD2D *app = reinterpret_cast<SnakeD2D *>(static_cast<LONG_PTR>(
                            ::GetWindowLongPtrW(
                                hwnd,
                                GWLP_USERDATA
                            )));
        switch(message)
        {
        case WM_KEYDOWN:
            switch(wParam)
            {
            case VK_ESCAPE:
                PostQuitMessage(0);
                break;
            default:
                break;
            }
            wasHandled = true;
            break;
        default:
            break;
        case WM_PAINT:
            ValidateRect(hwnd, nullptr); // avoid new wm_paint messages
            wasHandled = true;
            result = 0;
            break;
        case WM_SIZE:
        {
            UINT width = LOWORD(lParam);
            UINT height = HIWORD(lParam);
            app->OnResize(width, height);
        }
        result = 0;
        wasHandled = true;
        break;
        }
    }

    if(!wasHandled)
        result = DefWindowProc(hwnd, message, wParam, lParam);

    return result;
}