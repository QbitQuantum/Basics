void
ArxDbgUiDlgColor::calculateRectSize(UINT controlId, CRect& rect, double gridX, double gridY,
                    long& sizeX, long& sizeY, long& bookEndGapX, long& bookEndGapY)
{
    CWnd* tmpWnd = GetDlgItem(controlId);
    ASSERT(tmpWnd != NULL);

    tmpWnd->GetClientRect(rect);
    tmpWnd->ClientToScreen(rect);
    ScreenToClient(rect);
    rect.DeflateRect(1, 1);

        // get the size of each tile
    double rectWidth = static_cast<double>(rect.Width());
    sizeX = static_cast<long>(rectWidth / gridX);
    double rectHeight = static_cast<double>(rect.Height());
    sizeY = static_cast<long>(rectHeight / gridY);

    bookEndGapX = static_cast<long>((rectWidth - (gridX * sizeX)) / 2.0);
    bookEndGapY = static_cast<long>((rectHeight - (gridY * sizeY)) / 2.0);
}