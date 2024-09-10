MStatus polyMessageCmd::doIt( const MArgList& )
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

        MDagPath dp;
        MObject shapeNode = node;
        if ( MS::kSuccess == MDagPath::getAPathTo( node, dp ) )
            if ( MS::kSuccess == dp.extendToShape() )
                shapeNode = dp.node();

        bool wantIdChanges[3];
        wantIdChanges[MPolyMessage::kVertexIndex] = true;
        wantIdChanges[MPolyMessage::kEdgeIndex] = true;
        wantIdChanges[MPolyMessage::kFaceIndex] = true;

        id = MPolyMessage::addPolyComponentIdChangedCallback( shapeNode,
                wantIdChanges, 3,
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
            cout << "MPolyMessage.addCallback failed\n";
        }
    }

    return stat;
}