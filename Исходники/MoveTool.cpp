///////////////////////////////////////////////////////////////////////
//
// The following routines are used to register/unregister
// the commands we are creating within Maya
//
///////////////////////////////////////////////////////////////////////
MStatus initializePlugin( MObject obj )
{
	MStatus		status;
	MFnPlugin	plugin( obj, PLUGIN_COMPANY, "3.0", "Any" );

	status = plugin.registerContextCommand( CREATE_CTX_NAME,
									&moveContextCommand::creator,
									MOVENAME, &moveCmd::creator );
	if (!status) {
		status.perror("registerContextCommand");
		return status;
	}

	return status;
}