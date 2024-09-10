	CharacterContextContainer::CharacterContextContainer()
	{
		//create default
		{
			hkpCharacterState* state;
			hkpCharacterStateManager* manager = new hkpCharacterStateManager();

			state = new hkpCharacterStateOnGround();
			manager->registerState( state,	HK_CHARACTER_ON_GROUND);
			state->removeReference();

			state = new hkpCharacterStateInAir();
			manager->registerState( state,	HK_CHARACTER_IN_AIR);
			state->removeReference();

			state = new hkpCharacterStateJumping();
			manager->registerState( state,	HK_CHARACTER_JUMPING);
			state->removeReference();

			state = new hkpCharacterStateClimbing();
			manager->registerState( state,	HK_CHARACTER_CLIMBING);
			state->removeReference();

			hkpCharacterContext * characterContext = new hkpCharacterContext(manager, HK_CHARACTER_IN_AIR);	
			manager->removeReference();			

			// Set new filter parameters for final output velocity filtering
			// Smoother interactions with small dynamic boxes
			characterContext->setCharacterType(hkpCharacterContext::HK_CHARACTER_RIGIDBODY);
			characterContext->setFilterParameters(0.9f,12.0f,200.0f);

			registerContext("Default", characterContext);

			characterContext->removeReference();
		}
	}