MStatus initializePlugin ( MObject obj )
{
	MStatus   status;
	MFnPlugin plugin(obj, "Autodesk - nCloth Prototype 4", "8.5", "Any");	

	status = plugin.registerNode ( "testNucleusNode", testNucleusNode::id,testNucleusNode ::creator, testNucleusNode::initialize );

	if ( !status )
	{
		status.perror("registerNode");
		return status;
	}

	return status;
}