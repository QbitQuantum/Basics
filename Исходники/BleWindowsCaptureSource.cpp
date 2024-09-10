QPixmap BleWindowsCaptureSource::cursorPixmap()
{
    static HCURSOR cursor = NULL;
    static QPixmap cachedCursor = QPixmap();

    QPixmap cursorPixmap;
    HICON icon;
    CURSORINFO cursorInfo;
    ICONINFO iconInfo;
    cursorInfo.cbSize = sizeof(CURSORINFO);

    if(GetCursorInfo(&cursorInfo))
    {
        if (cursor == cursorInfo.hCursor)
            return cachedCursor;

        if (cursorInfo.flags == CURSOR_SHOWING)
        {
            icon = CopyIcon(cursorInfo.hCursor);
            if (GetIconInfo(icon, &iconInfo))
            {
                if (iconInfo.hbmColor != NULL) {
                    cursorPixmap = QtWin::fromHBITMAP(iconInfo.hbmColor, QtWin::HBitmapAlpha);
                } else if (iconInfo.hbmMask != NULL){//if the cursor hasn't color image (for example, Ibeam cursor)
                    cursorPixmap = QtWin::fromHBITMAP(iconInfo.hbmMask, QtWin::HBitmapAlpha).mask();

                    //replace white color with transparent
                    QImage cursorImage = cursorPixmap.copy(0, cursorPixmap.height() / 2, cursorPixmap.width(), cursorPixmap.height() / 2).toImage();
                    cursorImage.setColor(0, Qt::transparent);
                    cursorPixmap = QPixmap::fromImage(cursorImage);
                }
            }
        }
    }

    cursor = cursorInfo.hCursor;
    cachedCursor = cursorPixmap;

    return cursorPixmap;
}