int		LinkTimeControl::PaintFCurves( ParamDimensionBase *dim, HDC hdc, Rect& rcGraph, Rect& rcPaint,
			float tzoom, int tscroll, float vzoom, int vscroll, DWORD flags )
{
	const int n = NumKeys();
	if ( n == 0 )
		return 0;

	Interval valid;
	int h = rcGraph.h()-1;
	HPEN dpen,spen;
	BOOL init=FALSE;		
	Interval range = GetTimeRange(TIMERANGE_ALL);	
	SetBkMode(hdc,TRANSPARENT);	

	dpen = CreatePen(PS_DOT,0,GetColorManager()->GetColor(kFunctionCurveFloat));
	spen = CreatePen(PS_SOLID,0,GetColorManager()->GetColor(kFunctionCurveFloat));

	SIZE size;
	GetTextExtentPoint( hdc, _T("0"), 1, &size );

	float val;
	TimeValue leftTime = ScreenToTime(rcPaint.left,tzoom,tscroll);
	TimeValue rightTime = ScreenToTime(rcPaint.right,tzoom,tscroll);
	int x, y;

	// dotted line to left of keys
	if ( leftTime < range.Start() )
	{
		SelectObject(hdc,dpen);
		GetValue(range.Start(),&val,valid);
		y = ValueToScreen(dim->Convert(val),h,vzoom,vscroll);
		MoveToEx(hdc,rcPaint.left,y,NULL);
		LineTo(hdc,TimeToScreen(range.Start(),tzoom,tscroll),y);
	}

	SelectObject(hdc,spen);

	// first node text
	{
		TimeValue t = GetKeyTime( 0 );
		if ( t >= leftTime && t <= rightTime )
		{
			GetValue(t,&val,valid);
			y = ValueToScreen(dim->Convert(val),h,vzoom,vscroll);
			x = TimeToScreen(t,tzoom,tscroll);
			INode* node = fOwner->GetNode( 0 );
			DLTextOut( hdc, x, y-1-size.cy, node ? node->GetName() : _T("World") );
		}
	}

	// solid line between keys
	for ( int i=1; i<n; ++i )
	{
		TimeValue t0 = GetKeyTime( i-1 );
		TimeValue t1 = GetKeyTime( i );
		if ( t1 < leftTime || t0 > rightTime )
			continue;
		GetValue(t0,&val,valid);
		y = ValueToScreen(dim->Convert(val),h,vzoom,vscroll);
		MoveToEx(hdc,TimeToScreen(t0,tzoom,tscroll),y,NULL);
		x = TimeToScreen(t1,tzoom,tscroll);
		LineTo(hdc,x,y);
		GetValue(t1,&val,valid);
		y = ValueToScreen(dim->Convert(val),h,vzoom,vscroll);
		LineTo(hdc,x,y);

		INode* node = fOwner->GetNode( i );
		DLTextOut( hdc, x, y-1-size.cy, node ? node->GetName() : _T("World") );
	}

	// dotted line to right of keys
	if ( rightTime > range.End() )
	{
		SelectObject(hdc,dpen);
		GetValue(range.End(),&val,valid);
		y = ValueToScreen(dim->Convert(val),h,vzoom,vscroll);
		MoveToEx(hdc,TimeToScreen(range.End(),tzoom,tscroll),y,NULL);
		LineTo(hdc,rcPaint.right,y);
	}

	SelectObject( hdc, spen );
	HBRUSH hUnselBrush = CreateSolidBrush(GetColorManager()->GetColor(kTrackbarKeys));
	HBRUSH hSelBrush = CreateSolidBrush(GetColorManager()->GetColor(kTrackbarSelKeys));

	// render keys themselves
	for ( int i=0; i<n; ++i )
	{
		TimeValue t = GetKeyTime( i );
		if ( t < leftTime || t > rightTime )
			continue;
		GetValue(t,&val,valid);
		y = ValueToScreen(dim->Convert(val),h,vzoom,vscroll);
		x = TimeToScreen(t,tzoom,tscroll);
		SelectObject( hdc, IsKeySelected( i ) ? hSelBrush : hUnselBrush );
		Rectangle(hdc,x-3,y-3,x+3,y+3);
	}

	SetBkMode(hdc,OPAQUE);
	SelectObject(hdc,GetStockObject(BLACK_PEN));	

	DeleteObject(spen);
	DeleteObject(dpen);
	DeleteObject(hUnselBrush);
	DeleteObject(hSelBrush);

	return 0;
}