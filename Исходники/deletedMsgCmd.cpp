MStatus deletedMessage::doIt( const MArgList& args )
{
	MStatus status = MS::kSuccess;

	MArgDatabase argData(syntax(), args);
	MSelectionList objects;
	argData.getObjects(objects);

	for (unsigned int i = 0; i < objects.length(); i++) {
		MObject node;
		objects.getDependNode(i, node);
		
		callbackIds.append(
			MNodeMessage::addNodeAboutToDeleteCallback (node, aboutToDeleteCB, NULL, &status)
		);
		if (!status) {
			MGlobal::displayWarning("Could not attach about to delete callback for node.");
			continue;
		}
		callbackIds.append(
			MNodeMessage::addNodePreRemovalCallback (node, preRemovalCB, NULL, &status)
		);
		if (!status) {
			MGlobal::displayWarning("Could not attach pre-removal callback for node.");
			continue;
		}
		if (!nodeRemovedCBRegistered)
		{
			callbackIds.append(
				MDGMessage::addNodeRemovedCallback(removeCB, "dependNode", NULL, &status)
			);
			if (!status) {
				MGlobal::displayWarning("Could not attach node removal callback.");
				continue;
			}
			nodeRemovedCBRegistered = true;
		}
	}
	
	return status;
}