	/**
	*Finds our parent entity and deletes it
	*
	*@param curState the current worldstate to reference during update
	*@exception thrown if we do not have a valid entity parent, or if our target Entity is not set
	*/
	void ActionDestroyEntity::Update(const Library::WorldState& curState)
	{
		//Ensure our target entity name is set
		if (mEntity == "")
		{
			throw std::exception("Our entity target cannot be unnamed!");
		}

		Scope* scope = this;
		Entity* entity = nullptr;
		bool condition = false;

		//Iterate upwards to find our containing entity
		while (!condition)
		{
			//Get the action scope above us
			scope = scope->GetParent();
			if (scope == nullptr)
			{
				throw std::exception("We do not have an Entity or ActionList parent! This is invalid.");
			}

			//Get our real parent, who is either an entity of an action list
			scope = scope->GetParent();
			if (scope == nullptr)
			{
				throw std::exception("We do not have an Entity or ActionList parent! This is invalid.");
			}

			//See if our grandparent scope is an Entity
			entity = scope->As<Entity>();

			//If our grandparent is an actionlist we need to keep iterating upwards through the heirarchy to find the containing Entity
			//Else, we can delete the entity
			if (entity != nullptr)
			{
				condition = true;
			}
		}

		//Get the scope that contains the entity
		Scope* targetParent = entity->GetParent();

		//Remove the entity from the parent scope
		if (targetParent != nullptr)
		{
			Datum* target = targetParent->Find(mEntity);
			if (target != nullptr)
			{
				Scope* scope = target->Get<Scope*>();
				scope->Orphan();
				delete scope;
				target->Set((Scope*)nullptr);
			}
		}
	}