void MapMgr::_PerformObjectDuties()
{
	++mLoopCounter;
	uint32 mstime = getMSTime();
	uint32 difftime = mstime - lastUnitUpdate;
	if(difftime > 500)
		difftime = 500;

	// Update any events.
	// we make update of events before objects so in case there are 0 timediff events they do not get deleted after update but on next server update loop
	eventHolder.Update(difftime);

	// Update creatures.
	{
		creature_iterator = activeCreatures.begin();
		Creature* ptr;
		Pet* ptr2;

		for(; creature_iterator != activeCreatures.end();)
		{
			ptr = *creature_iterator;
			++creature_iterator;
			ptr->Update(difftime);
		}

		pet_iterator = m_PetStorage.begin();
		for(; pet_iterator != m_PetStorage.end();)
		{
			ptr2 = pet_iterator->second;
			++pet_iterator;
			ptr2->Update(difftime);
		}
	}

	// Update players.
	{
		PlayerStorageMap::iterator itr = m_PlayerStorage.begin();
		Player* ptr;
		for(; itr != m_PlayerStorage.end();)
		{
			ptr = itr->second;
			++itr;
			ptr->Update(difftime);
		}

		lastUnitUpdate = mstime;
	}

	// Dynamic objects
	//
	// We take the pointer, increment, and update in this order because during the update the DynamicObject might get deleted,
	// rendering the iterator unincrementable. Which causes a crash!
	{
		for(DynamicObjectStorageMap::iterator itr = m_DynamicObjectStorage.begin(); itr != m_DynamicObjectStorage.end();)
		{

			DynamicObject* o = itr->second;
			++itr;

			o->UpdateTargets();
		}
	}

	// Update gameobjects (not on every loop, however)
	if(mLoopCounter % 2)
	{
		difftime = mstime - lastGameobjectUpdate;

		GameObjectSet::iterator itr = activeGameObjects.begin();
		GameObject* ptr;
		for(; itr != activeGameObjects.end();)
		{
			ptr = *itr;
			++itr;
			if(ptr != NULL)
				ptr->Update(difftime);
		}

		lastGameobjectUpdate = mstime;
	}

	// Sessions are updated every loop.
	{
		int result;
		WorldSession* session;
		SessionSet::iterator itr = Sessions.begin();
		SessionSet::iterator it2;

		for(; itr != Sessions.end();)
		{
			session = (*itr);
			it2 = itr;
			++itr;

			if(session->GetInstance() != m_instanceID)
			{
				Sessions.erase(it2);
				continue;
			}

			// Don't update players not on our map.
			// If we abort in the handler, it means we will "lose" packets, or not process this.
			// .. and that could be disastrous to our client :P
			if(session->GetPlayer() && (session->GetPlayer()->GetMapMgr() != this && session->GetPlayer()->GetMapMgr() != 0))
			{
				continue;
			}

			if((result = session->Update(m_instanceID)) != 0)
			{
				if(result == 1)
				{
					// complete deletion
					sWorld.DeleteSession(session);
				}
				Sessions.erase(it2);
			}
		}
	}

	// Finally, A9 Building/Distribution
	_UpdateObjects();
}