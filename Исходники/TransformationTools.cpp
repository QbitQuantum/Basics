Transformation TransformationTools::axialMirrorAtALine(const Point& p1, const Point& p2)
{
	Point::euclidianVector_t c1 = p1.dehomogenize();
	Point::euclidianVector_t c2 = p2.dehomogenize();
	Point::euclidianVector_t c = c2 - c1;
	Transformation::scalar_t angle = atan2(c.y(), c.x());
	//transform line to x axis
	Transformation t = Transformation::Rotation(angle) * Transformation::Translation(-c1.x(), -c1.y());
	Transformation tInv = t.inverse();
	//mirror at x axis
	Transformation m = Transformation::Scaling(1, -1);
	//combine
	return tInv * m * t;
}