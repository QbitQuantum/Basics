void RS_ActionInfoAngle::trigger() {

    RS_DEBUG->print("RS_ActionInfoAngle::trigger()");

    if (entity1!=NULL && entity2!=NULL) {
        RS_VectorSolutions sol =
            RS_Information::getIntersection(entity1, entity2, false);

        if (sol.hasValid()) {
            intersection = sol.get(0);

            if (intersection.valid && point1.valid && point2.valid) {
                double angle1 = intersection.angleTo(point1);
                double angle2 = intersection.angleTo(point2);
                double angle = RS_Math::rad2deg(remainder(angle2-angle1,2.*M_PI));

                QString str;
                str.setNum(angle);
                str += QChar(0xB0);
                if(angle<0.) {
                    QString str2;
                    str2.setNum(angle+360.); //positive value
                    str += QString(" or %1%2").arg(str2).arg(QChar(0xB0));
                }
                RS_DIALOGFACTORY->commandMessage(tr("Angle: %1").arg(str));
            }
        } else {
            RS_DIALOGFACTORY->commandMessage(tr("Lines are parallel"));
        }
    }
}