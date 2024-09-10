void SceneObjectImplementation::sendSlottedObjectsTo(SceneObject* player) {
	//sending all slotted objects by default
	VectorMap<String, ManagedReference<SceneObject* > > slotted;
	getSlottedObjects(slotted);

	SortedVector<SceneObject*> objects(slotted.size(), slotted.size());
	objects.setNoDuplicateInsertPlan();

	for (int i = 0; i < slotted.size(); ++i) {
		SceneObject* object = slotted.get(i);

		if (objects.put(object) != -1) {
			if (object->isInQuadTree()) {
				notifyInsert(object);
			} else {
				object->sendTo(player, true);
			}
		}
	}
}