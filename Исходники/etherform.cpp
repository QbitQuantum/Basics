void Etherform::updateCameraPos(F32 delta)
{
	//
	// Update 3rd person camera position.
	//

	F32 min,max;
	Point3F offset;
	MatrixF rot;
	this->getCameraParameters(&min,&max,&offset,&rot);

	Point3F vec = mCameraTargetPos - mCameraPos;
	F32    dist = vec.len();

	if(dist == 0)
	{
		// Catch camera position up to its target position.
		mCameraPos = mCameraTargetPos;
	}
	else if(dist > max)
	{
		// Catch camera up to max allowed dist from target position.
		vec.normalize(); vec.neg();
		mCameraPos = mCameraTargetPos + vec * max;
	}
	else
	{
		// Move camera pos towards its target pos.
#if 0
		F32 speed = mDataBlock->accelerationForce;
		speed *= 1 - (1/vec.lenSquared());

		vec.normalize();
		mCameraPos += vec * speed * delta;
#else
		//F32 speedScale = this->getVelocity().len() / mDataBlock->accelerationForce;
		F32 speedScale = 4; //mDataBlock->accelerationForce / 2;
		F32 distScale = 1 - (1/vec.lenSquared());
		vec *= speedScale * distScale * delta;
		if(vec.len() > dist)
			mCameraPos = mCameraTargetPos;
		else
			mCameraPos += vec;
#endif
	}
}