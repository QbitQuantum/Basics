void LaserStatusDialog::DrawTemperaturePointer(POINT &StartLoc, HDC hdc)
{
	int PointerHeight=20;
	int PointerWidth=52;
	int PointerOffset=5;

	POINT ptArray[6];
	ptArray[0]=StartLoc;

	ptArray[1].x=StartLoc.x+PointerOffset;
	ptArray[1].y=StartLoc.y-PointerHeight/2;

	ptArray[2].x=ptArray[1].x+PointerWidth;
	ptArray[2].y=ptArray[1].y;

	ptArray[3].x=ptArray[2].x;
	ptArray[3].y=StartLoc.y+PointerHeight/2;

	ptArray[4].x=ptArray[1].x;
	ptArray[4].y=ptArray[3].y;


	ptArray[5]=StartLoc;

	RECT PolyTextZone;
	PolyTextZone.top=ptArray[1].y+2;
	PolyTextZone.left=ptArray[1].x;
	PolyTextZone.bottom=ptArray[3].y;
	PolyTextZone.right=ptArray[3].x;

	int OldPolyFillMode=SetPolyFillMode(hdc,WINDING);
	//Polyline (hdc, ptArray,6 );
	//PolyDraw(hdc,ptArray,PT_CLOSEFIGURE,6);
	Polygon(hdc,ptArray,6);
	
	SetPolyFillMode(hdc,OldPolyFillMode);

	char TempText[20];
	sprintf_s(TempText,"%.1f°C",m_dCurrentTempCelsius);

	

	DrawTempatureScaleText(hdc,PolyTextZone,TempText);


}