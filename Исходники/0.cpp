	bool isParallel(Segment &a) {
		Point left = p2 - p1;
		Point right = a.p2 - a.p1;
		return equals(left.cross(right), 0);
	}