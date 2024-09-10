void LKSurface::DrawCircle(long x, long y, int radius, const RECT& rc, bool fill) {

    if ((x - radius) > rc.right) return;
    if ((x + radius) < rc.left) return;
    if ((y - radius) > rc.bottom) return;
    if ((y + radius) < rc.top) return;

    // Only called by ThreadDraw, so static vector can be used.
    static std::vector<RasterPoint> CirclePt;
    buildCircle(RasterPoint(x,y), radius, CirclePt);
      
    if (fill) {
        Polygon(CirclePt.data(), CirclePt.size(), rc);
    } else {
        Polyline(CirclePt.data(), CirclePt.size(), rc);
    }
}