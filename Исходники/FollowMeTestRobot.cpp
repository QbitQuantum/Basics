// move to a target point
double MyController::goToObj(Vector3d pos, double velocity, double range, double now)
{
	// get own position
	Vector3d myPos;
	m_my->getPosition(myPos);

	// vector from own position to a target position
	pos -= myPos;

	pos.y(0);

	// distance to a target position
	double distance = pos.length() - range;

	// calcurate veloocity from radius of wheels
	double vel = m_radius*velocity;

	// start moving
	m_my->setWheelVelocity(velocity, velocity);

	// calcurate time of arrival
	double time = distance / vel;

	return now + time;
}