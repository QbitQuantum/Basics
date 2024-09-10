/////////////////////////////////////////////////////////////////////
// TMapDC
// ------
//
void
TMapDC::SetupOrg()
{
#ifdef WINDOWS_SCALING
	// Set window and viewport scale and extension
	SetMapMode (MM_ANISOTROPIC);
	SetViewportOrg (TPoint(ScrCenterX, ScrCenterY));
	SetWindowOrg (TPoint(OrigX, OrigY)) ;
	if ( Scale > 1.0 )
	{
		// dc.SetWindowExt (TSize(ScrMaxX, ScrMaxY));
		// dc.SetViewportExt (TSize(ScrMaxX * MUL_SCALE, -ScrMaxY * MUL_SCALE));
		SetWindowExt (TSize(1, 1));
		SetViewportExt (TSize(MUL_SCALE, -MUL_SCALE));
	}
	else if (Scale <= 1.0 )
	{
		SetWindowExt (TSize(ScrMaxX * DIV_SCALE, ScrMaxY * DIV_SCALE));
		SetViewportExt (TSize(ScrMaxX, -ScrMaxY));
	}

	/*
	for (int x = MIN_MAP_X ; x <= MAX_MAP_X ; x+=1000)
		for (SHORT y = MIN_MAP_Y ; y <= MAX_MAP_Y ; y+=1000)
		{
			char msg[80];
			wsprintf (msg,"(%d:%d)", x/1000, y/1000);
			dc.TextOut (x, y, msg);
		}
	*/

#endif
}