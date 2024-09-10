void GroupObjectImplementation::addMember(SceneObject* newMember) {
	Locker locker(_this.get());

	GroupObjectDeltaMessage6* grp = new GroupObjectDeltaMessage6(_this.get());
	grp->startUpdate(1);
	groupMembers.add(newMember, grp);
	grp->close();

	broadcastMessage(grp);

	if (newMember->isPlayerCreature())
	{
		ManagedReference<CreatureObject*> playerCreature = cast<CreatureObject*>(newMember);

		sendTo(playerCreature, true);

		if (hasSquadLeader()) {
			addGroupModifiers(playerCreature);
		}

		scheduleUpdateNearestMissionForGroup(playerCreature->getPlanetCRC());
	}

	calcGroupLevel();
}