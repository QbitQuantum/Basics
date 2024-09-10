/*-------------------------------------------------------------------*
 |  DimLinear                                                        |
 |  Inputs:                                                          |
 |      PDRAWING pDrawing = pointer to the current DRAWING structure |
 |      OBJHANDLE BlockObjhandle = handle of block that entity must  |
 |                        be added in it. (NULL = Entity Section)    |
 |      PENTITYHEADER pDimHeader = pointer to dim data header        |
 |      PENTDIMENSION pDimension = pointer to dim data structure     |
 |      PDIMSTYLE pDimStyle = pointer of dim-style structure         |
 |  Output: TRUE if everything is ok                                 |
 *-------------------------------------------------------------------*/
BOOL DimLinear( PDRAWING pDrawing, OBJHANDLE BlockObjhandle, PENTITYHEADER pDimHeader, PENTDIMENSION pDimension, PDIMSTYLE pDimStyle )
{
	BOOL			result;
	double			TextWidth;
	double			a, a1, a2, a3;
	double			sina1, cosa1;
	double			sina2, cosa2;
	REALPOINT		A1, A2, A3;
	REALPOINT		B1, B2, B3;
	REALPOINT		C1, C2, C3;
	double			pi = 3.1415926535;

	double			x1 = pDimension->DefPoint3.x;			// x position of start point
	double			y1 = pDimension->DefPoint3.y;			// y position of start point
	double			x2 = pDimension->DefPoint4.x;			// x position of end point
	double			y2 = pDimension->DefPoint4.y;			// y position of end point
	double			x3 = pDimension->DimLineDefPoint.x;		// x position of dimension line
	double			y3 = pDimension->DimLineDefPoint.y;		// y position of dimension line
	double			angle = pDimension->DimRotationAngle;	// dim-line's rotation angle
	LPCTSTR			text = pDimension->DimText;				// dim-line's text (dafault is NULL)

	ENTITYHEADER	EntityHeader;
	ENTPOINT		Point;
	ENTLINE			Line;
	ENTTEXT			Text;

	memcpy(&EntityHeader, pDimHeader, sizeof(ENTITYHEADER));
	// Writting dimension data to the drawing  ---------------------
	result = TRUE;

	a = tan( angle*pi/180 );
	if(a!=0)
	{
		A1.x = (y1 - y3 + x1/a + a*x3) / (a + 1/a);
		A1.y = a * (A1.x - x3) + y3;
		B1.x = (y2 - y3 + x2/a + a*x3) / (a + 1/a);
		B1.y = a * (B1.x - x3) + y3;

		a1 = (A1.y - y1) / (A1.x - x1);
		sina1 = (A1.x>x1 ? 1 : -1) * sin( atan(a1) );
		cosa1 = (A1.x>x1 ? 1 : -1) * cos( atan(a1) );
		A2.x = A1.x + cosa1*pDimStyle->dimexe;
		A2.y = A1.y + sina1*pDimStyle->dimexe;
		A3.x = x1 + cosa1*pDimStyle->dimexo;
		A3.y = y1 + sina1*pDimStyle->dimexo;

		a2 = (B1.y - y2) / (B1.x - x2);
		sina2 = (B1.x>x2 ? 1 : -1) * sin( atan(a2) );
		cosa2 = (B1.x>x2 ? 1 : -1) * cos( atan(a2) );
		B2.x = B1.x + cosa2*pDimStyle->dimexe;
		B2.y = B1.y + sina2*pDimStyle->dimexe;
		B3.x = x2 + cosa2*pDimStyle->dimexo;
		B3.y = y2 + sina2*pDimStyle->dimexo;
	}
	else
	{
		A1.x = x1;
		A1.y = y3;
		B1.x = x2;
		B1.y = y3;

		A2.x = A1.x;
		A2.y = A1.y + _copysign(pDimStyle->dimexe, A1.y-y1);
		A3.x = x1;
		A3.y = y1 + _copysign(pDimStyle->dimexo, A1.y-y1);

		B2.x = B1.x;
		B2.y = B1.y + _copysign(pDimStyle->dimexe, B1.y-y2);
		B3.x = x2;
		B3.y = y2 + _copysign(pDimStyle->dimexo, B1.y-y2);
	}

	C1.x = (A1.x + B1.x) / 2;
	C1.y = (A1.y + B1.y) / 2;

	// Begin & End Points ----
	EntityHeader.EntityType = ENT_POINT;
	Point.Point0.x = x1; Point.Point0.y = y1;
	drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Point);
	Point.Point0.x = x2; Point.Point0.y = y2;
	drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Point);

	// Dimension Line ----
	EntityHeader.Color = pDimStyle->dimclrd;

	switch(pDimStyle->dimtad)
	{
	case 0: // Centered
		// At this time the program cannot calculate the exact width of the text
		TextWidth = (strlen(text) * pDimStyle->dimtxt * 0.3) + pDimStyle->dimgap*2;
		C2.x = C1.x + _copysign( cos(angle*pi/180), A1.x-B1.x)*TextWidth;
		C2.y = C1.y + _copysign( sin(angle*pi/180), A1.x-B1.x)*TextWidth;
		C3.x = C1.x + _copysign( cos(angle*pi/180), B1.x-A1.x)*TextWidth;
		C3.y = C1.y + _copysign( sin(angle*pi/180), B1.x-A1.x)*TextWidth;

		EntityHeader.EntityType = ENT_LINE;
		Line.Point0.x = A1.x; Line.Point0.y = A1.y;
		Line.Point1.x = C2.x; Line.Point1.y = C2.y;
		drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Line);
		Line.Point0.x = C3.x; Line.Point0.y = C3.y;
		Line.Point1.x = B1.x; Line.Point1.y = B1.y;
		drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Line);

		// Text
		EntityHeader.Color = pDimStyle->dimclrt;

		EntityHeader.EntityType = ENT_TEXT;
		Text.Point0.x = C1.x; Text.Point0.y = C1.y;
		Text.TextData.SecondAlignmentPoint.x = C1.x; Text.TextData.SecondAlignmentPoint.y = C1.y;
		Text.TextData.Height = pDimStyle->dimtxt;
		Text.TextData.RotationAngle = angle;
		Text.TextData.Justification = TJ_MIDDLE;
		Text.TextData.WidthFactor = 0;
		Text.TextData.TextStyleObjhandle = pDimStyle->dimtxstyObjhandle;
		strcpy(Text.strText, pDimension->DimText);
		drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Text);
		break;
	case 1: // Above
		EntityHeader.EntityType = ENT_LINE;
		Line.Point0.x = A1.x; Line.Point0.y = A1.y;
		Line.Point1.x = B1.x; Line.Point1.y = B1.y;
		drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Line);
		// Text
		EntityHeader.Color = pDimStyle->dimclrt;

		EntityHeader.EntityType = ENT_TEXT;
		Text.Point0.x = C1.x + cos((angle+90)*pi/180)*(pDimStyle->dimgap+pDimStyle->dimtxt/2);
		Text.Point0.y = C1.y + sin((angle+90)*pi/180)*(pDimStyle->dimgap+pDimStyle->dimtxt/2);
		Text.TextData.SecondAlignmentPoint.x = Text.Point0.x;
		Text.TextData.SecondAlignmentPoint.y = Text.Point0.y;
		Text.TextData.Height = pDimStyle->dimtxt;
		Text.TextData.RotationAngle = angle;
		Text.TextData.Justification = TJ_MIDDLE;
		Text.TextData.WidthFactor = 0;
		Text.TextData.TextStyleObjhandle = pDimStyle->dimtxstyObjhandle;
		strcpy(Text.strText, pDimension->DimText);
		drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Text);
		break;
	}

	// Arrow Heads ----
	EntityHeader.Color = pDimStyle->dimclrd;

	a3 = (B1.y - A1.y) / (B1.x - A1.x);

	if(B1.x>A1.x)
	{
		// 1st Arrow Head
		result &= dimDrawArrowHead( pDrawing, BlockObjhandle, &EntityHeader, A1.x, A1.y, pi+atan(a3), pDimStyle->dimasz, pDimStyle->dimblk1, 1 );
		// 2nd Arrow Head
		result &= dimDrawArrowHead( pDrawing, BlockObjhandle, &EntityHeader, B1.x, B1.y, atan(a3), pDimStyle->dimasz, pDimStyle->dimblk2, 2 );
	}
	else if(B1.x<A1.x)
	{
		// 1st Arrow Head
		result &= dimDrawArrowHead( pDrawing, BlockObjhandle, &EntityHeader, A1.x, A1.y, atan(a3), pDimStyle->dimasz, pDimStyle->dimblk1, 1 );
		// 2nd Arrow Head
		result &= dimDrawArrowHead( pDrawing, BlockObjhandle, &EntityHeader, B1.x, B1.y, pi+atan(a3), pDimStyle->dimasz, pDimStyle->dimblk2, 2 );
	}
	else // (B1.x==A1.x)
	{
		// 1st Arrow Head
		result &= dimDrawArrowHead( pDrawing, BlockObjhandle, &EntityHeader, A1.x, A1.y, (B1.y>A1.y?0:1)*pi+atan(a3), pDimStyle->dimasz, pDimStyle->dimblk1, 1 );
		// 2nd Arrow Head
		result &= dimDrawArrowHead( pDrawing, BlockObjhandle, &EntityHeader, B1.x, B1.y, (B1.y>A1.y?1:0)*pi+atan(a3), pDimStyle->dimasz, pDimStyle->dimblk2, 2 );
	}

	// Extension Lines ----
	EntityHeader.Color = pDimStyle->dimclre;
	// 1st Extension Line
	EntityHeader.EntityType = ENT_LINE;
	Line.Point0.x = A2.x; Line.Point0.y = A2.y;
	Line.Point1.x = A3.x; Line.Point1.y = A3.y;
	drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Line);
	// 2nd Extension Line
	EntityHeader.EntityType = ENT_LINE;
	Line.Point0.x = B2.x; Line.Point0.y = B2.y;
	Line.Point1.x = B3.x; Line.Point1.y = B3.y;
	drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Line);

	return result;
}