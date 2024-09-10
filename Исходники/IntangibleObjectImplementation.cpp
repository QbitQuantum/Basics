void IntangibleObjectImplementation::updateStatus(int newStatus, bool notifyClient) {
	if (status == newStatus)
		return;

	status = newStatus;

	if (!notifyClient)
		return;

	ManagedReference<SceneObject*> strongParent = getParent().get();
	if (strongParent == NULL)
		return;

	ManagedReference<SceneObject*> player = strongParent->getParent();

	if (player == NULL)
		return;

	IntangibleObjectDeltaMessage3* delta = new IntangibleObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
	delta->updateStatus(newStatus);
	delta->close();
	player->sendMessage(delta);
}