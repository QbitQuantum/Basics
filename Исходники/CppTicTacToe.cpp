BOOL GetGameBoardRect(HWND &hwnd, RECT *pRect)
{
    RECT rc;
    if (GetClientRect(hwnd, &rc)) {
        pRect->left = ((rc.right - rc.left) - CELL_SIZE * 3) / 2;
        pRect->top = ((rc.bottom - rc.top) - CELL_SIZE * 3) / 2;

        pRect->right = pRect->left + CELL_SIZE * 3;
        pRect->bottom = pRect->top + CELL_SIZE * 3;
return TRUE;
    }

    SetRectEmpty(pRect);
    return FALSE;
}