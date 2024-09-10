void ObjectContainer::removeObject(ScriptObject &object) {
	lock();

	ObjectType type = object.getObjectType();
	if (((uint) type) < kObjectTypeMAX)
		_objects[type].remove(&object);

	::Aurora::NWScript::ObjectContainer::removeObject(object);

	unlock();
}