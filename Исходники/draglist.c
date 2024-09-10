/***********************************************************************
 *		DrawInsert (COMCTL32.15)
 *
 * Draws insert arrow by the side of the ListBox item in the parent window.
 *
 * RETURNS
 *      Nothing.
 */
VOID WINAPI DrawInsert (HWND hwndParent, HWND hwndLB, INT nItem)
{
    RECT rcItem, rcListBox, rcDragIcon;
    HDC hdc;
    DRAGLISTDATA * data;

    TRACE("(%p %p %d)\n", hwndParent, hwndLB, nItem);

    if (!hDragArrow)
        hDragArrow = LoadIconW(COMCTL32_hModule, (LPCWSTR)IDI_DRAGARROW);

    if (LB_ERR == SendMessageW(hwndLB, LB_GETITEMRECT, nItem, (LPARAM)&rcItem))
        return;

    if (!GetWindowRect(hwndLB, &rcListBox))
        return;

    /* convert item rect to parent co-ordinates */
    if (!MapWindowPoints(hwndLB, hwndParent, (LPPOINT)&rcItem, 2))
        return;

    /* convert list box rect to parent co-ordinates */
    if (!MapWindowPoints(HWND_DESKTOP, hwndParent, (LPPOINT)&rcListBox, 2))
        return;

    rcDragIcon.left = rcListBox.left - DRAGICON_HOTSPOT_X;
    rcDragIcon.top = rcItem.top - DRAGICON_HOTSPOT_Y;
    rcDragIcon.right = rcListBox.left;
    rcDragIcon.bottom = rcDragIcon.top + DRAGICON_HEIGHT;

    if (!GetWindowSubclass(hwndLB, DragList_SubclassWindowProc, DRAGLIST_SUBCLASSID, (DWORD_PTR*)&data))
        return;

    if (nItem < 0)
        SetRectEmpty(&rcDragIcon);

    /* prevent flicker by only redrawing when necessary */
    if (!EqualRect(&rcDragIcon, &data->last_drag_icon_rect))
    {
        /* get rid of any previous inserts drawn */
        RedrawWindow(hwndParent, &data->last_drag_icon_rect, NULL,
            RDW_INTERNALPAINT | RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW);

        CopyRect(&data->last_drag_icon_rect, &rcDragIcon);

        if (nItem >= 0)
        {
            hdc = GetDC(hwndParent);

            DrawIcon(hdc, rcDragIcon.left, rcDragIcon.top, hDragArrow);

            ReleaseDC(hwndParent, hdc);
        }
    }
}