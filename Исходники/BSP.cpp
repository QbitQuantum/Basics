CSGNode vol_subtraction(CSGNode &a, CSGNode &b) {

	if (a.numPolygons() == 0 || b.numPolygons() == 0) {
		return CSGNode(a);
	}

	a.invert();
	a.clipTo(b);
	b.clipTo(a);
	b.invert();
	b.clipTo(a);;
	b.invert();

	a.build(b.getAllPolygons());
	a.invert();
	return a;
}