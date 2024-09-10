MStatus initializePlugin( MObject obj )
{
	MStatus   status;
    MFnPlugin plugin( obj, PLUGIN_COMPANY, "4.0", "Any");

    // NOTE: referenceQuery is already a Maya cmd
    status = plugin.registerCommand( "refQuery", 
									 referenceQuery::creator );
	if (!status) {
		status.perror("registerCommand");
		return status;
	}

    return status;
}