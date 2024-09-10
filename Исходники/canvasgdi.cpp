bool GiCanvasGdi::rawBezierTo(const Point2d* pxs, int count)
{
    bool ret = false;

    if (count > 0)
    {
        std::vector<POINT> pts;
        pts.resize(count);
        for (int i = 0; i < count; i++)
            pxs[i].get(pts[i].x, pts[i].y);
        ret = !!PolyBezierTo(m_draw->getDrawDC(), &pts.front(), count);
    }

    return ret;
}