HRGN qt_tryCreatePolygonRegion(const QPolygon &a, Qt::FillRule fillRule)
{
    const int tries = 10;
    for (int i = 0; i < tries; ++i) {
        HRGN region = CreatePolygonRgn(reinterpret_cast<const POINT*>(a.data()), a.size(),
                                       fillRule == Qt::OddEvenFill ? ALTERNATE : WINDING);
        if (region) {
            if (GetRegionData(region, 0, 0))
                return region;
            else
                DeleteObject(region);
        }
    }
    return 0;
}