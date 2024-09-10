MStatus initializePlugin(MObject obj)
{
	MStatus   status;
	MFnPlugin plugin(obj, PLUGIN_COMPANY, "7.0", "Any");

	status = plugin.registerNode("exampleRampAttrNode", exampleRampAttrNode::id,
		   	exampleRampAttrNode::creator, exampleRampAttrNode::initialize);
	if (!status) 
	{
		status.perror("registerNode");
		return status;
	}

	return status;
}