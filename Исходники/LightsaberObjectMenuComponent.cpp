int LightsaberObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {

	if (!sceneObject->isTangibleObject())
		return 0;

	Reference<PlayerObject*> playObject = player->getPlayerObject();

	// Admins should be able to open.
	if (!sceneObject->isASubChildOf(player) && !playObject->isPrivileged())
		return 0;

	ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(sceneObject);

	if (weapon == NULL)
		return 1;

	// Handle opening sabers
	if (selectedID == 89) {

		ManagedReference<SceneObject*> parent = weapon->getParent();
		if (parent != NULL && parent->isPlayerCreature()){
			player->sendSystemMessage("@jedi_spam:saber_not_while_equpped");
			return 0;
		}

		weapon->sendContainerTo(player);
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}