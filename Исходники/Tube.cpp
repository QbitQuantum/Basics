void Tube::buildFrenet()
{
	mFrames.clear();
	
	int n = mPs.size();
	mFrames.resize( n );
	
	for( int i = 0; i < n; ++i ) {
		Vec3f p0, p1, p2;		
		if( i < (n - 2) ) {
			p0 = mPs[i];
			p1 = mPs[i + 1];
			p2 = mPs[i + 2];
		}
		else if( i == (n - 2) ) {
			p0 = mPs[i - 1];
			p1 = mPs[i];
			p2 = mPs[i + 1];
		}	
		else if( i == (n - 1) ) {
			p0 = mPs[i - 3];
			p1 = mPs[i - 2];
			p2 = mPs[i - 1];
		}

		
	    Vec3f t = (p1 - p0).normalized();
		Vec3f n = t.cross(p2 - p0).normalized();
		if( n.length() == 0.0f ) {
			int i = fabs( t[0] ) < fabs( t[1] ) ? 0 : 1;
			if( fabs( t[2] ) < fabs( t[i] ) ) 
				i = 2;
				
			Vec3f v( 0.0f, 0.0f, 0.0f ); 
			v[i] = 1.0;
			n = t.cross( v ).normalized();
		}
		Vec3f b = t.cross( n );	
	
		Matrix44f& m = mFrames[i];
		m.at( 0, 0 ) = b.x;
		m.at( 1, 0 ) = b.y;
		m.at( 2, 0 ) = b.z;
		m.at( 3, 0 ) = 0;
		
		m.at( 0, 1 ) = n.x;
		m.at( 1, 1 ) = n.y;
		m.at( 2, 1 ) = n.z;
		m.at( 3, 1 ) = 0;
		
		m.at( 0, 2 ) = t.x;
		m.at( 1, 2 ) = t.y;
		m.at( 2, 2 ) = t.z;
		m.at( 3, 2 ) = 0;
		
		m.at( 0, 3 ) = mPs[i].x;
		m.at( 1, 3 ) = mPs[i].y;
		m.at( 2, 3 ) = mPs[i].z;
		m.at( 3, 3 ) = 1;
	}
}