/* MapLine::dirTabPoint
 * Calculates and returns the end point of the 'direction tab' for
 * the line (used as a front side indicator for 2d map display)
 *******************************************************************/
fpoint2_t MapLine::dirTabPoint(double tablen)
{
	// Calculate midpoint
	fpoint2_t mid(x1() + ((x2() - x1()) * 0.5), y1() + ((y2() - y1()) * 0.5));

	// Calculate tab length
	if (tablen == 0)
	{
		tablen = getLength() * 0.1;
		if (tablen > 16) tablen = 16;
		if (tablen < 2) tablen = 2;
	}

	// Calculate tab endpoint
	if (front_vec.x == 0 && front_vec.y == 0) frontVector();
	return fpoint2_t(mid.x - front_vec.x*tablen, mid.y - front_vec.y*tablen);
}