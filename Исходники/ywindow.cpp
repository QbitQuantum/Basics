LRESULT CALLBACK Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    Window* window = (Window*)GetWindowLong(hwnd, GWL_USERDATA);
    switch (message) {
    case  WM_ERASEBKGND:
        return true;
    case WM_PAINT:
        {
            RECT rect;
            GetUpdateRect(hwnd, &rect, FALSE);
            SkRect clip_rect = SkRect::MakeXYWH(
                SkIntToScalar(rect.left), 
                SkIntToScalar(rect.top), 
                SkIntToScalar(rect.right - rect.left),
                SkIntToScalar(rect.bottom - rect.top));
            window->Draw(clip_rect);
            TexturePool::GetInstance()->CanvasToScreen(clip_rect);
        }
        break;
    case WM_SIZE:
        {
            if(wParam != SIZE_MINIMIZED) {
                RECT rect;
                GetClientRect(hwnd, &rect);
                window->SetGeometry(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
                window->Dolayout();
            }
        }
        break;
    case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
            if(window->LimitMaxWidth() < (int)(INT32_MAX - GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYBORDER))) {
                lpMMI->ptMaxTrackSize.x = window->LimitMaxWidth() + GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYBORDER);
            }
            if(window->LimitMaxHeight() < (int)(INT32_MAX - GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYBORDER))) {
                lpMMI->ptMaxTrackSize.y = window->LimitMaxHeight() + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER);
            }
            RECT inner_rect, window_rect;
            GetClientRect(hwnd, &inner_rect);
            GetWindowRect(hwnd, &window_rect);

            lpMMI->ptMinTrackSize.x = window->LimitMinWidth() + 
                ((window_rect.right - window_rect.left) - (inner_rect.right - inner_rect.left));

            lpMMI->ptMinTrackSize.y = window->LimitMinHeight() +
                ((window_rect.bottom - window_rect.top) - (inner_rect.bottom - inner_rect.top));
        }
    default:
        auto events = EventFactory::GetInstance()->CreateEvent(message, wParam, lParam);
        for (auto event:events) {
            if(event && event->Target()) {
                event->Target()->DoEvent(event.get());
            }
        }
    }
    return CallWindowProc(window->oldProc_, hwnd, message, wParam, lParam);
}