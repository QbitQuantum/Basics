MObject slopeShaderBehavior::findShadingEngine(MObject &node)
//
//	Description:
//		Given the material MObject this method will
//	return the shading group that it is assigned to.
//	if there is no shading group associated with
//	the material than a null MObject is apssed back.
//
{
	MFnDependencyNode nodeFn(node);
	MPlug srcPlug = nodeFn.findPlug("outColor");
	MPlugArray nodeConnections;
	srcPlug.connectedTo(nodeConnections, false, true);
	//loop through the connections
	//and find the shading engine node that
	//it is connected to
	//
	for(unsigned i = 0; i < nodeConnections.length(); i++)
	{
		if(nodeConnections[i].node().hasFn(MFn::kShadingEngine))
			return nodeConnections[i].node();
	}

	//no shading engine associated so return a
	//null MObject
	//
	return MObject();
}