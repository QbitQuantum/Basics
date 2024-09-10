// Node added to model callback.
static void userNodeAddedCB(MObject& node,void *clientData)
{
	MStatus status;

	if (! node.isNull()) {
		bool doDisplay = true;

		MDagPath path;
		status = MDagPath::getAPathTo(node,path);
		if ( status.error() ) {
			doDisplay = false;
			MGlobal::displayInfo("Error: failed to get dag path to node.");
		}

		if ( doDisplay ) {
			MString s = path.fullPathName();
			MString info("DAG Model -  Node added: ");
			info+= s;

			path.transform(&status);
			if (MS::kInvalidParameter == status) {
				info += "(WORLD)";
			}

			MGlobal::displayInfo(info);	
		}
	}

	// remove the callback
	MCallbackId id = MMessage::currentCallbackId();
	MMessage::removeCallback(id);

	// listen for removal message
	/* MCallbackId id = */ MModelMessage::addNodeRemovedFromModelCallback( node, userNodeRemovedCB, 0, &status );
	if ( status.error() ) {
		MGlobal::displayError("Failed to install node removed from model callback.\n");
		return;
	}
}