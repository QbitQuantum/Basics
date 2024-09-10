MStatus uninitializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin plugin(obj);

	status = plugin.deregisterCommand("AbcBulletExport");
	if (!status)
	{
		status.perror("deregisterCommand");
	}

	//MGlobal::executeCommandOnIdle("AlembicDeleteUI");

	return status;
}