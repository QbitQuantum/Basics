GLvoid Torus::GetTorusSegment( Parameter &theParamTheta, Parameter &theParamPhi )
{
	theParamPhi += torus.sideDelta;
	
	torus.factor = torus.outerRadii + torus.innerRadii * theParamPhi.cos( );

	// Begin the segment here with the normal and the vertex
	
	GetTorusNormal( theParamTheta, theParamPhi );
	GetTorusVertex( theParamTheta, theParamPhi );

	theParamTheta += torus.ringDelta;
	
	// End the segment here with the normal and the vertex

	GetTorusNormal( theParamTheta, theParamPhi );
	GetTorusVertex( theParamTheta, theParamPhi );
} // TorusSegment::GetTorusSegment