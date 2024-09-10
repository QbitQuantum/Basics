void ComputeController(btVector3 &currentSpeed, const btVector3 &delta, const btVector3 &maxSpeed, float scaleDelta, float damping) {
	// Timestep scale
	btVector3 acceleration = delta * scaleDelta;

	if (currentSpeed.fuzzyZero() && !currentSpeed.isZero()) {
		currentSpeed.setZero();
	}
	acceleration += currentSpeed * -damping;

	// Clamp the acceleration to max speed
	for(int i = 2; i >= 0; i--) {
		if (fabs(acceleration[i]) < maxSpeed[i]) continue;
		acceleration[i] = (acceleration[i] < 0) ? -maxSpeed[i] : maxSpeed[i];
	}

	currentSpeed += acceleration;
}