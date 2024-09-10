void AimingEnemyController::update(UpdatePackage * package)
{
	//find the player
	PlayerController * playerController = package->state->getComponentOfType<PlayerController>();
	// if there is a player
	if (playerController != NULL)
	{
		// get information on the player and the enemy
		Entity * player = package->state->getContainerEntity(playerController);
		ShipController * ship = package->entity->getComponentOfType<ShipController>();
		Transform * transform = package->entity->getComponentOfType<Transform>();
		Physics * physics = package->entity->getComponentOfType<Physics>();
		Transform * playerTransform = player->getComponentOfType<Transform>();
		//find the vector between them
		XMVECTOR difference = transform->getPosition() - playerTransform->getPosition();
		//get the length of the distance
		float distance = XMVectorGetX(XMVector3Length(difference));
		//get the cross product of the unit vector between the player and the enemy and the forward vector of the enemy 
		difference = XMVector3Normalize(difference);
		XMVECTOR cross = XMVector3Cross(transform->getUp(), difference);
		// turn the ship based on the z component of the cross product
		ship->turn(-XMVectorGetZ(cross) * 2);
		//if the vectors are moslty aligned then fire
		if (abs(XMVectorGetZ(cross)) < 0.1f)
		{
			ship->fire();
		}
		//if the ship is mostly facing the player and is too far away then thrust
		if (distance > 300 && abs(abs(XMVectorGetZ(cross)) < 0.5f))
		{
			ship->thrust();
		}
	}
}