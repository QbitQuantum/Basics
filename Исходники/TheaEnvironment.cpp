TheaSDK::Normal3D TheaRenderer::getSunDirection()
{
	MFnDependencyNode depFn(getRenderGlobalsNode());
	std::shared_ptr<RenderGlobals> renderGlobals = MayaTo::getWorldPtr()->worldRenderGlobalsPtr;
	std::shared_ptr<TheaRenderer> renderer = std::static_pointer_cast<TheaRenderer>(MayaTo::getWorldPtr()->worldRendererPtr);

	TheaSDK::Normal3D sunDir;

	MObjectArray nodeList;
	getConnectedInNodes(MString("sunLightConnection"), getRenderGlobalsNode(), nodeList);
	if( nodeList.length() > 0)	
	{
		MVector lightDir(0,0,1);
		MFnDagNode sunDagNode(nodeList[0]);
		//lightDir *= this->mtth_renderGlobals->globalConversionMatrix.inverse();
		lightDir *= sunDagNode.transformationMatrix();
		lightDir *= renderGlobals->globalConversionMatrix;
		lightDir.normalize();
		return TheaSDK::Normal3D(lightDir.x,lightDir.y,lightDir.z);
	}
	float sunDirX = 0.0f, sunDirY = 0.0f, sunDirZ = 1.0f;
	MPlug sunDirPlug = depFn.findPlug("sunDirection");
	if (!sunDirPlug.isNull())
	{
		sunDirX = sunDirPlug.child(0).asFloat();
		sunDirY = sunDirPlug.child(1).asFloat();
		sunDirZ = sunDirPlug.child(2).asFloat();
	}
	return TheaSDK::Normal3D(sunDirX, sunDirY, sunDirZ);
}