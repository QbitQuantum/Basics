void drawRectangle(int x, int y, int width, int height)
{
	POINT point[5];
	point[0].x = x;
	point[0].y = y;

	point[1].x = x + width;
	point[1].y = y;

	point[2].x = x + width;
	point[2].y = y + height;

	point[3].x = x;
	point[3].y = y + height;

	point[4].x = x;
	point[4].y = y;

	Polyline(_paintDC, point, 5);
}