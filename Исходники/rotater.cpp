QPoint Rotater::get_line_cross_point(QLine base_line, QLine rotate_line)
{
    qreal k = (qreal)rotate_line.dy() / rotate_line.dx();
    int x(0), y(0);

    if (base_line.dy() == 0)
    {
        x = (base_line.y1() - rotate_line.y1()) / k + rotate_line.x1();
        y = base_line.y1();
    }
    else if (base_line.dx() == 0)
    {
        y = (base_line.x1() - rotate_line.x1()) * k + rotate_line.y1();
        x = base_line.x1();
    }

//    qDebug() << "k dx dy" << k << rotate_line.dx() << rotate_line.dy();
//    qDebug() << "rotate_line x1 y1" << rotate_line.x1() << rotate_line.y1();
//    qDebug() << "rotate_line x2 y2" << rotate_line.x2() << rotate_line.y2();

    QPoint p(x, y);
    return p;
}