DocReport& DocReport::SetPageSize(int cx, int cy) {
	pgsz = Size(cx, cy);
	StartPage();
	return *this;
}