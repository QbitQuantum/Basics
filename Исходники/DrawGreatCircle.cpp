//
// Draw bearing line to target
//
void MapWindow::DrawGreatCircle(LKSurface& Surface, const RECT& rc, const ScreenProjection& _Proj, 
        double startLon, double startLat, double targetLon, double targetLat) {

    POINT pt[2] = {
        _Proj.LonLat2Screen(startLon, startLat),
        _Proj.LonLat2Screen(targetLon, targetLat)
    };


    if(LKGeom::ClipLine(rc, pt[0], pt[1])) {
        const auto hpOld = Surface.SelectObject(LKPen_GABRG);
        Surface.Polyline(pt, 2);
        Surface.SelectObject(LK_BLACK_PEN);
        Surface.Polyline(pt, 2);
        Surface.SelectObject(hpOld);
    }
}