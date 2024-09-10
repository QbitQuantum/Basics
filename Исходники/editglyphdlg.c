static LRESULT CALLBACK
EditGlyphEditWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    PEDIT_GLYPH_INFO Info;

    Info = (PEDIT_GLYPH_INFO) GetWindowLongW(hwnd, GWLP_USERDATA);

    if(Info)
    {
        switch(uMsg)
        {
            case WM_CREATE:
                return 0;

            case WM_LBUTTONDOWN:
                SetPixelBit(Info, GET_Y_LPARAM(lParam) / Info->lEditSpacing, GET_X_LPARAM(lParam) / Info->lEditSpacing, 1);
                return 0;

            case WM_RBUTTONDOWN:
                SetPixelBit(Info, GET_Y_LPARAM(lParam) / Info->lEditSpacing, GET_X_LPARAM(lParam) / Info->lEditSpacing, 0);
                return 0;

            case WM_PAINT:
            {
                BOOL bBit;
                HPEN hOldPen;
                HPEN hPen;
                PAINTSTRUCT ps;
                RECT rect;
                UINT i;
                UINT j;

                BeginPaint(hwnd, &ps);

                // Draw the grid
                GetClientRect(hwnd, &rect);
                Info->lEditSpacing = rect.right / 8;

                hPen = CreatePen( PS_SOLID, 1, RGB(128, 128, 128) );
                hOldPen = SelectObject(ps.hdc, hPen);

                for(i = 1; i < 8; i++)
                {
                    MoveToEx(ps.hdc, i * Info->lEditSpacing, 0, NULL);
                    LineTo  (ps.hdc, i * Info->lEditSpacing, rect.right);

                    MoveToEx(ps.hdc, 0, i * Info->lEditSpacing, NULL);
                    LineTo  (ps.hdc, rect.right, i * Info->lEditSpacing);
                }

                SelectObject(ps.hdc, hOldPen);
                DeleteObject(hPen);

                // Draw all bits
                for(i = 0; i < 8; i++)
                {
                    for(j = 0; j < 8; j++)
                    {
                        bBit = (BOOL) (Info->CharacterBits[i] << j & 0x80);

                        GetBitRect(Info, i, j, &rect);
                        FillRect( ps.hdc, &rect, (HBRUSH) GetStockObject(bBit ? BLACK_BRUSH : WHITE_BRUSH) );
                    }
                }

                // Draw the bounding rectangle
                SelectObject( ps.hdc, GetStockObject(NULL_BRUSH) );
                Rectangle(ps.hdc, 0, 0, rect.right, rect.right);

                EndPaint(hwnd, &ps);
                return 0;
            }
        }
    }

    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}