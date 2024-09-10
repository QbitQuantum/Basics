/**
 * @return Intersection between two lines.
 */
RS_VectorSolutions RS_Information::getIntersectionLineLine(RS_Line* e1,
        RS_Line* e2) {

    RS_VectorSolutions ret;

	if (!(e1 && e2)) {
		RS_DEBUG->print("RS_Information::getIntersectionLineLin() for nullptr entities");
        return ret;
    }

    RS_Vector p1 = e1->getStartpoint();
    RS_Vector p2 = e1->getEndpoint();
    RS_Vector p3 = e2->getStartpoint();
    RS_Vector p4 = e2->getEndpoint();

    double num = ((p4.x-p3.x)*(p1.y-p3.y) - (p4.y-p3.y)*(p1.x-p3.x));
    double div = ((p4.y-p3.y)*(p2.x-p1.x) - (p4.x-p3.x)*(p2.y-p1.y));

	if (fabs(div)>RS_TOLERANCE &&
			fabs(remainder(e1->getAngle1()-e2->getAngle1(), M_PI))>=RS_TOLERANCE*10.) {
		double u = num / div;

		double xs = p1.x + u * (p2.x-p1.x);
		double ys = p1.y + u * (p2.y-p1.y);
		ret = RS_VectorSolutions({RS_Vector(xs, ys)});
	}

    // lines are parallel
    else {
        ret = RS_VectorSolutions();
    }

    return ret;
}