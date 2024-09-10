void CPlanetDot::update(float dt)
{
	/** Assume circular orbit */
	/** x^2 + y^2 = orbitRadius */
	/** position = (cos(t), sin(t)) */

	/*
	time +=dt * orbitSpeed;;
	mVecPosition.x = cosf(time);
	mVecPosition.y = sinf(time);
	*/

	float a = mVecVelocity.lengthSq() / this->orbitRadius;
	Vector2f aVec = mVecCenter - mVecPosition;
	aVec.normalize();
	aVec *= a;
	mVecVelocity += aVec;
	if(mVecVelocity.length() > orbitSpeed)
	{
		mVecVelocity.normalize();
		mVecVelocity *= orbitSpeed;
	}
	mVecPosition += mVecVelocity;
}