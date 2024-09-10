void VehicleObjectImplementation::sendMessage(BasePacket* msg) {
	ManagedReference<CreatureObject* > linkedCreature = this->linkedCreature.get();

	if (linkedCreature != NULL && linkedCreature->getParent().get() == _this.getReferenceUnsafeStaticCast())
		linkedCreature->sendMessage(msg);
	else
		delete msg;
}