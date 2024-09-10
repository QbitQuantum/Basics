void Path2DSamplesApp::setup()
{
	
	// lineTo
	path1.moveTo( vec2( 0.0, 0.0 ) );
	path1.lineTo( vec2( 100.0, 100.0 ) );
	path1.lineTo( vec2( 200.0, 0.0 ) );
	path1.lineTo( vec2( 300.0, 100.0 ) );
	path1.lineTo( vec2( 400.0, 0.0 ) );
	
	// quadTo - waves
	float waveWidth = 100.0;
	path2.moveTo( vec2( 0.0, 50.0 ) );
	for( int i = 0; i < 5; i++ ) {
		float startX = i * waveWidth;
		path2.quadTo( vec2( startX, 0.0 ), vec2( startX + waveWidth / 2.0, 0.0 ) );
		path2.quadTo( vec2( startX + waveWidth / 2.0, 50.0 ), vec2( startX + waveWidth, 50.0 ) );
	}
	
	// curveTo
	path3.moveTo( vec2( 0 ) );
	path3.curveTo( vec2( 25.0, 0.0 ), vec2( 50.0, 25.0 ), vec2( 50.0, 50.0 ) );
	
	// arc & arcTo
//	path4.moveTo( zero<vec2>() );
//	path4.arc( vec2( 25.0, 25.0 ), 25.0, 0.0, glm::pi<float> );
	path4.arc( vec2( 25.0, 25.0 ), 25.0, 0.0, M_PI );
	
	
	path5.moveTo( vec2( 0.0, 0.0 ) );
	// end point, tangent position, radius
	path5.arcTo( vec2( 50.0, 50.0 ), vec2( 50.0, 0.0 ), 25.0 );
	
	// path for contains
	path6.moveTo( vec2( 0.0, 0.0 ) );
	path6.quadTo( vec2( 80.0, 30.0), vec2( 100, 50) );
	path6.quadTo( vec2( 180.0, 50.0), vec2( 210.0, 20.0) );
	path6.quadTo( vec2( 270.0, 10.0), vec2( 280.0, 100.0) );
	path6.quadTo( vec2( 200.0, 150.0), vec2( 140.0, 100.0) );
	path6.quadTo( vec2( 100.0, 150.0), vec2( 50.0, 80.0) );
	path6.close();
	
	// points to look for intersection
	for( int i = 0; i < 50; i++ ) {
		auto bounds = path6.calcBoundingBox();
		std::pair<vec2, vec2> pair;
		pair.first = vec2( randFloat( bounds.x1 , bounds.x2), randFloat( bounds.y1, bounds.y2 ) );
		pair.second = vec2( randFloat( -1, 1), randFloat( -1, 1) );
		intersectPts.push_back( pair );
	}
	
	
	// move over a bit and dot affine matrix copies and rotate
	{
		int amount = 10;
		
		for( int i = 0; i < amount; i++ ){
			MatrixAffine2<float> affineMtrx;
			affineMtrx.scale( 0.3 );
			affineMtrx.rotate( ( ( M_PI * 2) / 8 ) * i );
			auto pathCopy = path2.transformCopy( affineMtrx );
			pathCaches.emplace_back( pathCopy );
		}
	}

	
	
	// snowflake using 
	
	
}