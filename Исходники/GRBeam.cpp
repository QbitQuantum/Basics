void GRBeam::OnDraw( VGDevice & hdc) const
{
	if (error) return;

	if(!mDraw)
		return;

	GRSystemStartEndStruct * sse = getSystemStartEndStruct( gCurSystem );
	if (sse == 0) return;

	GRBeamSaveStruct * st = (GRBeamSaveStruct *)sse->p;
	assert(st);

	if (mColRef) {
		VGColor color ( mColRef ); 	// custom or black
		hdc.PushFillColor( color );
		hdc.PushPen( color, 1);
	}
		
	float ax [4] = { st->p[0].x, st->p[1].x, st->p[3].x, st->p[2].x };
	float ay [4] = { st->p[0].y, st->p[1].y, st->p[3].y, st->p[2].y };
	
	// This does the drawing!
	hdc.Polygon(ax, ay, 4);
	
	if (st->simpleBeams)
	{
		GuidoPos smplpos = st->simpleBeams->GetHeadPosition();
		while (smplpos)
		{
			GRSimpleBeam * smplbeam = st->simpleBeams->GetNext(smplpos);
			smplbeam->OnDraw(hdc);
		}
	}

	if(drawDur)
	{
		const char * fraction = st->duration.c_str();
		size_t n = st->duration.length();

        hdc.PushPenWidth(4);

		if(sse->startflag != GRSystemStartEndStruct::OPENLEFT)
		{	
			hdc.Line(st->DurationLine[0].x, st->DurationLine[0].y, st->DurationLine[1].x, st->DurationLine[1].y);
			hdc.Line(st->DurationLine[1].x, st->DurationLine[1].y, st->DurationLine[2].x, st->DurationLine[2].y);
			hdc.Line(st->DurationLine[3].x, st->DurationLine[3].y, st->DurationLine[4].x, st->DurationLine[4].y);
		}
		else
			hdc.Line(st->DurationLine[1].x, st->DurationLine[1].y, st->DurationLine[4].x, st->DurationLine[4].y);
		if(sse->endflag != GRSystemStartEndStruct::OPENRIGHT)
			hdc.Line(st->DurationLine[4].x, st->DurationLine[4].y, st->DurationLine[5].x, st->DurationLine[5].y);
		
		const VGFont* hmyfont;
		hmyfont = FontManager::gFontText;
		hdc.SetTextFont( hmyfont );

		if (sse->startflag != GRSystemStartEndStruct::OPENLEFT)
			hdc.DrawString(st->DurationLine[2].x + LSPACE/4, st->DurationLine[2].y + LSPACE / 2, fraction, n);

        hdc.PopPenWidth();
	}

	if (mColRef)
    {
		hdc.PopPen();
		hdc.PopFillColor();
	}

}