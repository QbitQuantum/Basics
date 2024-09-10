/*+/csubr/TOC/internal-------------------------------------------------------
* PlPOINTPlot - plot an array of POINT structures
*
* Purpose:
*		Plots an array of POINT structures.
*
*		If the number of points is 1, then PL_LINE... gets plotted as
*		though it were PL_POINT.
*
* Return Value:
*		PL_OK, or
*		other error codes
*
*-Date     Author		Revision
* -------- ------------	--------
* 09-27-95 R. Cole		created
*--------------------------------------------------------------------------*/
int
PlPOINTPlot(
PL_CTX	*pPlot,			// I pointer to plot context structure
HDC		hDC,			// I HDC
const RECT *pRectPts,	// I pointer to rect bounding points, or NULL
const POINT *aPts,		// I array of POINT structures
int		nPts,			// I number of array elements
int		eDrawType,		// I PL_LINE... or PL_POINT or PL_... mark
float	fPts,			// I drawing thickness or mark size, in points
COLORREF rgb)			// I color to use for drawing
{
	int		retStat=PL_OK;
	HBRUSH	hBrush=0, hOldBrush=0;
	HPEN	hPen=0, hOldPen=0;
	int		stat, j;
	RECT	rectPts;

	// If the caller has told us the RECT that bounds the points to be
	// drawn, check to see if the RECT (or a part of it) lies within
	// the area of the window that needs to be drawn.  If not, just
	// exit from this routine.
	if (pRectPts != NULL) {
		rectPts = *pRectPts;
		// Make the rect follow the Windows convention.
		rectPts.right += 1;
		rectPts.bottom += 1;

		if (pPlot->hRgnPaint != 0) {
			if (!RectInRegion(pPlot->hRgnPaint, &rectPts))
				goto done;
		}
		if (!RectVisible(hDC, &rectPts))
			goto done;
	}

	// Now draw the actual data points.  There is a separate section
	// here for each drawing type.  One of the overriding objectives
	// in how this is coded is to minimize the number of subroutine
	// calls.
	if (nPts >= 2 && eDrawType >= PL_LINE &&
					eDrawType <= PL_LINE_DASHDOTDOT) {
// Draw all "line" types.
		stat = Polyline(hDC, aPts, nPts);
		if (stat == 0) {
			// In some cases (not well understood), Polyline
			// fails.  When this happens, draw the line one
			// point at a time.
			MoveToEx(hDC, aPts[0].x, aPts[0].y, NULL);
			for (j=1; j<nPts; j++) 
				LineTo(hDC, aPts[j].x, aPts[j].y);
		}
		SetPixel(hDC, aPts[nPts-1].x, aPts[nPts-1].y, rgb);
	}
	else if (eDrawType >= PL_SQUARE && eDrawType <= PL_CROSS) {
// Draw all "plot mark" types.
		int		wid, ht;

		ht = PL_YPTS_TO_YPIX(fPts);
		wid = PL_XPTS_TO_XPIX(fPts);
		for (j=0; j<nPts; j++)  {
			retStat = PlDraw_discrete(pPlot, hDC,
				aPts[j].x, aPts[j].y,
				wid, ht, eDrawType,
				0, 0, 0, 0, 0, 0,
				rgb);
			if (retStat != PL_OK) goto done;
		}
	}
	else {
// Draw PL_POINT type.
		int		nX, nY;
		nX = PL_XPTS_TO_XPIX(fPts);
		nY = PL_YPTS_TO_YPIX(fPts);
		if (nX <= 1 && nY <= 1) {
			for (j=0; j<nPts; j++)
				SetPixel(hDC, aPts[j].x, aPts[j].y, rgb);
		}
		else {
			int		xL, xR, yB, yT;
			int		iHalfWid=(nX - 1)/2;
			int		iHalfHt=(nY - 1)/2;
			if ((hPen = CreatePen(PS_SOLID, 1, rgb)) == 0) goto gdi_error;
			/* KG */
			//hOldPen = SelectObject(hDC, hPen);
			hOldPen = (HPEN)SelectObject(hDC, hPen);
			if ((hBrush = CreateSolidBrush(rgb)) == 0) goto gdi_error;
			/* KG */
			//hOldBrush = SelectObject(hDC, hBrush);
			hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			for (j=0; j<nPts; j++)  {
				xL = aPts[j].x - iHalfWid;
				xR = xL + nX;
				yT = aPts[j].y - iHalfHt;
				yB = yT + nY;
				Ellipse(hDC, xL, yT, xR, yB);
			}
		}
	}

done:
	if (hOldPen != 0) SelectObject(hDC, hOldPen);
	if (hPen != 0) DeleteObject(hPen);
	if (hOldBrush != 0) SelectObject(hDC, hOldBrush);
	if (hBrush != 0) DeleteObject(hBrush);
	return retStat;

gdi_error:
	retStat = PL_GDI_FAIL;
	goto done;
}