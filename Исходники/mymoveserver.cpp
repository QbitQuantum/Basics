QPoint MyMoveServer::getCentralPoint(const QList<QPoint>& list, int& width, int& height)
{
    int minx = 0;
    int maxx = 0;
    int miny = 0;
    int maxy = 0;
    int x = 0;
    int y = 0;
    for (int i=0; i < list.length(); i++)
    {
        QPoint p = list.at(i);
        x = p.x(); y = p.y();
        if (x < minx ) minx = x;
        else if (x > maxx) maxx = x;
        if (y < miny ) miny = y;
        else if (y > maxy) maxy = y;
    }

    width = maxx - minx;
    height = maxy - miny;

    return QPointF((minx+maxx)*0.5, (maxy+miny)*0.5).toPoint();
}