bool BrLine::intersects(BrLine& line) const{
    //il y a une intersection entre deux lignes si elles sont reliées au même
    //point, du coup, on teste l'intersection avec une courbe de bezier sans
    //les deux points extrêmes
    QPainterPath* withoutPoints = new QPainterPath(_line->pointAt(0.000000001));
    withoutPoints->cubicTo(_contr->coord(), _contr->coord(), _line->pointAt(0.999999999));
    return withoutPoints->intersects(line.bezierCurve());
}