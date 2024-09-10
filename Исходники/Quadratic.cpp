quadratic operator*(double r, const quadratic& q)
{
	quadratic qnew;
	qnew.setA(r*q.getA());
	qnew.setB(r*q.getB());
	qnew.setC(r*q.getC());

	return qnew;
}