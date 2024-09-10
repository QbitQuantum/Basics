void Movement::MoveToLocation()
{
	Vector3f pos;
	bool isPosition = false;
	/// Check if we reached our destination?
	switch(location)
	{
		case Location::VECTOR:
		{
			// Adjust movement vector?
			pos = levelEntity->worldPosition + vec;
			isPosition = true;
			break;
		}
		case Location::LEFT_EDGE:
		{
			if (state == 0)
			{
				SetDirection(Vector3f(-1,0,0));
				++state;
			}
			else if (shipEntity->worldPosition.x < leftEdge && state == 1)
			{
				SetDirection(Vector2f());
				++state;
			}
			break;
		}
		case Location::RIGHT_EDGE:
			if (state == 0)
			{
				SetDirection(Vector3f(1,0,0));
				++state;
			}
			else if (shipEntity->worldPosition.x > rightEdge && state == 1)
			{
				SetDirection(Vector2f());
				++state;
			}
			break;
		case Location::UPPER_EDGE:
		{
			if (state == 0)
			{
				SetDirection(Vector3f(0,1,0));
				++state;
			}
			else if (shipEntity->worldPosition[1] > 20.f && state == 1)
			{
				SetDirection(Vector2f());
				++state;
			}
			break;
		}
		case Location::LOWER_EDGE:
		{
			if (state == 0)
			{
				SetDirection(Vector3f(0,-1,0));
				++state;
			}
			if (shipEntity->worldPosition[1] < 0.f && state == 1)
			{
				SetDirection(Vector2f());
				++state;
			}
			break;
		}
		case Location::CENTER: 
			pos = levelEntity->worldPosition;
			isPosition = true;
			break;
		case Location::PLAYER:
			if (playerShip->entity)
			{
				pos = playerShip->entity->worldPosition;
				isPosition = true;
			}
			else {
				SetDirection(Vector3f());
				return;
			}
			break;
		default:
			assert(false && "Movement unidentified");
	}
	if (isPosition)
	{
		Vector3f toPos = pos - shipEntity->worldPosition;
		if (toPos.LengthSquared() > 1)
			toPos.Normalize();
		SetDirection(toPos);
	}
}