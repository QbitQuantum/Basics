static LRESULT WINAPI doc_view_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    DocHost *This;

    static const WCHAR wszTHIS[] = {'T','H','I','S',0};

    if(msg == WM_CREATE) {
        This = *(DocHost**)lParam;
        SetPropW(hwnd, wszTHIS, This);
    }else {
        This = GetPropW(hwnd, wszTHIS);
    }

    switch(msg) {
    case WM_SIZE:
        return resize_document(This, LOWORD(lParam), HIWORD(lParam));
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}