void UpdateWindowSize(DialogData* pdd, const int cx, const int cy, HWND hwnd) {
    const int nDeltaX = cx - pdd->sizeClient.dx;
    const int nDeltaY = cy - pdd->sizeClient.dy;

    HDWP hdwp = BeginDeferWindowPos(pdd->nItemCount);
    for (int i = 0; i < pdd->nItemCount; i++) {
        const DialogSizerSizingItem* psd = pdd->psd + i;
        HWND hwndChild = GetDlgItem(hwnd, psd->uControlID);
        RectI rect = MapRectToWindow(WindowRect(hwndChild), HWND_DESKTOP, hwnd);

        // Adjust the window horizontally
        if (psd->uSizeInfo & DS_MoveX)
            rect.x += nDeltaX;
        // Adjust the window vertically
        if (psd->uSizeInfo & DS_MoveY)
            rect.y += nDeltaY;
        // Size the window horizontally
        if (psd->uSizeInfo & DS_SizeX)
            rect.dx += nDeltaX;
        // Size the window vertically
        if (psd->uSizeInfo & DS_SizeY)
            rect.dy += nDeltaY;

        DeferWindowPos(hdwp, hwndChild, nullptr, rect.x, rect.y, rect.dx, rect.dy, SWP_NOACTIVATE | SWP_NOZORDER);
    }
    EndDeferWindowPos(hdwp);

    pdd->sizeClient = SizeI(cx, cy);
    // If we have a sizing grip enabled then adjust it's position
    pdd->UpdateGripper();
}