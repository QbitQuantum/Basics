void DrawSymbol(CDC *pDC, int x, int y, int length, int width, COLORREF color, DSYMBOL symbol, bool bFill, int angle)
{
	//TRACE("Entering CGraphLine::DrawSymbol\n");
	int l = length;		// velkost krizika
	double PI = 3.1415926535897932384626433832795;

	CPen pen, *pPen;
	pen.CreatePen(PS_SOLID, width, color);
	pPen = pDC->SelectObject(&pen);
	if(symbol == CROSS) {
		pDC->MoveTo(x+l, y);
		pDC->LineTo(x-l, y);
		pDC->MoveTo(x, y+l);
		pDC->LineTo(x, y-l);
		return;
	}
	if(symbol == ARROW) {
		pDC->MoveTo(x, y);
		int xx = int (x + 3*l*cos(angle/10*PI/180)),
			yy = int (y + 3*l*sin(angle/10*PI/180));
		pDC->LineTo(xx, yy);
		return;
	}
	if( (symbol == CIRCLE) || (symbol == RECTANGLE)) {
		LOGBRUSH logBrush;
		if(bFill) {
			logBrush.lbStyle = BS_SOLID;
		}
		else {
			logBrush.lbStyle = BS_HOLLOW;
		}
		logBrush.lbColor = color;
		logBrush.lbHatch = HS_CROSS;

		CBrush brush;
		brush.CreateBrushIndirect(&logBrush);
		CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&brush);
		
		if(symbol == CIRCLE) {
			pDC->Ellipse(x-l, y-l, x+l, y+l);
		}
		
		if(symbol == RECTANGLE) {
			pDC->Rectangle(x-l, y-l, x+l, y+l);
		}
		
		pDC->SelectObject(pOldBrush);
	}
	pDC->SelectObject( pPen );
}