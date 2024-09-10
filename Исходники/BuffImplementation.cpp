void BuffImplementation::activate(bool applyModifiers) {
	//info("activating buff with crc " + String::hexvalueOf((int)buffCRC), true);
	try {
		if (applyModifiers) {
			applyAttributeModifiers();
			applySkillModifiers();
			applyStates();
		}

		buffEvent = new BuffDurationEvent(creature.get(), _this.get());
		buffEvent->schedule((int) (buffDuration * 1000));
		//nextExecutionTime = buffEvent->getNextExecutionTime();
		Core::getTaskManager()->getNextExecutionTime(buffEvent, nextExecutionTime);

		//info("nextExecutionTime miliDifference:" + String::valueOf(nextExecutionTime.miliDifference()), true);

		if (creature.get()->isPlayerCreature())
			sendTo((cast<CreatureObject*>(creature.get().get())));

		if (!startMessage.isEmpty())
			creature.get()->sendSystemMessage(startMessage);

		if (!startFlyFile.isEmpty())
			creature.get()->showFlyText(startFlyFile, startFlyAux, startFlyRed, startFlyGreen, startFlyBlue);

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}
}