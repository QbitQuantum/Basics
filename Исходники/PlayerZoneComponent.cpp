void PlayerZoneComponent::notifyInsert(SceneObject* sceneObject, QuadTreeEntry* entry) {
	SceneObject* scno = cast<SceneObject*>( entry);

	if (scno == NULL || scno == sceneObject)
		return;

	if (scno->isPlayerCreature()) {
		CreatureObject* player = cast<CreatureObject*>( scno);

		if (player->isInvisible())
			return;
	}

	ManagedReference<SceneObject*> parent = scno->getParent().get();

	if (parent != NULL /*&& parent->isCellObject()*/) {
		return;
	}

	scno->sendTo(sceneObject, true);
}