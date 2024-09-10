/***********************************************************************
 *		FlatSB_SetScrollInfo (COMCTL32.@)
 *
 * See SetScrollInfo.
 */
INT WINAPI
FlatSB_SetScrollInfo(HWND hwnd, int nBar, LPSCROLLINFO info, BOOL bRedraw)
{
    return SetScrollInfo(hwnd, nBar, info, bRedraw);
}