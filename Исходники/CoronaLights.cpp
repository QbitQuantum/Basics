bool CoronaRenderer::isSunLight(std::shared_ptr<MayaObject> obj)
{
	// a sun light has a transform connection to the coronaGlobals.sunLightConnection plug
	MObject coronaGlobals = objectFromName(MString("coronaGlobals"));
	MObjectArray nodeList;
	MStatus stat;
	getConnectedInNodes(MString("sunLightConnection"), coronaGlobals, nodeList);
	if( nodeList.length() > 0)
	{
		MObject sunObj = nodeList[0];
		if(sunObj.hasFn(MFn::kTransform))
		{
			MFnDagNode sunDagNode(sunObj);
			MObject sunDagObj =	sunDagNode.child(0, &stat);
			if( sunDagObj == obj->mobject)
				return true;
		}
	}
	return false;
}