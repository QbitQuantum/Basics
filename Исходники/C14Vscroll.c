LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int  cxChar, cxCaps, cyChar, cyClient,
        iVscrollPos = 0, //竖直滑块当前位置
        row_num,
        col_num = 8;
    static wchar_t** data;
    static wchar_t* text;
    HDC         hdc;
    int         i, y;
    PAINTSTRUCT ps;
    TCHAR       szBuffer[10];
    TEXTMETRIC  tm;

    switch (message)
    {
    case WM_CREATE:
        hdc = GetDC(hwnd);
        GetTextMetrics(hdc, &tm);
        cyChar = tm.tmHeight + tm.tmExternalLeading;//字体高度
        ReleaseDC(hwnd, hdc);

        text = getFileContent();
        row_num = (int)ceil((double)wcslen(text) / col_num);
        data = (wchar_t**)malloc(sizeof(wchar_t*) * (row_num));
        SetScrollRange(hwnd, SB_VERT, 0, row_num - 1, FALSE);//范围
        SetScrollPos(hwnd, SB_VERT, iVscrollPos, TRUE);//初始位置
        return 0;

    case WM_SIZE:
        cyClient = HIWORD(lParam);
        return 0;

    case WM_VSCROLL:
        switch (LOWORD(wParam))
        {
        case SB_LINEUP://点滚动条上方的小箭头
            iVscrollPos -= 1;
            break;

        case SB_LINEDOWN://点滚动条下方的小箭头
            iVscrollPos += 1;
            break;

        case SB_PAGEUP://在滚动条上方点空白位置
            iVscrollPos -= cyClient / cyChar;
            break;

        case SB_PAGEDOWN://在滚动条下方点空白位置
            iVscrollPos += cyClient / cyChar;
            break;

        case SB_THUMBPOSITION://在滚动条上松开鼠标
            iVscrollPos = HIWORD(wParam);//这里用上了wParam
            break;

        default:
            break;
        }

        iVscrollPos = max(0, min(iVscrollPos, row_num - 1));

        if (iVscrollPos != GetScrollPos(hwnd, SB_VERT))//获取当前的位置
        {
            SetScrollPos(hwnd, SB_VERT, iVscrollPos, TRUE);//更新数值
            InvalidateRect(hwnd, NULL, TRUE);//刷新界面
        }
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);

        for (i = 0; i < row_num; i++) {
            y = cyChar * (i - iVscrollPos);
            *(data + i) = (wchar_t*)malloc(sizeof(wchar_t) * (col_num + 1));
            wcsncpy_s(*(data + i), col_num + 1, text + col_num * i, col_num);
            if (i != row_num - 1) {
                TextOut(hdc, 0, y, *(data + i), col_num);
            } else {
                if (!wcslen(text) % col_num) {
                    TextOut(hdc, 0, y, *(data + i), wcslen(text) % col_num);
                }
                else {
                    TextOut(hdc, 0, y, *(data + i), col_num);
                }
            }
        }
        EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}