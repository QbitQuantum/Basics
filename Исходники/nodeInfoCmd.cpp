/////////////////////////////////////////////////////////////////
//
// The following routines are used to register/unregister
// the command we are creating within Maya
//
/////////////////////////////////////////////////////////////////
MStatus initializePlugin( MObject obj )
{
	MStatus   status;
	MFnPlugin plugin( obj, PLUGIN_COMPANY, "3.0", "Any");

	status = plugin.registerCommand( "nodeInfo",
									  nodeInfo::creator,
									  nodeInfo::newSyntax);
	if (!status) {
		status.perror("registerCommand");
		return status;
	}

	return status;
}