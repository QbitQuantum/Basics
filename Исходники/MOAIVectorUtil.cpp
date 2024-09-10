//----------------------------------------------------------------//
int MOAIVectorUtil::StrokeWedge ( const MOAIVectorStyle& style, ZLVec2D*& verts, const ZLVec2D& origin, const ZLVec2D& n0, const ZLVec2D& n1, float width ) {
	
	float wedge = n0.Radians ( n1 ); // angle between two normals
	
	u32 steps = style.GetResolutionForWedge ( wedge );
	
	if ( verts ) {
		
		float angle = n0.Radians (); // angle of first normal against x axis
		float angleStep = wedge / ( float )steps;
		
		for ( u32 i = 0; i <= steps; ++i, angle += angleStep ) {
			ZLVec2D v;
			v.mX = origin.mX + ( Cos ( angle ) * width );
			v.mY = origin.mY + ( Sin ( angle ) * width );
			*( verts++ ) = v;
		}
	}
	return ( int )( steps + 1 );
}