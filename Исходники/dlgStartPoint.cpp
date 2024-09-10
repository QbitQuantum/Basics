static void OnStartPointPaintListItem(WindowControl * Sender, LKSurface& Surface) {
    (void)Sender;

    TCHAR label[MAX_PATH];

    if (DrawListIndex < MAXSTARTPOINTS) {
        int i = DrawListIndex;

        if ((StartPoints[i].Index != -1)&&(StartPoints[i].Active)) {
            _tcscpy(label, WayPointList[StartPoints[i].Index].Name);
        } else {
            int j;
            int i0=0;
            for (j=MAXSTARTPOINTS-1; j>=0; j--) {
                if ((StartPoints[j].Index!= -1)&&(StartPoints[j].Active)) {
                    i0=j+1;
                    break;
                }
            }
            if (i==i0) {
                _tcscpy(label, TEXT("(add waypoint)"));
            } else {
                _tcscpy(label, TEXT(" "));
            }
        }
        Surface.SetTextColor(RGB_BLACK);
        Surface.DrawText(2*ScreenScale, 2*ScreenScale, label, _tcslen(label));
    }
}