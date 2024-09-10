void ZoneComponent::destroyObjectFromWorld(SceneObject* sceneObject, bool sendSelfDestroy) {
	ManagedReference<SceneObject*> par = sceneObject->getParent();

	sceneObject->broadcastDestroy(sceneObject, sendSelfDestroy);

	ManagedReference<Zone*> rootZone = sceneObject->getZone();
	ManagedReference<Zone*> zone = sceneObject->getLocalZone();

	if (par != NULL) {
		uint64 parentID = sceneObject->getParentID();
		par->removeObject(sceneObject, NULL, false);

		if (par->isCellObject()) {
			ManagedReference<BuildingObject*> build = cast<BuildingObject*>(par->getParent().get().get());

			if (build != NULL) {
				CreatureObject* creature = cast<CreatureObject*>(sceneObject);

				if (creature != NULL)
					build->onExit(creature, parentID);
			}
		}

		sceneObject->notifyObservers(ObserverEventType::OBJECTREMOVEDFROMZONE, sceneObject, 0);
	} else if (zone != NULL) {
		zone->removeObject(sceneObject, NULL, false);
	}

	if (rootZone != NULL) {
		Locker locker(rootZone);

		if (!sceneObject->isActiveArea())
			rootZone->remove(sceneObject);
			
		rootZone->dropSceneObject(sceneObject);

		SharedBuildingObjectTemplate* objtemplate = dynamic_cast<SharedBuildingObjectTemplate*>(sceneObject->getObjectTemplate());

		if (objtemplate != NULL) {
			String modFile = objtemplate->getTerrainModificationFile();

			if (!modFile.isEmpty()) {
				rootZone->getPlanetManager()->getTerrainManager()->removeTerrainModification(sceneObject->getObjectID());
			}
		}
		
		locker.release();


		SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;

		CloseObjectsVector* closeobjects = (CloseObjectsVector*) sceneObject->getCloseObjects();

		if (closeobjects != NULL) {
			try {
				closeobjects->safeCopyTo(closeSceneObjects);

				while (closeSceneObjects.size() > 0) {
					ManagedReference<QuadTreeEntry*> obj = closeSceneObjects.get(0);

					if (obj != NULL && obj != sceneObject && obj->getCloseObjects() != NULL)
						obj->removeInRangeObject(sceneObject);
					
					sceneObject->removeInRangeObject((int) 0);

					closeSceneObjects.remove((int) 0);
				}

				closeobjects->removeAll();

			} catch (...) {
			}
		} else {
			SortedVector<ManagedReference<QuadTreeEntry*> > closeSceneObjects;

			sceneObject->info("Null closeobjects vector in ZoneComponent::destroyObjectFromWorld", true);

			rootZone->getInRangeObjects(sceneObject->getPositionX(), sceneObject->getPositionY(), 512, &closeSceneObjects, false);

			for (int i = 0; i < closeSceneObjects.size(); ++i) {
				QuadTreeEntry* obj = closeSceneObjects.get(i);

				if (obj != sceneObject && obj->getCloseObjects() != NULL)
					obj->removeInRangeObject(sceneObject);
			}
		}

//		rootZone->dropSceneObject(sceneObject);

//		locker.release();

		Vector<ManagedReference<ActiveArea*> >* activeAreas =  sceneObject->getActiveAreas();

		while (activeAreas->size() > 0) {
			Locker _alocker(sceneObject->getContainerLock());
			ManagedReference<ActiveArea*> area = activeAreas->get(0);
			activeAreas->remove(0);
			
			_alocker.release();
			
			area->enqueueExitEvent(sceneObject);
		}
	}
}