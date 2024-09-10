bool RoboCat::MoveToLocation( float inDeltaTime, const Vector3& inLocation )
{
	bool finishedMove = false;

	Vector3 toMoveVec = inLocation - GetLocation();
	float distToTarget = toMoveVec.Length();
	toMoveVec.Normalize2D();
	if( distToTarget > 0.1f )
	{
		if ( distToTarget > ( kMoveSpeed * inDeltaTime ) )
		{
			SetLocation( GetLocation() + toMoveVec * inDeltaTime * kMoveSpeed );
		}
		else
		{
			//we're basically almost there, so set it to move location
			SetLocation( inLocation );
			finishedMove = true;
		}
	}
	else
	{
		//since we're close, stop moving towards the target
		finishedMove = true;
	}

	return finishedMove;
}