LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            RECT area;            

            HDC hDC = BeginPaint(hWnd, &ps);
            GetClientRect(hWnd, &area);
            SetBkMode(hDC, TRANSPARENT);

            // draw caption with the fuzzed font
            HFONT hFont = MyCreateFont(); 
            HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
            if (hOldFont) 
            { 
                DrawTextA(hDC, m_szTable, -1, &area, DT_CENTER | DT_VCENTER);
                SelectObject(hDC, hOldFont); 
            } 
            
            EndPaint(hWnd, &ps);

            break;
        }

    case WM_COMMAND:
        {
            switch (wParam)
            {
            case ID_CLOSE:

#ifdef TEST_MSG
                MessageBoxA(0, __FUNCTION__, "ID_CLOSE", MB_ICONINFORMATION);
#endif
                // window can be closed now
                SetEvent(m_hWndEvent);
                break;
            }

            break;
        }

    case WM_DESTROY:

        PostQuitMessage(0);
        break;

    default:

        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}