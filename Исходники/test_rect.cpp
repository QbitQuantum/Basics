void test_rect_intersects(Rect<int> r1, Rect<int> r2, bool expected)
{
	if (r1.intersects(r2) != expected)
	{
		LogError("Rect {%d,%d},{%d,%d} incorrectly %s rect {%d,%d},{%d,%d}", r2.p0.x, r2.p0.y,
		         r2.p1.x, r2.p1.y, expected ? "does not intersect" : "intersects", r1.p0.x, r1.p0.y,
		         r1.p1.x, r1.p1.y);
		exit(EXIT_FAILURE);
	}
}