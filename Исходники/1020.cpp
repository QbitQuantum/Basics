int main() {
	int n, i;
	float r, x, y, x1, y1, x2, y2, s;
	scanf("%d%f%f%f", &n, &r, &x, &y);
	x1 = x2 = x;
	y1 = y2 = y;
	s = 0;
	for (i = 1; i < n; i++) {
		scanf("%f%f", &x2, &y2);
		s += hypotf(x1 - x2, y1 - y2);
		x1 = x2;
		y1 = y2;
	}
	s += hypotf(x2 - x, y2 - y) + 2 * acos(-1) * r;
	printf("%.2f\n", s);
}