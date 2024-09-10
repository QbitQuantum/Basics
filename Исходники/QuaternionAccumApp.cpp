void QuaternionAccumApp::drawBall()
{
	Vec3f pos = mSpline.getPosition( mSplineValue );
	Vec3f delta = pos - mLastPos;
	// our axis of rotation is the normal to the spline at this point
	Vec3f normal = Vec3f( delta.z, 0, -delta.x );
	
	// rotation amount (in radians) is the distance we've traveled divided by the radius of the ball
	float rotation = delta.length() / BALL_RADIUS;
	if( rotation ) {
		// increment our quaternion by a new quaternion representing how much rotating we did since the last frame
		Quatf incQuat( normal, rotation );
		mQuat *= incQuat;
		mQuat.normalize();
	}
	
	gl::translate( Vec3f( 0.0f, BALL_RADIUS, 0.0f ) + pos );
	gl::scale( Vec3f( BALL_RADIUS, BALL_RADIUS, BALL_RADIUS ) );
	gl::rotate( mQuat );
	
	gl::color( Color( 1, 1, 1 ) );
	mBallTexture.enableAndBind();
	gl::drawSphere( Vec3f::zero(), 1.0f, 60 );
	mBallTexture.disable();
	
	mLastPos = pos;
}