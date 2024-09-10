	void Player::Update()
	{
		Entity::Update();

		if (Input::IsMouseButtonHeld(MOUSE_BUTTON_LEFT))
		{
			Vector2 dir = Input::GetWorldMousePosition() - position;
			dir.Normalize();
			velocity += force * dir * Monocle::deltaTime;
		}

		position += velocity * Monocle::deltaTime;

		Game::GetScene()->GetCamera()->position = position;
		//Graphics::SetCameraPosition(position);
	}