void Xiq::Draw(Matrix const &/*matrix*/)
{
	float x0 = location.x;
	float y0 = location.y;

	Time t = GetRoot()->TimeNow();
	float r = colors[0](t);
	float g = colors[1](t);
	float b = colors[2](t);
	Color color = GetRoot()->MakeColor(r,g,b);

	int ra = radius;
	if (ra < 0)
		ra *= -1;

	int f = 1 - ra;
	int ddF_x = 1;
	int ddF_y = -2 * ra;
	int x = 0;
	int y = ra;

	SetPixel(x0, y0 + ra, color);
	SetPixel(x0, y0 - ra, color);
	SetPixel(x0 + ra, y0, color);
	SetPixel(x0 - ra, y0, color);

	while (x < y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		SetPixel(x0 + x, y0 + y, color);
		SetPixel(x0 - x, y0 + y, color);
		SetPixel(x0 + x, y0 - y, color);
		SetPixel(x0 - x, y0 - y, color);
		SetPixel(x0 + y, y0 + x, color);
		SetPixel(x0 - y, y0 + x, color);
		SetPixel(x0 + y, y0 - x, color);
		SetPixel(x0 - y, y0 - x, color);
	}
}