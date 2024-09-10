MStatus initializePlugin( MObject obj )
{ 
	MStatus stat;

	MFnPlugin fnPlugin( obj, "Marco Giordano", "1.0", "Any");


	stat  =fnPlugin.registerNode("MG_dotProduct",
		MTypeId(0x832496),MG_dotProduct::creator,
		MG_dotProduct::initialize);

	if( stat != MS::kSuccess )
		stat.perror( "could not register the CustomLocator node" );

	return stat; 
}