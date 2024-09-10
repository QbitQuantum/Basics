MStatus nodeMessageCmd::doIt( const MArgList& )
//
// Takes the  nodes that are on the active selection list and adds an
// attriubte changed callback to each one.
//
{
	MStatus 		stat;
	MObject 		node;
	MSelectionList 	list;
    MCallbackId     id;
    
	// Register node callbacks for all nodes on the active list.
	//
	MGlobal::getActiveSelectionList( list );

    for ( unsigned int i=0; i<list.length(); i++ )
    {
        list.getDependNode( i, node );
        
	    id = MNodeMessage::addAttributeChangedCallback( node,
                                                        userCB,
                                                        NULL,
                                                        &stat);

    	// If the callback was successfully added then add the
        // callback id to our callback table so it can be removed
        // when the plugin is unloaded.
	    //
	    if ( stat ) {
		    callbackIds.append( id );
    	} else {
	    	cout << "MNodeMessage.addCallback failed\n";
    	}
    }
        
	return stat;
}