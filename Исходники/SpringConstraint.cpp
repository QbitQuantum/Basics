void SpringConstraint::apply()
{
	// F = -kd
	// where F = force, k = elasticity, d = displacement from resting distance

	Vector2 displacement = bodyB->getPosition() - bodyA->getPosition();
	float displacementMagnitude = displacement.getMagnitude() - restingDistance;
	displacement.normalize();
	displacement *= displacementMagnitude * 0.5f * elasticity;
	if (bodyA->isDynamic())
	{
		bodyA->applyForce(displacement, bodyA->getPosition());
	}

	displacement *= -1.0f;
	if (bodyB->isDynamic())
	{
		bodyB->applyForce(displacement, bodyB->getPosition());
	}

	if (debugModel != NULL)
	{
		float stretchedness = min(restingDistance / abs(displacementMagnitude) / elasticity, 1.0f);
		debugModel->setColour(Vector4(1.0f - stretchedness, 0.0f, stretchedness, 1.0f));
		debugModel->setPointA(bodyA->getPosition());
		debugModel->setPointB(bodyB->getPosition());
	}
}