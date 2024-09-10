void POLY::borrarpoly() {
	int t;
	t = getcolor();
	setcolor (getbkcolor() );
	drawpoly (n, puntos);
	setcolor(t);
}