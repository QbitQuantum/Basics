void Arena::ReDraw()
{
    Coord c1 = GetMemberOne()->GetCoord();
    Coord c2 = GetMemberTwo()->GetCoord();

    double tAngle;
    ArScene->removeItem(tr1);
    ArScene->removeItem(tr2);
    delete tr1;
    delete tr2;
    QPolygonF pg;

    //нужно определить координаты точек равнобедренного треугольника, учитывая угол
    triangle tr;
    tAngle = c1.Angle*_180_DIV_PI;
    tr.x1 = c1.X-20*sin(tAngle);
    tr.y1 = c1.Y-20*cos(tAngle);
    tr.x2 = c1.X+70*cos(tAngle);
    tr.y2 = c1.Y-70*sin(tAngle);
    tr.x3 = c1.X+20*sin(tAngle);
    tr.y3 = c1.Y+20*cos(tAngle);

    pg<< QPointF(tr.x1/_MULTIPLIER+_BORDER,tr.y1/_MULTIPLIER+_BORDER)
      <<QPointF(tr.x2/_MULTIPLIER+_BORDER,tr.y2/_MULTIPLIER+_BORDER)
      <<QPointF(tr.x3/_MULTIPLIER+_BORDER,tr.y3/_MULTIPLIER+_BORDER);
    tr1 = ArScene->addPolygon(pg, QPen(Qt::black),QBrush(Qt::white));
    pg.remove(0,3);

    tAngle = c2.Angle*_180_DIV_PI;
    tr.x1 = c2.X-20*sin(tAngle);
    tr.y1 = c2.Y-20*cos(tAngle);
    tr.x2 = c2.X+70*cos(tAngle);
    tr.y2 = c2.Y-70*sin(tAngle);
    tr.x3 = c2.X+20*sin(tAngle);
    tr.y3 = c2.Y+20*cos(tAngle);

    pg<< QPointF(tr.x1/_MULTIPLIER+_BORDER,tr.y1/_MULTIPLIER+_BORDER)
      <<QPointF(tr.x2/_MULTIPLIER+_BORDER,tr.y2/_MULTIPLIER+_BORDER)
      <<QPointF(tr.x3/_MULTIPLIER+_BORDER,tr.y3/_MULTIPLIER+_BORDER);
    tr2 = ArScene->addPolygon(pg, QPen(Qt::black),QBrush(Qt::white));

}