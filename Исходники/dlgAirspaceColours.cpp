static void OnAirspaceColoursPaintListItem(WindowControl * Sender, LKSurface& Surface){
  (void)Sender;
  if ((DrawListIndex < NUMAIRSPACECOLORS) &&(DrawListIndex>=0)) {
    int i = DrawListIndex;
    Surface.SelectObject(LKBrush_White);
    Surface.SelectObject(LK_BLACK_PEN);
    Surface.SetBkColor(LKColor(0xFF, 0xFF, 0xFF));
    Surface.SelectObject(MapWindow::GetAirspaceSldBrush(i)); // this is the solid brush
    Surface.SetTextColor(MapWindow::GetAirspaceColour(i));
    Surface.Rectangle(
              100*ScreenScale, 
              2*ScreenScale,
              180*ScreenScale,
              22*ScreenScale);
  }
}