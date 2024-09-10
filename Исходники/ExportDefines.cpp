MObject findShader(MObject& setNode, SXRShaderData& d)
//
//  Description:
//      Find the shading node for the given shading group set node.
//
{
	MFnDependencyNode fnNode(setNode);
	d.name	= fnNode.name();
	// cout << "looking for shader in node " << fnNode.name().asChar() << "\n";
	MPlug shaderPlug = fnNode.findPlug("surfaceShader");

	if (!shaderPlug.isNull()) {			
		MPlugArray connectedPlugs;
		bool asSrc = false;
		bool asDst = true;
		shaderPlug.connectedTo( connectedPlugs, asDst, asSrc );

		if (connectedPlugs.length() != 1)
			Msg("!Error getting shader");
		else 
			return connectedPlugs[0].node();
	}

	Msg("!Error finding surface shader for node '%s'",fnNode.name().asChar());
	return MObject::kNullObj;
}