void liqIPRNodeMessage::gatherUpdateObjects(std::vector<MString>& objects)
{
	MStatus status;

	//get selection list
	MSelectionList 	selection;
	IfMErrorWarn(MGlobal::getActiveSelectionList( selection ));

	for ( unsigned int i=0; i<selection.length(); i++ )
	{
		MObject node;
		IfMErrorWarn(selection.getDependNode( i, node ));

		MFnDependencyNode nodeFn(node, &status);
		IfMErrorWarn(status);

		const MString nodeName(nodeFn.name());
		objects.push_back(nodeName);//record current node

		if( isShaderNode(nodeName) )
		{
			onShaderNode(nodeName, objects);
		}
		else{
			onOtherNode(nodeName, objects);
		}
	}

	//add current camera shape node
	MStringArray cameraShapeFullPaths;
	IfMErrorWarn(MGlobal::executeCommand("string $cam = `getAttr liquidGlobals.renderCamera`; ls -long $cam;", cameraShapeFullPaths));
	objects.push_back(cameraShapeFullPaths[0]);

	//add current camera transform node

}