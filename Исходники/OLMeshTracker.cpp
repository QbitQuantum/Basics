// Call for an unload when list is already locked
void OLMeshTracker::MakeUnLoadedLocked(Ogre::String meshName, Ogre::String stringParam, Ogre::Entity* entityParam) {
	// see if in the loading list. Remove if  there.
	GenericQm* loadEntry = m_meshesToLoad->Find(meshName);
	if (loadEntry != NULL) {
		loadEntry->Abort();
		m_meshesToLoad->Remove(meshName);
	}
	// see if in the serialize list. Mark for unload if it's there
	GenericQm* serialEntry = m_meshesToSerialize->Find(meshName);
	if (serialEntry != NULL) {
		serialEntry->stringParam = "unload";
	}
	else {
		Ogre::MeshPtr meshP = Ogre::MeshManager::getSingleton().getByName(meshName);
		if (!meshP.isNull()) {
			if (meshP.useCount() == 1) {
				meshP->unload();
			}
			else {
				LG::Log("OLMeshTracker::MakeUnLoaded: Didn't unload mesh because count = %d", meshP.useCount());
			}
		}
	}
}