MStatus particlePathsCmd::parseArgs( const MArgList& args )
{
	MArgDatabase argData(syntax(), args);

	//
	// Parse the time flags
	//

	if (argData.isFlagSet(startFlag))
	{
		argData.getFlagArgument(startFlag, 0, start);
	}

	if (argData.isFlagSet(finishFlag))
	{
		argData.getFlagArgument(finishFlag, 0, finish);
	}

	if (argData.isFlagSet(incrementFlag))
	{
		argData.getFlagArgument(incrementFlag, 0, increment);
	}

	if (finish <= start || increment <= 0.0)
	{
		MGlobal::displayError( "Invalid time arguments." );
		return MS::kFailure;
	}

	//
	// Get the particle system object
	//

	MSelectionList selectList;
	argData.getObjects(selectList);
	
	if( selectList.length() < 1 )
	{
		MGlobal::displayError( "Missing particle node name argument." );
		return MS::kFailure;
	}
	else if( selectList.length() > 1 )
	{
		MGlobal::displayError( "Too many particle nodes given." );
		return MS::kFailure;
	}

	selectList.getDependNode(0,particleNode);

	if (particleNode.isNull() || !particleNode.hasFn(MFn::kParticle))
	{
		MGlobal::displayError( "Invalid node argument." );
		return MS::kFailure;
	}

	return MS::kSuccess;
}