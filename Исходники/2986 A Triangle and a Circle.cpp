double getArea(Point p[], int ptr, double r){
	double res = 0;
	for (int i = 1; i < ptr; i++){
		Point a = p[i - 1], b = p[i];
		if (isZero(a.distance(circle) - r) > 0 || isZero(b.distance(circle) - r) > 0){
			double angle = atan2(b.y, b.x) - atan2(a.y, a.x);
			while (isZero(angle - PI) > 0) angle -= PI * 2;
			while (isZero(angle + PI) < 0) angle += PI * 2;
			res += angle * r * r;
		}
		else
			res += circle.cross(a, b);
	}
	return res;
}