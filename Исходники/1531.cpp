void marge(const int x, const int y) {
	father[getAncestor(x)] = getAncestor(y);
}