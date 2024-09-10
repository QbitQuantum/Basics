void draw_rect(int x, int y, int w, int h, COLORREF c)
{
	HPEN   pn, po;
	HBRUSH br, bo;

	if(w == 1 && h == 1)
	{
		SetPixelV(dc, x, y, intensecolors ? c : col_bar_line);

	}else{

		if(!intensecolors)
		{
			if(c)
			{
				pn = CreatePen(PS_SOLID, 1, col_bar_line);
				br = CreateSolidBrush(col_bar_fill);
			}else{
				pn = CreatePen(PS_SOLID, 1, 0);
				br = CreateSolidBrush(0);
			}
		}else{
			if(w != 1)
				pn = CreatePen(PS_SOLID, 1, 0);
			else
				pn = CreatePen(PS_SOLID, 1, c );
			br = CreateSolidBrush(c);
		}
		
		po = (HPEN) SelectObject(dc, pn);
		bo = (HBRUSH) SelectObject(dc, br);

		Rectangle(dc, x, y, x + w, y + h);

		SelectObject(dc, po);
		SelectObject(dc, bo);

		DeleteObject(pn);
		DeleteObject(br);
	}
}