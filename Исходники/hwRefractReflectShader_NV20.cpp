MStatus initializePlugin( MObject obj )
{ 
	MStatus   status;
	
	const MString UserClassify( "shader/surface/utility" );

	MFnPlugin plugin( obj, PLUGIN_COMPANY, "4.0", "Any");
	status = plugin.registerNode( "hwRefractReflectShader_NV20", hwRefractReflectShader_NV20::id, 
			                      hwRefractReflectShader_NV20::creator, hwRefractReflectShader_NV20::initialize,
								  MPxNode::kHwShaderNode, &UserClassify );
	if (!status) {
		status.perror("registerNode");
		return status;
	}

	return MS::kSuccess;
}