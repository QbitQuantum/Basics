Point2F Mover::CalculateFriction(float frictionMag, const Point2F& gravity)
{
	//Friction=-frictionMag*N*v
	//v==mVelocity.Normalize()

	Point2F friction = -mVelocity;
	friction.Normalize();

	friction *= frictionMag;
	friction *= mMass*gravity;
	return friction;
}