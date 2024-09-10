void DirectionSphericalTestApp::update()
{
	// sperical coordinate
	float thetaDiff = mVectorTarget.y - mVectorSpherical.y;
	float phiDiff = mVectorTarget.z - mVectorSpherical.z;
	if ( phiDiff > M_PI )
	{
		phiDiff -= 2 * M_PI;
	}
	else
	if ( phiDiff < -M_PI )
	{
		phiDiff += 2 * M_PI;
	}
	mVectorSpherical.y = mVectorSpherical.y + 0.05f * thetaDiff;
	mVectorSpherical.z = mVectorSpherical.z + 0.05f * phiDiff;

	// vector slerp - cannot handle parallel target
	mVectorSlerp = mVectorSlerp.slerp( 0.06f, sphericalToCartesian( mVectorTarget ) );

	// quaternion slerp
	Quatf q( mVectorQuat, sphericalToCartesian( mVectorTarget ) );
	Quatf q0;
	mVectorQuat = q0.slerp( 0.07f, q ) * mVectorQuat;
}