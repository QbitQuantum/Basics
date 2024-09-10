void ShadingNode::getConnectedInputObjects(MObjectArray& objectArray)
{
	MStatus stat;
	MFnDependencyNode depFn(this->mobject);
	MStringArray aliasArray;
	depFn.getAliasList(aliasArray);
	MObjectArray objectList;
	MPlugArray connections;
	depFn.getConnections(connections);

	for (uint connId = 0; connId < connections.length(); connId++)
	{
		MPlug p = connections[connId];
		if (!p.isDestination())
			continue;
		
		// a connection can be a direct connection or a child connection e.g. colorR, colorG...
		// but in a shader description file only the main attribute is listed so we go up until we have the main plug
		MPlug mainPlug = p;
		while (mainPlug.isChild())
			mainPlug = mainPlug.parent();
		if (mainPlug.isElement())
			mainPlug = mainPlug.array();
		MStringArray stringArray;
		// name contains node.attributeName, so we have to get rid of the nodeName
		mainPlug.name().split('.', stringArray);
		MString plugName = stringArray[stringArray.length() - 1];
		if (!this->isAttributeValid(plugName))
			continue;
		getConnectedInNodes(p, objectList);
		makeUniqueArray(objectList);
	}
	objectArray = objectList;
}