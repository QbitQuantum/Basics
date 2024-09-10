HBRUSH wf_create_brush(wfInfo * wfi, rdpBrush* brush, uint32 color, int bpp)
{
	int i;
	HBRUSH br;
	LOGBRUSH lbr;
	uint8* cdata;
	uint8 ipattern[8];
	HBITMAP pattern = NULL;

	lbr.lbStyle = brush->style;

	if (lbr.lbStyle == BS_DIBPATTERN || lbr.lbStyle == BS_DIBPATTERN8X8 || lbr.lbStyle == BS_DIBPATTERNPT)
		lbr.lbColor = DIB_RGB_COLORS;
	else
		lbr.lbColor = color;

	if (lbr.lbStyle == BS_PATTERN || lbr.lbStyle == BS_PATTERN8X8)
	{
		if (brush->bpp > 1)
		{
			pattern = wf_create_dib(wfi, 8, 8, bpp, brush->data, NULL);
			lbr.lbHatch = (ULONG_PTR) pattern;
		}
		else
		{
			for (i = 0; i != 8; i++)
				ipattern[7 - i] = brush->data[i];
	
			cdata = wf_glyph_convert(wfi, 8, 8, ipattern);
			pattern = CreateBitmap(8, 8, 1, 1, cdata);
			lbr.lbHatch = (ULONG_PTR) pattern;
			free(cdata);
		}
	}
	else if (lbr.lbStyle == BS_HATCHED)
	{
		lbr.lbHatch = brush->hatch;
	}
	else
	{
		lbr.lbHatch = 0;
	}

	br = CreateBrushIndirect(&lbr);
	SetBrushOrgEx(wfi->drawing->hdc, brush->x, brush->y, NULL);

	if (pattern != NULL)
		DeleteObject(pattern);

	return br;
}