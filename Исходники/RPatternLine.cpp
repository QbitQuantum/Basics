RPainterPath RPatternLine::getPainterPath() const {
    RPainterPath p;

    RVector cursor(0,0);
    p.moveTo(cursor);

    // continuous:
    if (dashes.length()==0) {
        cursor += RVector::createPolar(10.0, angle);
        p.lineTo(cursor);
    }
    else {
        for (int i=0; i<dashes.length(); i++) {
            double dash = dashes[i];
            cursor += RVector::createPolar(qAbs(dash), angle);
            if (dash<0) {
                p.moveTo(cursor);
            }
            else {
                p.lineTo(cursor);
            }
        }
    }

    return p;
}