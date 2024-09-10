void CreatureImplementation::sendMessage(BasePacket* msg) {
	if (!isMount()) {
		delete msg;
		return;
	}

	ManagedReference<CreatureObject* > linkedCreature = this->linkedCreature.get();

	if (linkedCreature != NULL && linkedCreature->getParent().get() == _this.get())
		linkedCreature->sendMessage(msg);
	else
		delete msg;
}