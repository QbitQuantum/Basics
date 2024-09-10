LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int cxClient, cyClient;
    static int cxGrid, cyGrid;
    static int CheckedGrid[5][5];

    PAINTSTRUCT ps;
    HDC         hdc;
    int         i, j;
    int         cxCursor, cyCursor;
    RECT        rectGrid;
    POINT       ptCursor;

    switch(uMsg)
    {
    case WM_KEYDOWN:
        {
            //Get Cursor current position
            GetCursorPos(&ptCursor);
            ScreenToClient(hwnd, &ptCursor);
            i = ptCursor.x / cxGrid;
            j = ptCursor.y / cyGrid;


            switch(wParam)
            {
            case VK_LEFT:
                i--;
                break;
            case VK_RIGHT:
                i++;
                break;
            case VK_UP:
                j--;
                break;
            case VK_DOWN:
                j++;
                break;
            case VK_HOME:
                i = 0;
                j = 0;
                break;
            case VK_END:
                i = ROWCOUNT - 1;
                j = COLUMNCOUNT - 1;
                break;
            default:
                break;
            }
            if (i > COLUMNCOUNT - 1)
            {
                i = 0;
            }
            else if (i < 0)
            {
                i = COLUMNCOUNT - 1;
            }
            if (j > ROWCOUNT - 1)
            {
                j = 0;
            }
            else if (j < 0)
            {
                j = ROWCOUNT - 1;
            }
            ptCursor.x = i * cxGrid + cxGrid / 2;
            ptCursor.y = j * cyGrid + cyGrid / 2;
            ClientToScreen(hwnd, &ptCursor);
            SetCursorPos(ptCursor.x, ptCursor.y);
            break;
        }
    case WM_CHAR:
        {
            switch (wParam)
            {
            case ' ':       //Space
            case '\r':      //Enter
                {
                    GetCursorPos(&ptCursor);
                    ScreenToClient(hwnd, &ptCursor);
                    SendMessage(hwnd, WM_LBUTTONDOWN, 0, MAKELONG(ptCursor.x, ptCursor.y));
                break;
                }
            }
            break;
        }
    case WM_SIZE:
        {
            cxClient    = LOWORD(lParam);
            cyClient    = HIWORD(lParam);
            cxGrid      = cxClient / COLUMNCOUNT;
            cyGrid      = cyClient / ROWCOUNT;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
    case WM_LBUTTONDOWN:
        {
            cxCursor = LOWORD(lParam);
            cyCursor = HIWORD(lParam);
            i = cxCursor / cxGrid;
            j = cyCursor /cyGrid;
            CheckedGrid[i][j] = !CheckedGrid[i][j];
            rectGrid.left   = i * cxGrid;
            rectGrid.right  = (i+1) * cxGrid;
            rectGrid.top    = j * cyGrid;
            rectGrid.bottom = (j+1) * cyGrid;
            InvalidateRect(hwnd, &rectGrid, TRUE);
            break;
        }
    case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);

            // Draw lines
            for (i = 0; i < ROWCOUNT; ++i)
            {
                MoveToEx(hdc, 0, cyGrid * (1 + i), NULL);
                LineTo(hdc, cxGrid * COLUMNCOUNT, cyGrid * (1 + i));
            }
            for (i = 0; i < COLUMNCOUNT; ++i)
            {
                MoveToEx(hdc, cxGrid * (1 + i), 0, NULL);
                LineTo(hdc, cxGrid * (1 + i), cyGrid * ROWCOUNT);
            }

            for (i = 0; i < ROWCOUNT; ++i)
            {
                for (j=0; j < COLUMNCOUNT; ++j)
                {
                    if (CheckedGrid[i][j])
                    {
                        //Draw Cross line
                        MoveToEx(hdc, i * cxGrid, j * cyGrid, NULL);
                        LineTo(hdc, (i+1) * cxGrid, (j+1) * cyGrid);

                        MoveToEx(hdc, (i+1) * cxGrid, j * cyGrid, NULL);
                        LineTo(hdc, i * cxGrid, (j+1) * cyGrid);
                    }
                }
            }
            // Draw Checkers
            EndPaint(hwnd, &ps);
            break;
        }
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}