extern MStatus initializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin plugin(obj, PLUGIN_COMPANY, "3.0", "Any");
	
	status = plugin.registerCommand("clusterWeightFunction",
									clusterWeightFunctionCmd::creator,
									clusterWeightFunctionCmd::newSyntax);
	
	if (!status) {
		status.perror("registerCommand");
	}

	return status;
}