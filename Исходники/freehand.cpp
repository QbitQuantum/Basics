QPainterPath FreehandShape::buildPainterPath(void)
{
    QPainterPath path;

    StlStrokeList::iterator sEnd = _geometry.strokes.end();
    for (StlStrokeList::iterator s = _geometry.strokes.begin(); s != sEnd; ++s)
    {
        StlStroke::iterator pBegin = (*s).begin();
        StlStroke::iterator pEnd = (*s).end();
        for (StlStroke::iterator p = pBegin; p != pEnd; ++p)
        {
            if (p == pBegin)
            {
                // First point.
                path.moveTo(QPointF((*p).x, (*p).y));
            }
            else
            {
                path.lineTo(QPointF((*p).x, (*p).y));
            }
        }
    }
    return path;
}