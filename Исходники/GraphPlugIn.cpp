double CGraphPlugIn::Interpolate(cell c, bool horizontal)
{
	double d1, d2;
	
	if (GetCellDouble(c, &d1))
		return d1;
	
	if (horizontal)
	{
		cell c2 = c;
		c2.h--;
		if (!GetCellDouble(c2, &d1))
			d1 = Nan(1);
		c2.h += 2;
		if (!GetCellDouble(c2, &d2))
			d2 = Nan(1);
	}
	else
	{
		cell c2 = c;
		c2.h--;
		if (!GetCellDouble(c2, &d1))
			d1 = Nan(1);
		c2.h += 2;
		if (!GetCellDouble(c2, &d2))
			d2 = Nan(1);
	}
	
	if (!isnan(d1) && !isnan(d2))
		return (d1 + d2) / 2;
	else if (!isnan(d1))
		return d1;
	else
		return d2;
} // CGraphPlugIn::Interpolate