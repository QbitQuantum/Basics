/*!
    \internal
     Create's a RegionHandle, it's the caller's responsibility to release.
*/
RgnHandle QRegion::toQDRgn() const
{
    RgnHandle rgnHandle = qt_mac_get_rgn();
    if(d->qt_rgn && d->qt_rgn->numRects) {
        RgnHandle tmp_rgn = qt_mac_get_rgn();
        int n = d->qt_rgn->numRects;
        const QRect *qt_r = (n == 1) ? &d->qt_rgn->extents : d->qt_rgn->rects.constData();
        while (n--) {
            SetRectRgn(tmp_rgn,
                       qMax(SHRT_MIN, qt_r->x()),
                       qMax(SHRT_MIN, qt_r->y()),
                       qMin(SHRT_MAX, qt_r->right() + 1),
                       qMin(SHRT_MAX, qt_r->bottom() + 1));
            UnionRgn(rgnHandle, tmp_rgn, rgnHandle);
            ++qt_r;
        }
        qt_mac_dispose_rgn(tmp_rgn);
    }
    return rgnHandle;
}