bool ZoneContainerComponent::transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient, bool allowOverflow, bool notifyRoot) {
	Zone* newZone = dynamic_cast<Zone*>(sceneObject);
	Zone* zone = object->getZone();

	if (object->isActiveArea())
		return insertActiveArea(newZone, dynamic_cast<ActiveArea*>(object));

	Locker zoneLocker(newZone);

	if (object->isInQuadTree() && newZone != zone) {
		object->error("trying to insert to zone an object that is already in a different quadtree");

		object->destroyObjectFromWorld(true);

		return false;

		//StackTrace::printStackTrace();
	}

	ManagedReference<SceneObject*> parent = object->getParent().get();

	if (parent != NULL/* && parent->isCellObject()*/) {
		uint64 parentID = object->getParentID();

		if (containmentType == -2)
			parent->removeObject(object, sceneObject, false);
		else
			parent->removeObject(object, sceneObject, true);

		if (object->getParent() != NULL && parent->containsChildObject(object))
			return false;
		else
			object->setParent(NULL);

		if (parent->isCellObject()) {
			ManagedReference<BuildingObject*> build = cast<BuildingObject*>(parent->getParent().get().get());

			if (build != NULL) {
				CreatureObject* creature = cast<CreatureObject*>(object);

				if (creature != NULL)
					build->onExit(creature, parentID);
			}
		}
	} else {
		object->setParent(NULL);
	}

	object->setZone(newZone);
	zone = newZone;

	zone->addSceneObject(object);

	if (notifyClient)
		object->sendToOwner(true);

	if (parent == NULL)
		object->initializePosition(object->getPositionX(), object->getPositionZ(), object->getPositionY());

	zone->insert(object);

	zone->inRange(object, ZoneServer::CLOSEOBJECTRANGE);

	if (object->isTangibleObject()) {
		TangibleObject* tano = cast<TangibleObject*>(object);

		zone->updateActiveAreas(tano);
	}

	SharedBuildingObjectTemplate* objtemplate = dynamic_cast<SharedBuildingObjectTemplate*>(object->getObjectTemplate());

	if (objtemplate != NULL) {
		String modFile = objtemplate->getTerrainModificationFile();

		if (!modFile.isEmpty()) {
			newZone->getPlanetManager()->getTerrainManager()->addTerrainModification(object->getWorldPositionX(), object->getWorldPositionY(), modFile, object->getObjectID());
		}
	}

	object->notifyInsertToZone(zone);

	return true;
}