static void OnPaintWaypointPicto(WindowControl * Sender, LKSurface& Surface) {
    (void) Sender;
    if (wf) {

        WndFrame *wPicto = ((WndFrame *) wf->FindByName(TEXT("frmWaypointPicto")));
        if (wPicto) {
            const RECT rc = wPicto->GetClientRect();

            MapWindow::DrawWaypointPictoBg(Surface, rc);
            LKASSERT(ValidWayPoint(SelectedWaypoint));
            if (WayPointCalc[SelectedWaypoint].IsLandable) {
                MapWindow::DrawRunway(Surface, &WayPointList[SelectedWaypoint], rc, 4000, true);
            } else {
                MapWindow::DrawWaypointPicto(Surface, rc, &WayPointList[SelectedWaypoint]);
            }
        }
    }
}