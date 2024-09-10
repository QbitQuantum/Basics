void GRSimpleBeam::OnDraw( VGDevice & hdc ) const
{
	const unsigned char * colref = getColRef();

	if (colref) {
		VGColor color ( colref ); 	// custom or black
		hdc.PushFillColor( color );
		hdc.PushPen( color, 1 );
	}
	float ax [4] = { fPoints[0].x, fPoints[1].x, fPoints[3].x, fPoints[2].x };
	float ay [4] = { fPoints[0].y, fPoints[1].y, fPoints[3].y, fPoints[2].y };


// DF added to check for incorrect coordinates
// makes sure that the right point is not to the left of the left point :-)
// actually this should be checked at coordinates computation time
// todo: check the object that computes the beam coordinates
	if (ax[0] > ax[2]) { ax[2] = ax[0]; }
	if (ax[1] > ax[3]) { ax[3] = ax[1]; }
	
	// This does the drawing!
	hdc.Polygon( ax, ay, 4 );

	// - Cleanup
	if (colref) {
		hdc.PopPen();
		hdc.PopFillColor();
	}
}