bool
atomExport::setUpAnimLayers(MSelectionList &sList,atomAnimLayers &animLayers, std::vector<atomNodeWithAnimLayers *> &nodesWithAnimLayers,
						std::set<std::string> &attrStrings, atomTemplateReader &templateReader)
					
{
	unsigned int numObjects = sList.length();
	nodesWithAnimLayers.resize(numObjects);

	bool somethingIsAnimLayered = false; 
	for (unsigned int i = 0; i < numObjects; i++) 
	{
		atomNodeWithAnimLayers *nodeWithLayer = NULL;
		//make sure it's a NULL, and preset it in case we skip this node
		nodesWithAnimLayers[i] = nodeWithLayer;

		MDagPath path;
		MObject node;
		if (sList.getDagPath (i, path) == MS::kSuccess) 
		{
			MString name = path.partialPathName();
			//if the name is in the template, only then write it out...
			if(templateReader.findNode(name)== false)
			{
				continue;
			}
			node = path.node();
		}
		else if (sList.getDependNode (i, node) == MS::kSuccess) {
			
			if (!node.hasFn (MFn::kDependencyNode)) {
				continue;
			}
			MFnDependencyNode fnNode (node);
			MString name = fnNode.name();
			if(templateReader.findNode(name)== false)
			{
				continue;
			}
		}
		if(node.isNull()==false)
		{
			MSelectionList localList;
			localList.add(node);
			MPlugArray animatablePlugs;
			MAnimUtil::findAnimatablePlugs(localList,animatablePlugs);
			unsigned int numPlugs = animatablePlugs.length();
			MPlugArray cachedPlugs;
			for (unsigned int k = 0; k < numPlugs; k++)
			{
				MPlug plug = animatablePlugs[k];
				MObjectArray layers;
				MPlugArray	 plugs;
				if(MAnimUtil::findAnimationLayers(plug,layers,plugs) && layers.length() > 0)
				{
					bool layerAdded = animLayers.addAnimLayers(layers);
					if(layerAdded)
					{
						if(nodeWithLayer == NULL)
							nodeWithLayer = new atomNodeWithAnimLayers();
						nodeWithLayer->addPlugWithLayer(plug,layers,plugs);
					}
					somethingIsAnimLayered = somethingIsAnimLayered == false ? layerAdded : true;
				}
			}
			nodesWithAnimLayers[i] = nodeWithLayer;

		}
	}
	return somethingIsAnimLayered;
}