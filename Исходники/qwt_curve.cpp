void QwtCurve::closePolyline(const QwtDiMap &xMap, const QwtDiMap &yMap,
    QPointArray &pa) const
{
    const int sz = pa.size();
    if ( sz < 2 )
        return;

    pa.resize(sz + 2);

    if ( d_options & QwtCurve::Xfy )
    {
        pa.setPoint(sz,
            xMap.transform(d_ref), pa.point(sz - 1).y());
        pa.setPoint(sz + 1,
            xMap.transform(d_ref), pa.point(0).y());
    }
    else
    {
        pa.setPoint(sz,
            pa.point(sz - 1).x(), yMap.transform(d_ref));
        pa.setPoint(pa.size() - 1,
            pa.point(0).x(), yMap.transform(d_ref));
    }
}