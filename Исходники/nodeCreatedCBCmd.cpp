MStatus uninitializePlugin( MObject obj )						
{																
	MFnPlugin	plugin( obj );									
	MStatus		stat;											
	stat = plugin.deregisterCommand( "nodeCreatedCB" );				
	if ( !stat )												
		stat.perror("deregisterCommand");						

	// Remove the API callback, necessary to prevent crashes.
	//
	MDGMessage::removeCallback( nodeCreatedCB::sId );

	nodeCreatedCB::sMelProcs.clear();
	nodeCreatedCB::sFullDagPath.clear();
	
	return stat;												
}