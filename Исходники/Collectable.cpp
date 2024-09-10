//Update collectables positions each frame
void Collectable::update(float dt){

	//make bounding boxes
	BoundingBox *playerbb = new BoundingBox(XMFLOAT3(player->player->getPosition()._41, player->player->getPosition()._42, player->player->getPosition()._43),
		XMFLOAT3(2.0f, 2.0f, 0.0f));

	//moves collectables across screen (right to left) and respawns them when they leave the screen
	for (unsigned int i = 0; i < 1; i++){
		collectables[i]->translate(XMFLOAT3(-8.0f * dt, 0.0f, 0.0f));

		//._41 is the x value for the position matrix of game entities
		if (collectables[i]->getPosition()._41 < -30)
			collectables[i]->setPosition(XMFLOAT3(30.0f, (rand() % 40) - 19.0f, 0.0f));}

	// Tests for collisions between the collectables and the player
	for (int i = 0; i < 1; i++){
		BoundingBox *collectablebb = new BoundingBox(XMFLOAT3(collectables[i]->getPosition()._41, collectables[i]->getPosition()._42, collectables[i]->getPosition()._43),
			XMFLOAT3(2.0f, 2.0f, 0.0f));
		//check for intersections
		if (collectablebb->Intersects(*playerbb))
		{
				collectables[i]->setPosition(XMFLOAT3(30.0f, (rand() % 40) - 19.0f, 0.0f));
				gameReference->pickUp();

				//elimate spawning on each other
				for (int g = 0; g < 1; g++)
				{
					BoundingBox *collectablebb2 = new BoundingBox(XMFLOAT3(collectables[g]->getPosition()._41, collectables[g]->getPosition()._42, collectables[g]->getPosition()._43),
						XMFLOAT3(2.0f, 2.0f, 0.0f));
					if (collectablebb2->Intersects(*collectablebb))
					{
						collectables[i]->setPosition(XMFLOAT3(30.0f, (rand() % 40) - 19.0f, 0.0f));
					}
				}

		}

		break;
	}
}