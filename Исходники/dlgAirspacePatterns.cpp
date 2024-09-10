static void OnAirspacePatternsPaintListItem(WindowControl * Sender, LKSurface& Surface) {
    (void) Sender;
    if ((DrawListIndex < NUMAIRSPACEBRUSHES) &&(DrawListIndex >= 0)) {
        int i = DrawListIndex;
        Surface.SelectObject(LKBrush_White);
        Surface.SelectObject(LK_BLACK_PEN);
        Surface.SetBkColor(LKColor(0xFF, 0xFF, 0xFF));
        Surface.SelectObject(MapWindow::GetAirspaceBrush(i));
        Surface.SetTextColor(LKColor(0x00, 0x00, 0x00));
        Surface.Rectangle(100 * ScreenScale, 2 * ScreenScale, 180 * ScreenScale, 22 * ScreenScale);
    }
}