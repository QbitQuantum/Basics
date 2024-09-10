void printMaterials(const MDagPath& dagPath) {
	MFnMesh fnMesh(dagPath);
	unsigned instanceNumber = dagPath.instanceNumber();
	MObjectArray sets;
	MObjectArray comps;
	fnMesh.getConnectedSetsAndMembers( instanceNumber, sets, comps, true );

	// Print Material Names
	for(unsigned int i = 0; i < sets.length(); ++i)
	{
		MFnDependencyNode fnDepSGNode(sets[i]);
		std::cout << fnDepSGNode.name() << std::endl;
	}
}