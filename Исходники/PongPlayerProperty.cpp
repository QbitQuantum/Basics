/// Time passed in seconds..!
void PongPlayerProperty::Process(int timeInMs)
{
	List<Entity*> entities = MapMan.GetEntities();

	Time now = Time::Now();
	int secondsSinceLastInput = (now - lastUserInput).Seconds();
	if (secondsSinceLastInput < 1)
	{
		StopMovement();
		return;
	}

	bool moved = false;
	Entity * closestBall = 0;
	float closestDistance = 1000000.f;
	/// Check distance to ball. Fetch closest/most dangerous one!
	for (int i = 0; i < entities.Size(); ++i)
	{
		Entity * ball = entities[i];
		if (!ball->physics)
			continue;
		PongBallProperty * pbp = (PongBallProperty*) ball->GetProperty("PongBallProperty");
		if (!pbp)
			continue;
		if (pbp->sleeping)
			continue;

		// Check distance.
		Vector3f ballToPaddle = owner->position - ball->position;
		// Ignore balls going away.
		if (ball->physics->velocity.DotProduct(lookAt) > 0)
			continue;
		float distance = AbsoluteValue(ballToPaddle[0]);
		if (!ball->physics)
			continue;
		if (distance > 500.f)
			continue;
		if (distance < closestDistance)
		{
			closestBall = ball;
			closestDistance = distance;
		}
	}
	if (closestBall)
	{
		/// Ball on the wya here?!
		if (lookAt.DotProduct(closestBall->physics->velocity) < 0)
		{
			// Head towards it!
			Vector3f ballToPaddle = owner->position - closestBall->position;
			Vector3f toMove = -ballToPaddle;
			toMove.Normalize();
			toMove *= aiSpeed;
			toMove[1] += closestBall->physics->velocity[1] * 0.5f;
			toMove[0] = toMove[2] = 0;
			Physics.QueueMessage(new PMSetEntity(owner, PT_VELOCITY, Vector3f(toMove)));
			moved = true;
		}
	}
	if (!moved)
		StopMovement();
	
}