void HelixObject::BuildShape(TimeValue t, PolyShape& ashape) {
	// Set the object's interpolation parameters
	ReadyInterpParams(t);
	// Set the general interval to the one we just got
	ivalid = interpValid;
	ashape.NewShape();
	// Start a PolyLine for our helix...
	PolyLine *line = ashape.NewLine();
	// Compute some helpful stuff...
	int points = (int)(turns * (float)POINTS_PER_TURN);
	if(points == 0)
		points = 1;
	float fPoints = (float)points;
	numberOfPieces = 0;
	for(int i = 0; i <= points; ++i) {
		float pct = (float)i / fPoints;
		float r = radius1 + deltaRadius * pct;
		float hpct = pct;
		if(bias > 0.0f)
			hpct = 1.0f - (float)pow(1.0f - pct, power );
		else
		if(bias < 0.0f)
			hpct = (float)pow(pct, power);
			
		float z = height * hpct;
		float angle = totalRadians * pct;
		float x = r * (float)cos(angle);
		float y = r * (float)sin(angle);
		DWORD flags = POLYPT_SMOOTH;
		if((i % 10) == 0 || i == points) {
			flags |= POLYPT_KNOT;	// Let it know the piece boundary
			if(i > 0)
				numberOfPieces++;
			}
		line->Append(PolyPt(Point3(x,y,z), flags));
		}
	perPiece = 1.0f / (float)numberOfPieces;
	ashape.UpdateSels();	// Make sure it readies the selection set info
	ashape.InvalidateGeomCache(FALSE);
	lengthOfCurve = ashape.lines[0].CurveLength();
	}