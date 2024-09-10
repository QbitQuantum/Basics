void DrawMapBoundsPoly (CMap* theMap, PolyObjectHdl MapPolyHdl, DrawSpecRecPtr drawSettings, Boolean erasePolygon)
{
	long numPts = (**MapPolyHdl).pointCount;
	POINT **pointsH = (POINT**)_NewHandle(numPts *sizeof(POINT));
	POINT *pointsPtr = (POINT*)_NewPtr(numPts *sizeof(POINT));
	LongPoint** thisPointsHdl=nil;
	Point pt;
	LongPoint wPt;
	long i;
	Boolean offQuickDrawPlane = false;
	RGBColor saveColor; // JLM ?? wouldn't compile without this
	if(!pointsH || !pointsPtr) {SysBeep(5); return;}
	
	thisPointsHdl = (LongPoint**) (**MapPolyHdl).objectDataHdl;
	for(i = 0; i< numPts;i++)
	{
		wPt = INDEXH(thisPointsHdl,i);
		pt = GetQuickDrawPt(wPt.h,wPt.v,&gRect,&offQuickDrawPlane);
		INDEXH(pointsH,i) = MakePOINT(pt.h,pt.v);
		(pointsPtr)[i] = MakePOINT(pt.h,pt.v);
		// code goes here, make sure this point does not equal previous point JLM
	}
	GetForeColor (&saveColor);		/* save original forecolor */

		if (erasePolygon)
		{
			RgnHandle newClip=0;
			HBRUSH whiteBrush;
			newClip = CreatePolygonRgn((const POINT*)pointsPtr,numPts,ALTERNATE);
			whiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
			//err = SelectClipRgn(currentHDC,savedClip);
			FillRgn(currentHDC, newClip, whiteBrush);
			//DeleteObject(newClip);
			DisposeRgn(newClip);
			//SelectClipRgn(currentHDC,0);
		}
		else
		{
			POINT p[2];
			p[0] = INDEXH(pointsH,numPts-1);
			p[1] = INDEXH(pointsH,0);
			RGBForeColor(&colors[BLACK]);
			if(numPts >= 2) 
			{
				Polyline(currentHDC,*pointsH,numPts);
				Polyline(currentHDC,p,2);	// close the polygon
			}
		}

	RGBForeColor (&saveColor);
	DisposeHandle((Handle)pointsH);
	if(pointsPtr) {_DisposePtr((Ptr)pointsPtr); pointsPtr = 0;}
}