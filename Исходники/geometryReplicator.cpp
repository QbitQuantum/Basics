void geometryReplicatorGeometryOverride::updateDG()
{
	if (!fPath.isValid()) {
		MFnDependencyNode fnThisNode(fThisNode);

		MObject messageAttr = fnThisNode.attribute("message");
		MPlug messagePlug(fThisNode, messageAttr);

		MPlugArray connections;
		if (messagePlug.connectedTo(connections, false, true)) {
			for (unsigned int i = 0; i < connections.length(); ++i) {
				MObject node = connections[i].node();
				if (node.hasFn(MFn::kMesh) ||
					node.hasFn(MFn::kNurbsSurface) ||
					node.hasFn(MFn::kNurbsCurve) ||
					node.hasFn(MFn::kBezierCurve))
				{
					MDagPath path;
					MDagPath::getAPathTo(node, path);

					fPath = path;
					fType = path.apiType();

					break;
				}
			}
		}
	}
}