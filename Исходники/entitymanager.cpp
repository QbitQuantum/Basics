bool EntityManager::IsMoveLegal(Entity* input)
{
	Sprite* entity = static_cast<Sprite*>(input);
	BoundingBox<s16> entitybb;
	entity->getBoundingBox(entitybb);

	// Make player walk through everything
	if( input->getType() != PLAYERENTITY)
	{
		for(LinkedList* node = mEntities; node != NULL; node = node->next)
		{
			Entity* entity_to_check = (Entity*) node->data;

			// Ugly casting but it's needed...
			if(entity_to_check->getType() != LIVINGENTITY || input == entity_to_check || entity_to_check->hidden)
				continue;

			Sprite* current = static_cast<Sprite*>(entity_to_check);

			BoundingBox<s16> bb;
			current->getBoundingBox(bb);
			if(entitybb.Intersects(bb))
				return false;
		}
	}

	return true;

	/* Check the map walk/nowalk flag */
	//return (gpMapEngine->collisionAbsolute(entity->position.x() + 16, entity->position.y() + 16));
}