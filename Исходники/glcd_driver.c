// Bresenham's algorithm - From wikipedia
void drawline(uint8_t *buff, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color) 
{
	uint8_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) 
	{
		swap(x0, y0);
		swap(x1, y1);
	}

	if (x0 > x1) 
	{
		swap(x0, x1);
		swap(y0, y1);
	}

	uint8_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int8_t err = dx / 2;
	int8_t ystep;

	if (y0 < y1) 
	{
		ystep = 1;
	} 
	else 
	{
		ystep = -1;
	}

	for (; x0<x1; x0++) 
	{
		if (steep) 
		{
			setpixel(buff, y0, x0, color);
		} 
		else 
		{
			setpixel(buff, x0, y0, color);
		}
		err -= dy;
		if (err < 0) 
		{
			y0 += ystep;
			err += dx;
		}
	}
}