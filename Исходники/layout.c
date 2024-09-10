static LRESULT CALLBACK
WinPrevProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PWINPREV_DATA pData;

    pData = (PWINPREV_DATA)GetWindowLongPtrW(hWnd, GWLP_USERDATA);

    switch (msg)
    {
        case WM_CREATE:
        {
            pData = (PWINPREV_DATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*pData));
            if (!pData)
            {
                /* We failed to allocate our private data, halt the window creation */
                return (LRESULT)-1;
            }
            pData->hWnd  = hWnd;
            pData->pData = ConInfo;
            GetClientRect(pData->hWnd, &pData->rcMaxArea);
            // LPCREATESTRUCT::cx and cy give window (not client) size
            WinPrev_OnDisplayChange(pData);
            SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)pData);
            break;
        }

        case WM_DESTROY:
        {
            if (pData)
                HeapFree(GetProcessHeap(), 0, pData);
            break;
        }

        case WM_DISPLAYCHANGE:
        {
            WinPrev_OnDisplayChange(pData);
            UpdateWindow(hWnd);
            // InvalidateRect(hWnd, NULL, FALSE);
            break;
        }

        case WM_SIZE:
            break;

        case WM_ERASEBKGND:
            return 1;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);
            WinPrev_OnDraw(ps.hdc, pData);
            EndPaint(hWnd, &ps);
            return 0;
        }
    }

    return DefWindowProcW(hWnd, msg, wParam, lParam);
}