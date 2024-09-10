static LRESULT WINAPI shell_embedding_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    WebBrowser *This;

    static const WCHAR wszTHIS[] = {'T','H','I','S',0};

    if(msg == WM_CREATE) {
        This = *(WebBrowser**)lParam;
        SetPropW(hwnd, wszTHIS, This);
    }else {
        This = GetPropW(hwnd, wszTHIS);
    }

    switch(msg) {
    case WM_SIZE:
        return resize_window(This, LOWORD(lParam), HIWORD(lParam));
    case WM_DOCHOSTTASK:
        return process_dochost_tasks(&This->doc_host);
    case WM_SETFOCUS:
        notify_on_focus(This, TRUE);
        break;
    case WM_KILLFOCUS:
        notify_on_focus(This, FALSE);
        break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}