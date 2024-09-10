static HPEN CreatePenFromStyle(COLORREF cl, int nLineWidth, int nLineStyle, DWORD dwCaps)
{
	LOGBRUSH lb;

	lb.lbStyle = BS_SOLID;
	lb.lbColor = cl;
	lb.lbHatch = 0;

	switch(nLineStyle) {
		case 0:
		default:
			return ExtCreatePen(PS_GEOMETRIC | PS_SOLID | dwCaps,
			  MAX(1, nLineWidth), &lb, 0, NULL);

		case 1:
			return ExtCreatePen(PS_COSMETIC | PS_ALTERNATE | dwCaps,
			  MAX(1, 1), &lb, 0, NULL);

		case 2:
			return ExtCreatePen(PS_COSMETIC | PS_DOT | dwCaps,
			  MAX(1, 1), &lb, 0, NULL);

		case 3:				// Custom style
			{
				DWORD dwStyle[] = {2, 1};
				return ExtCreatePen(PS_COSMETIC | PS_USERSTYLE | dwCaps,
				  MAX(1, 1), &lb, 2, (CONST DWORD *)&dwStyle);
			}

		case 4:				// Custom style
			{
				DWORD dwStyle[] = {2, 2};
				return ExtCreatePen(PS_COSMETIC | PS_USERSTYLE | dwCaps,
				  MAX(1, 1), &lb, 2, (CONST DWORD *)&dwStyle);
			}

		case 5:				// Custom style
			{
				DWORD dwStyle[] = {3, 1};
				return ExtCreatePen(PS_COSMETIC | PS_USERSTYLE | dwCaps,
				  MAX(1, 1), &lb, 2, (CONST DWORD *)&dwStyle);
			}

		case 6:				// Custom style
			{
				DWORD dwStyle[] = {4, 1};
				return ExtCreatePen(PS_COSMETIC | PS_USERSTYLE | dwCaps,
				  MAX(1, 1), &lb, 2, (CONST DWORD *)&dwStyle);
			}

		case 7:
			return ExtCreatePen(PS_COSMETIC | PS_DASH | dwCaps,
			  MAX(1, 1), &lb, 0, NULL);

		case 8:
			return ExtCreatePen(PS_COSMETIC | PS_DASHDOT | dwCaps,
			  MAX(1, 1), &lb, 0, NULL);

		case 9:
			return ExtCreatePen(PS_COSMETIC | PS_DASHDOTDOT | dwCaps,
			  MAX(1, 1), &lb, 0, NULL);
	}
}