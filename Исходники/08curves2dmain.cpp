void calculatePolylineFromCP(const std::vector<Vector2d> &aCPs)
{
	// build a polyline from our control points, for visible. 
	polyline.clear();
	polyline.setPosition(Vector2d(400, 400) );
	for (unsigned int i = 0; i < aCPs.size(); ++i)
		polyline.addVertex( aCPs[i] );

	// to do the evaluation of the curve, get an array pos on the curve
	std::vector<Vector2d> aPos;
	for (int i = 0; i <= 200; ++i)
		aPos.push_back( evaluateCubicBezier_deCasteljau(aCPs, i * 1.0f / 200) );
	// we use those pos on the curve to simulate a curve by a polyline, for visible.
	curvePolyline.clear(); 
	curvePolyline.setPosition(Vector2d(400, 400) );
	for (unsigned int i = 0; i < aPos.size(); ++i)
		curvePolyline.addVertex( aPos[i] ); 
}