void DroidStimpackModuleDataComponent::handleInsertStimpack(CreatureObject* player, StimPack* pack) {
	// we need to send the invalid stimpack message just where is a good question
	countUses();

	if (player == NULL)
		return;

	if (!player->hasSkill("science_medic_ability_04")) {
		return;
	}

	ManagedReference<DroidObject*> droid = getDroidObject();
	if (droid == NULL) {
		return;
	}

	if (pack == NULL) {
		player->sendSystemMessage("@pet/droid_modules:invalid_stimpack");
		return;
	}

	if (!pack->isClassA()) {
		player->sendSystemMessage("@pet/droid_modules:invalid_stimpack");
		return;
	}

	if (droid->getLinkedCreature().get() != player) {
		return;
	}

	// we have the player and the stim to add to ourselves.
	// code should goes as follow, count total use of all stims, then deduct amount form capacity
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());

	if (droidComponent == NULL) {
		return;
	}

	ManagedReference<SceneObject*> craftingComponents = droidComponent->getSlottedObject("crafted_components");

	if (craftingComponents == NULL) {
		return;
	}

	SceneObject* satchel = craftingComponents->getContainerObject(0);

	if (satchel == NULL) {
		return;
	}

	int allowedAmount = capacity - loaded;

	if (allowedAmount <= 0) {
		player->sendSystemMessage("@pet/droid_modules:stimpack_capacity_full");
		return;
	}

	Locker plocker(pack);

	int amountOnStim = pack->getUseCount();
	StimPack* targetStim = compatibleStimpack(pack->getEffectiveness());

	if (targetStim != NULL) {
		Locker tlocker(targetStim);

		if (allowedAmount > amountOnStim) {
			targetStim->setUseCount(targetStim->getUseCount() + amountOnStim, true);
			pack->decreaseUseCount(pack->getUseCount());
		} else {
			targetStim->setUseCount(targetStim->getUseCount() + allowedAmount, true);
			pack->decreaseUseCount(allowedAmount);
		}
	} else {
		// can we take it all?
		if (allowedAmount > amountOnStim) {
			pack->destroyObjectFromWorld(true);
			// transfer to the droid and broadcast, then send the satchel to the player
			satchel->transferObject(pack, -1, true);
			satchel->broadcastObject(pack, true);
			pack->sendTo(player, true);
			droid->sendTo(player, true);
			player->sendSystemMessage("@pet/droid_modules:stimpack_loaded");
		} else {
			// we cant load it all so split the diff
			StimPack* newStim = pack->split(allowedAmount);

			if (newStim != NULL) {
				Locker slocker(newStim);
				satchel->transferObject(newStim, -1, true);
				satchel->broadcastObject(newStim, true);
				player->sendSystemMessage("@pet/droid_modules:stimpack_loaded");
			}
		}
	}

	countUses();
}