//-----------------------------------------------------------------------------
// Selects all vstAttachment nodes in the scene
//-----------------------------------------------------------------------------
MStatus CVstAttachmentCmd::DoSelect()
{
	MSelectionList mSelectionList;
	MDagPath mDagPath;

	for ( MItDag dagIt; !dagIt.isDone(); dagIt.next() )
	{
		if ( MFnDependencyNode( dagIt.item() ).typeName() == "vstAttachment" )
		{
			dagIt.getPath( mDagPath );
			mSelectionList.add( mDagPath, MObject::kNullObj, true );
		}
	}

	if ( mSelectionList.length() )
	{
		// Save the current selection just in case we want to undo stuff
		MGlobal::getActiveSelectionList( m_mSelectionList );
		MGlobal::setActiveSelectionList( mSelectionList, MGlobal::kReplaceList );
		m_undoable = true;
	}

	return MS::kSuccess;
}