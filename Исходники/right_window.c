void PaintAlternatingRows (HWND hWnd)
//    re-draw rows with the appropriate background colour
{
    int i;
    RECT    rectUpd,        	//    rectangle to update
            rectDestin,        	//    temporary storage
            rect;            	//    row rectangle
    POINT    pt;
    int     iItems,
            iTop;
    COLORREF    c;            	//    temporary storage

//    get the rectangle to be updated
    GetUpdateRect (hWnd, &rectUpd, FALSE);
//    allow default processing first
    CallWindowProc (old_lv_proc, hWnd, WM_PAINT, 0, 0);
//    set the row horizontal dimensions
    SetRect (&rect, rectUpd.left, 0, rectUpd.right, 0);
//    number of displayed rows
    iItems = ListView_GetCountPerPage (hWnd);
//    first visible row
    iTop = ListView_GetTopIndex (hWnd);

    ListView_GetItemPosition (hWnd, iTop, &pt);
    for (i=iTop ; i<=iTop+iItems ; i++) {
//        set row vertical dimensions
        rect.top = pt.y;
        ListView_GetItemPosition (hWnd, i+1, &pt);
        rect.bottom = pt.y;
//        if row rectangle intersects update rectangle then it requires
//        re-drawing
        if (IntersectRect (&rectDestin, &rectUpd, &rect)) {
//            change text background colour accordingly
            c = get_row_color(hWnd, i);
            ListView_SetTextBkColor (hWnd, c);
//            invalidate the row rectangle then...
            InvalidateRect (hWnd, &rect, FALSE);
//            ...force default processing
            CallWindowProc (old_lv_proc, hWnd, WM_PAINT, 0, 0);
        }
    }
}