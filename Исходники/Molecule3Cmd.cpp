MStatus	Molecule3Cmd::undoIt()
{
	MDGModifier dgMod;
	MFnDagNode dagFn;
	MObject child;
	
	unsigned int i;
	for( i=0; i < objTransforms.length(); i++ )
	{
		// N.B. It is important to delete the child shape before
		// the transform node, otherwise Maya will crash.
		dagFn.setObject( objTransforms[i] );
		child = dagFn.child( 0 );
		dgMod.deleteNode( child );
		
		dgMod.deleteNode( objTransforms[i] );
	}
	
	return dgMod.doIt();
}