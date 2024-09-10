	void Ball::Update()
	{
		// store our last position
		Vector2 lastPosition = position;

		// update our current position using velocity
		position += velocity * Monocle::deltaTime;

		// check collisions against the paddles
		Collider* collider = Collide("Paddle");
		if (collider)
		{
			Debug::Log("Ball hit an entity tagged with 'Paddle'");
			position = lastPosition;
			
			Vector2 diff = position - collider->GetEntity()->position;
			diff.Normalize();
			diff *= velocity.GetMagnitude();
			velocity = diff;
            
            // Calculate panning
            float pan = ((collider->GetEntity()->position.x / Graphics::GetVirtualWidth()) - 0.5) * 2.0;

            if (sfxWall)
                sfxWall->Play(1,1.0,pan); // Play it with panning! (STEREO, baby :D)
		}

		// if we hit the top or bottom of the screen
		if (position.y < 0 || position.y > 600)
		{
			position = lastPosition;
			velocity.y *= -1;
            
            // Calculate panning
            float pan = ((position.x / Graphics::GetVirtualWidth()) - 0.5) * 2.0;
            
            if (sfxWall)
                sfxWall->Play(1,1.0,pan,2.0); // Play it higher, you won't even notice it's the same ;D
		}
		
		// if we go off the left side of the screen
		if (position.x < 0)
		{
			SendNoteToScene("BallOffLeft");
		}

		// if we go off the right side of the screen
		if (position.x > 800)
		{
			SendNoteToScene("BallOffRight");
		}
	}