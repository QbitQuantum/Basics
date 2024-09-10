//------------------------------ Pursuit ---------------------------------
//
//  this behavior creates a force that steers the agent towards the 
//  evader
//------------------------------------------------------------------------
Vector2D SteeringBehavior::Pursuit(const Vehicle* evader)
{
	//if the evader is ahead and facing the agent then we can just seek
	//for the evader's current position.
	Vector2D ToEvader = evader->Pos() - m_pVehicle->Pos();

	double RelativeHeading = m_pVehicle->Heading().Dot(evader->Heading());

	if ((ToEvader.Dot(m_pVehicle->Heading()) > 0) &&
		(RelativeHeading < -0.95))  //acos(0.95)=18 degs
	{
		return Seek(evader->Pos());
	}

	//Not considered ahead so we predict where the evader will be.

	//the lookahead time is propotional to the distance between the evader
	//and the pursuer; and is inversely proportional to the sum of the
	//agent's velocities
	double LookAheadTime = ToEvader.Length() /
		(m_pVehicle->MaxSpeed() + evader->Speed());

	//now seek to the predicted future position of the evader
	return Seek(evader->Pos() + evader->Velocity() * LookAheadTime);
}