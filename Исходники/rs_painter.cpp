void RS_Painter::drawHandle(const RS_Vector& p, const RS_Color& c, int size) {
	if (size<0) {
		size = 2;
	}
	fillRect((int)(p.x-size), (int)(p.y-size), 2*size, 2*size, c);
}