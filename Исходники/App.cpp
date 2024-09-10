void updateOrientation() {
	if ( orientationDirty == false ) {
		return;
	}
	orientationDirty = false;
	
	float decay = 0.9f;
	
	float hyst = cos( ToRadians( app_orientationHysteresis.GetVal() ) );

	if ( GotCompassUpdate ) {
		if ( headingSmooth.Dot( heading ) < hyst ) {
			headingSmooth *= decay;
			headingSmooth += (1.0f - decay) * heading;
		}
		headingSmooth.Normalize();
	} 		

	if ( accelSmooth.Dot( accel ) < hyst ) {
		accelSmooth *= decay;
		accelSmooth += (1.0f - decay) * accel;		
	}
	accelSmooth.Normalize();		
	
	Vec3f up = -accelSmooth;
	up.Normalize();
	Vec3f north = headingSmooth;
	north -= up * up.Dot( north );
	north.Normalize();

	Matrix3f toTrueNorth = Rotationf( up, ToRadians( trueHeadingDiff ) ).GetMatrix3();
	north = toTrueNorth * north;
	
	Vec3f east = north.Cross( up );

	Matrix4f o;
	o.SetRow( 0, Vec4f(  east.x,  east.y,  east.z, 0.0f ) );
	o.SetRow( 1, Vec4f( north.x, north.y, north.z, 0.0f ) );
	o.SetRow( 2, Vec4f(    up.x,    up.y,    up.z, 0.0f ) );
	o.SetRow( 3, Vec4f(     0.0,     0.0,     0.0, 1.0f ) );
	
	platformOrientation = o.Transpose();
}