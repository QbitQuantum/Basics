/*
 * called on mouse-down events. decide what to start tracking.
 */
void
gtab_press(HWND hwnd, lpTable ptab, int x, int y)
{
    long cell, ncells;
    long row;

    if (ptab->trackmode != TRACK_NONE) {
        return;
    }

    /* has he grabbed a cell-edge to resize ? */
    cell = gtab_xtocol(hwnd, ptab, x);
    if (cell == -1) {
        return;
    }
    if (gtab_isborder(hwnd, ptab, x, cell)) {
        gtab_trackcol(hwnd, ptab, cell, x);
        return;
    }
    if ( (cell > 0) && gtab_isborder(hwnd, ptab, x, cell-1)) {
        gtab_trackcol(hwnd, ptab, cell, x);
        return;
    }

    /* find which line he selected */
    row = gtab_linetorow(hwnd, ptab, gtab_ytoline(hwnd, ptab, y));

    /* is he selecting a disabled fixed area ? */
    if ( (row < ptab->hdr.fixedrows) || (cell < ptab->hdr.fixedcols)) {
        if (ptab->hdr.fixedselectable == FALSE) {
            return;
        }
    }

    // ignore if beyond data
    if ((row >= ptab->hdr.nrows) ||
            (cell >= ptab->hdr.ncols)) {
        return;
    }


    /* ok, start cell selection */
    ptab->trackmode = TRACK_CELL;
    SetCapture(hwnd);

    /* record and paint new selection */

    if (ptab->hdr.selectmode & TM_ROW) {
        cell = 0;
        ncells = ptab->hdr.ncols;
    } else {
        ncells = 1;
    }

    /*
     * if the shift key is down, then extend the selection to this
     * new anchor point, rather than create a new selection
     */
    if (GetKeyState(VK_SHIFT) & 0x8000) {
        gtab_extendsel(hwnd, ptab, row, cell, FALSE);
    } else {
        gtab_select(hwnd, ptab, row, cell, 1, ncells, FALSE);
    }
    return;
}