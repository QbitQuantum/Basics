BOOL bcg_CS_clip(const CBCGPRect& rect, CBCGPPoint& point1, CBCGPPoint& point2)
{
	if (rect.IsRectEmpty ())
	{
		return TRUE;
	}

	if (point1 == point2)
	{
		return rect.PtInRect(point1);
	}

	int code1 = bcg_CS_code(rect, point1);
	int code2 = bcg_CS_code(rect, point2);

	double kx = 0.0;
	double ky = 0.0;
	CBCGPSize d(point2.x - point1.x, point2.y - point1.y);
	if (d.cx != 0.0)
	{
		ky = d.cy / d.cx;
	}
	else if (d.cy == 0.0)
	{
		if (code1 == 0 && code2 == 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	if (d.cy != 0.0)
	{
		kx = d.cx / d.cy;
	}

	BOOL visible = FALSE;
	CBCGPPoint pt1(point1);
	CBCGPPoint pt2(point2);

	int count_inv = 0;

	for(int i = 0; i < 4; i++)
	{
		if (code1 & code2)
		{
			break;
		}
		else if (code1 == 0 && code2 == 0)
		{
			visible = TRUE;
			break;
		}

		if (code1 == 0)
		{
			int c = code1;
			code1 = code2;
			code2 = c;

			CBCGPPoint p(pt1);
			pt1 = pt2;
			pt2 = p;

			count_inv++;
		}

		if (code1 & 0x01)
		{
			pt1.y += ky * (rect.left - pt1.x);
			pt1.x = rect.left;
		}
		else if (code1 & 0x02)
		{
			pt1.y += ky * (rect.right - pt1.x);
			pt1.x = rect.right;
		}
		else if (code1 & 0x04)
		{
			pt1.x += kx * (rect.top - pt1.y);
			pt1.y = rect.top;
		}
		else if (code1 & 0x08)
		{
			pt1.x += kx * (rect.bottom - pt1.y);
			pt1.y = rect.bottom;
		}

		code1 = bcg_CS_code(rect, pt1);
	}

	if (visible)
	{
		if ((count_inv % 2) != 0)
		{
			point1 = pt1;
			point2 = pt2;
		}
		else
		{
			point1 = pt2;
			point2 = pt1;
		}
	}

	return visible;
}