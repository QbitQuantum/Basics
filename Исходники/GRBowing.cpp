/** \brief Draws a slur.

	(JB) experimental modifications to original code

	It takes 3 control points x1,y1,x2,y2,x3,y3 and draws a curv from x1, y1
	through x2,y2 (approximately) to x3, y3.  The thickness of the slur is
	set by SLUR_THICKNESS (1 - 10)
*/
void drawSlur(VGDevice & hdc, float x1, float y1, float x2, float y2,
								float x3, float y3, float inflexion )
{
	float delx1, delx2, ratio;
	float addY2, addX, addY, x2a, y2a, x2b, y2b;
	float maxD;//, h1, h2;

	// if start and endpoint is the same, just don't do anything.
	// this is a hack, whatsoever, because this should not really happen!
	if (x1==x3) return;

	const float oneOverDeltaX = (1.0f / (x3 - x1));

	maxD = (SLUR_THICKNESS * 1.25f);
	ratio = (y3 - y1) * oneOverDeltaX;
	addY2 = (y2 - y1) / 3;
	addX = (x3 - x1) / (2 + inflexion);	// defines the attack of the curve.
	addY = addX * ratio;
	x2a = x2 - addX;
	y2a = y2 - addY + addY2;
	x2b = x2 + addX;
	y2b = y2 - addY + addY2;
//	h1 = (y2a > y1) ? (y2a - y1) : (y1 - y2a);
//	h2 = (y2b > y3) ? (y2b - y3) : (y3 - y2b);
//	if (x2a - x1 > h1) x2a = x1 + h1;
//	if (x3 - x2b > h2) x2b = x3 - h2;
	delx1 = ((y3 - y1) * SLUR_THICKNESS) * oneOverDeltaX;
	delx2 = ((y3 - y1) * SLUR_THICKNESS) * oneOverDeltaX;
	if (delx1 > maxD) delx1 = maxD;
	if (delx2 > maxD) delx2 = maxD;
	if (delx1 < -maxD) delx1 = -maxD;
	if (delx2 < -maxD) delx2 = -maxD;

	const int ptCount = (2 * ( NSEGS + 3 ));

	NVPoint thePoints[ ptCount ]; //ptCount ];

	// CALCULATE THE FIRST CURVE
	// PROBABLY YOU WANT TO START A POLYGON NOW
	int index = 0;
	makeCurve( x1, y1, x2a, y2a, x2b, y2b, x3, y3, NSEGS, thePoints, &index );

	y2a = (y2a < y1 ? y2a + SLUR_THICKNESS : y2a - SLUR_THICKNESS);
	y2b = (y2b < y3 ? y2b + SLUR_THICKNESS : y2b - SLUR_THICKNESS);
	x2a += delx1;
	x2b += delx2;

	// CALCULATE THE SECOND CURVE
	makeCurve( x3, y3, x2b, y2b, x2a, y2a, x1, y1, NSEGS, thePoints, &index );

	//PROBABLY YOU WANT TO CLOSE THE POLYGON NOW AND FILL IT
	float xPoints [ ptCount ];
	float yPoints [ ptCount ];
	for( int currPt = 0; currPt < index; ++ currPt )
	{
		xPoints [ currPt ] = thePoints[ currPt ].x;
		yPoints [ currPt ] = thePoints[ currPt ].y;
	}

	hdc.Polygon( xPoints, yPoints, index );

	/* - DEBUG ->
	hdc.PushPen( GColor( 200, 0, 0 ), 5 );

	hdc.Line( x1 - 20, y1 - 20, x1 + 20, y1 + 20);
	hdc.Line( x1 - 20, y1 + 20, x1 + 20, y1 - 20);

	hdc.PushPen( GColor( 200, 0, 200 ), 5 );
	hdc.Line( x2 - 20, y2 - 20, x2 + 20, y2 + 20);
	hdc.Line( x2 - 20, y2 + 20, x2 + 20, y2 - 20);
	hdc.PopPen();

	hdc.Line( x2a - 20, y2a - 20, x2a + 20, y2a + 20);
	hdc.Line( x2a - 20, y2a + 20, x2a + 20, y2a - 20);

	hdc.Line( x2b - 20, y2b - 20, x2b + 20, y2b + 20);
	hdc.Line( x2b - 20, y2b + 20, x2b + 20, y2b - 20);

	hdc.Line( x3 - 20, y3 - 20, x3 + 20, y3 + 20);
	hdc.Line( x3 - 20, y3 + 20, x3 + 20, y3 - 20);


	hdc.PopPen();
	// <- */
}