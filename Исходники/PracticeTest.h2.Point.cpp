double area( const Point & a, const Point & b, const Point & c ){ //special area function. returns 0 if the three points lie in a straight line.
	double s; //triangle perimeter
	
	if (((b.getY() - a.getY()) / (b.getX() - a.getX())) != ((c.getY() - b.getY()) / (c.getX() - b.getX()))){
		s = (a.distance(b) + b.distance(c) + c.distance(a)) / 2;
		//cout << "(" << a.distance(b) << " + " << b.distance(c) << " + " << c.distance(a) << ") / 2 = " << perimeter << endl;
		return sqrt(s * (s - a.distance(b)) * (s - b.distance(c)) * (s - c.distance(a))); //Heron's formula
	} else {
		//cout << "These three points lie in a straight line" << endl;
		return 0;
	}
}