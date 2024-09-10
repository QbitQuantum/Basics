boolean MultiLineObj::Intersects (LineObj& l) {
    register int i;
    BoxObj b;
    
    GetBox(b);
    if (b.Intersects(l)) {
	for (i = 1; i < _count; ++i) {
            LineObj test(_x[i-1], _y[i-1], _x[i], _y[i]);

	    if (l.Intersects(test)) {
	        return true;
	    }
	}
    }    
    return false;
}