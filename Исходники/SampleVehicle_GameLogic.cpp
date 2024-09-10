void SampleVehicleWayPoints::update(const PxTransform& playerTransform, const PxF32 timestep)
{
	//Increment the elapsed time
	mTimeElapsed+=timestep;

	//Work out the point on the crossing line of the next way-point that is closest to the player.
	const PxTransform& nextWayPoint=mWayPoints[mProgress+1];
	const PxVec3 v=nextWayPoint.p;
	const PxVec3 w=nextWayPoint.q.getBasisVector0();
	const PxVec3 p=playerTransform.p;
	const PxVec3 pv=p-v;
	const PxF32 t=pv.dot(w);

	//Test if the player's position is inside the width of the line crossing the next way-point.
	if(PxAbs(t) < LINEWIDTH)
	{
		//Now test if the shortest distance to the next crossing line is smaller than a threshold.
		const PxVec3 linePos=v+w*t;
		const PxVec3 diff=p-linePos;
		const PxF32 dist2=diff.magnitudeSquared();
		if(dist2<LINEDISTANCE2)
		{
			mProgress++;
		}
	}

	if(mProgress == mNumWayPoints-1)
	{
		mMinTimeElapsed=PxMin(mTimeElapsed, mMinTimeElapsed);
		mTimeElapsed=0;
		mProgress=0;
	}
}