long double
hypotl(long double x, long double y) {
	int n0, n1, n2, n3;
	long double t1, t2, y1, y2, w;
	int *px = (int *) &x, *py = (int *) &y;
	int *pt1 = (int *) &t1, *py1 = (int *) &y1;
	enum fp_direction_type rd;
	int j, k, nx, ny, nz;

	if ((*(int *) &one) != 0) {	/* determine word ordering */
		n0 = 0;
		n1 = 1;
		n2 = 2;
		n3 = 3;
	} else {
		n0 = 3;
		n1 = 2;
		n2 = 1;
		n3 = 0;
	}

	px[n0] &= 0x7fffffff;	/* clear sign bit of x and y */
	py[n0] &= 0x7fffffff;
	k = 0x7fff0000;
	nx = px[n0] & k;	/* exponent of x and y */
	ny = py[n0] & k;
	if (ny > nx) {
		w = x;
		x = y;
		y = w;
		nz = ny;
		ny = nx;
		nx = nz;
	}			/* force x > y */
	if ((nx - ny) >= 0x00730000)
		return (x + y);	/* x/y >= 2**116 */
	if (nx < 0x5ff30000 && ny > 0x205b0000) {	/* medium x,y */
		/* save and set RD to Rounding to nearest */
		rd = __swapRD(fp_nearest);
		w = x - y;
		if (w > y) {
			pt1[n0] = px[n0];
			pt1[n1] = px[n1];
			pt1[n2] = pt1[n3] = 0;
			t2 = x - t1;
			x = sqrtl(t1 * t1 - (y * (-y) - t2 * (x + t1)));
		} else {
			x = x + x;
			py1[n0] = py[n0];
			py1[n1] = py[n1];
			py1[n2] = py1[n3] = 0;
			y2 = y - y1;
			pt1[n0] = px[n0];
			pt1[n1] = px[n1];
			pt1[n2] = pt1[n3] = 0;
			t2 = x - t1;
			x = sqrtl(t1 * y1 - (w * (-w) - (t2 * y1 + y2 * x)));
		}
		if (rd != fp_nearest)
			(void) __swapRD(rd);	/* restore rounding mode */
		return (x);
	} else {
		if (nx == k || ny == k) {	/* x or y is INF or NaN */
			if (isinfl(x))
				t2 = x;
			else if (isinfl(y))
				t2 = y;
			else
				t2 = x + y;	/* invalid if x or y is sNaN */
			return (t2);
		}
		if (ny == 0) {
			if (y == zero || x == zero)
				return (x + y);
			t1 = scalbnl(one, 16381);
			x *= t1;
			y *= t1;
			return (scalbnl(one, -16381) * hypotl(x, y));
		}
		j = nx - 0x3fff0000;
		px[n0] -= j;
		py[n0] -= j;
		pt1[n0] = nx;
		pt1[n1] = pt1[n2] = pt1[n3] = 0;
		return (t1 * hypotl(x, y));
	}
}