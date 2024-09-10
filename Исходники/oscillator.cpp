/**
 *	This method runs this motor.
 */
void Oscillator::rev( float dTime )
{
	BW_GUARD;
	double timeNow = Script::getTotalGameTime();

	float yawOffset = float( 2 * MATH_PI * fmod( timeNow / period_ + offset_, 1.0 ) );
	if (amplitude_ >= 0.f) yawOffset = amplitude_ * sinf( yawOffset );

	const Matrix & oldWorld = pOwner_->worldTransform();
	Matrix newWorld;

	newWorld.setRotate( yaw_ + yawOffset, oldWorld.pitch(), oldWorld.roll() );
	newWorld[0] *= oldWorld[0].length();
	newWorld[1] *= oldWorld[1].length();
	newWorld[2] *= oldWorld[2].length();
	newWorld.translation( oldWorld.applyToOrigin() );

	pOwner_->worldTransform( newWorld );
}