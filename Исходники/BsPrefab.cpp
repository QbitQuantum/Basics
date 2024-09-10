	HPrefab Prefab::create(const HSceneObject& sceneObject, bool isScene)
	{
		SPtr<Prefab> newPrefab = createEmpty();
		newPrefab->mIsScene = isScene;

		PrefabUtility::clearPrefabIds(sceneObject, true, false);
		newPrefab->initialize(sceneObject);

		HPrefab handle = static_resource_cast<Prefab>(gResources()._createResourceHandle(newPrefab));
		newPrefab->mUUID = handle.getUUID();
		sceneObject->mPrefabLinkUUID = newPrefab->mUUID;
		newPrefab->_getRoot()->mPrefabLinkUUID = newPrefab->mUUID;

		return handle;
	}